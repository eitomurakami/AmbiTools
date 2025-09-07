//-----------------------------------------------------------------------------
// file: AmbiBin.cpp
// desc: 
//
// Template MetaSound code provided by Epic Games.
// 
// author: Eito Murakami (https://ccrma.stanford.edu/~eitom/)
// date: Winter 2025
//-----------------------------------------------------------------------------

#include "AmbiBin.h"

#define LOCTEXT_NAMESPACE "Metasound_AmbiBin"

namespace Metasound
{
    //------------------------------------------------------------------------------------
    // FAmbiBinOperator
    //------------------------------------------------------------------------------------
    FAmbiBinOperator::FAmbiBinOperator(const FOperatorSettings& InSettings, const FAudioBufferReadRef& InAudioInput1, const FAudioBufferReadRef& InAudioInput2, const FAudioBufferReadRef& InAudioInput3, const FAudioBufferReadRef& InAudioInput4, const FFloatReadRef& InRoll, const FFloatReadRef& InPitch, const FFloatReadRef& InYaw)
        : AudioInput1(InAudioInput1)
        , AudioInput2(InAudioInput2)
        , AudioInput3(InAudioInput3)
        , AudioInput4(InAudioInput4)
        , Roll(InRoll)
        , Pitch(InPitch)
        , Yaw(InYaw)
        , AudioOutputLeft(FAudioBufferWriteRef::CreateNew(InSettings))
        , AudioOutputRight(FAudioBufferWriteRef::CreateNew(InSettings))
        
    { 
        ambi_bin_create(&hAmbi);
        ambi_bin_setNormType(hAmbi, NORM_N3D);
        ambi_bin_setInputOrderPreset(hAmbi, SH_ORDER_FIRST);
        ambi_bin_setUseDefaultHRIRsflag(hAmbi, 1);
        ambi_bin_setEnableRotation(hAmbi, true);
        ambi_bin_initCodec(hAmbi);
        ambi_bin_init(hAmbi, InSettings.GetSampleRate());
        //FAmbiToolsModule::Log(FString("Channel Order: ") + FString::FromInt(ambi_bin_getChOrder(hAmbi)));
        //FAmbiToolsModule::Log(FString("Decoding Method: ") + FString::FromInt(ambi_bin_getDecodingMethod(hAmbi)));
    }
    FAmbiBinOperator::~FAmbiBinOperator()
    {
        ambi_bin_destroy(&hAmbi);
    }

    /// <summary>
    /// Assign reference to inlet params
    /// </summary>
    /// <returns></returns>
    FDataReferenceCollection FAmbiBinOperator::GetInputs() const
    {
        using namespace AmbiBin;

        FDataReferenceCollection InputDataReferences;

        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNameAudioInput1), AudioInput1);
        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNameAudioInput2), AudioInput2);
        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNameAudioInput3), AudioInput3);
        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNameAudioInput4), AudioInput4);
        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNameRoll), Roll);
        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNamePitch), Pitch);
        InputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(InParamNameYaw), Yaw);

        return InputDataReferences;
    }

    /// <summary>
    /// Assign reference to outlet param
    /// </summary>
    /// <returns></returns>
    FDataReferenceCollection FAmbiBinOperator::GetOutputs() const
    {
        using namespace AmbiBin;

        FDataReferenceCollection OutputDataReferences;

        OutputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(OutParamNameAudioOutputLeft), AudioOutputLeft);
        OutputDataReferences.AddDataReadReference(METASOUND_GET_PARAM_NAME(OutParamNameAudioOutputRight), AudioOutputRight);

        return OutputDataReferences;
    }

    /// <summary>
    /// Process audio block
    /// </summary>
    void FAmbiBinOperator::Execute()
    {
        const float* inBuffer1 = AudioInput1->GetData();
        const float* inBuffer2 = AudioInput2->GetData();
        const float* inBuffer3 = AudioInput3->GetData();
        const float* inBuffer4 = AudioInput4->GetData();
        float* outBufferLeft = AudioOutputLeft->GetData();
        float* outBufferRight = AudioOutputRight->GetData();
        const int32 blockSize = AudioOutputLeft->Num();
        int frameSize = ambi_bin_getFrameSize();
        //FAmbiConvModule::Log(FString("Block Size: ") + FString::FromInt(blockSize));
        //FAmbiConvModule::Log(FString("Frame Size: ") + FString::FromInt(frameSize));

        // Rotate ambisonics
        ambi_bin_setRoll(hAmbi, *Roll);
        ambi_bin_setPitch(hAmbi, *Pitch);
        ambi_bin_setYaw(hAmbi, *Yaw);

        // Create temp buffers
        const float* inFrame[4];
        float* outFrame[2]{ new float[frameSize], new float[frameSize] };

        // Iterate through frames
        for (int frame = 0; frame < ceil(blockSize / frameSize); frame++)
        {
            inFrame[0] = inBuffer1 + frame * frameSize;
            inFrame[1] = inBuffer2 + frame * frameSize;
            inFrame[2] = inBuffer3 + frame * frameSize;
            inFrame[3] = inBuffer4 + frame * frameSize;
            ambi_bin_process(hAmbi, inFrame, outFrame, 4, 2, frameSize);
            for (int i = 0; i < frameSize; i++)
            {
                int sampleIndex = i + frame * frameSize;
                if (sampleIndex >= blockSize) break;

                *(outBufferLeft + sampleIndex) = *(outFrame[0] + i);
                *(outBufferRight + sampleIndex) = *(outFrame[1] + i);
            }
        }

        // Clean up
        delete outFrame[0];
        delete outFrame[1];
    }

    /// <summary>
    /// Declare params
    /// </summary>
    /// <returns></returns>
    const FVertexInterface& FAmbiBinOperator::GetVertexInterface()
    {
        using namespace AmbiBin;

        static const FVertexInterface Interface(
            FInputVertexInterface(
                TInputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAudioInput1)),
                TInputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAudioInput2)),
                TInputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAudioInput3)),
                TInputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameAudioInput4)),
                TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameRoll), 0.0f),
                TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNamePitch), 0.0f),
                TInputDataVertex<float>(METASOUND_GET_PARAM_NAME_AND_METADATA(InParamNameYaw), 0.0f)
            ),

            FOutputVertexInterface(
                TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutParamNameAudioOutputLeft)),
                TOutputDataVertex<FAudioBuffer>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutParamNameAudioOutputRight))
            )
        );

        return Interface;
    }

    /// <summary>
    /// Define node info
    /// </summary>
    /// <returns></returns>
    const FNodeClassMetadata& FAmbiBinOperator::GetNodeInfo()
    {
        auto InitNodeInfo = []() -> FNodeClassMetadata
        {
            FNodeClassMetadata Info;

            Info.ClassName        = { TEXT("UE"), TEXT("AmbiBin"), TEXT("Audio") };
            Info.MajorVersion     = 1;
            Info.MinorVersion     = 0;
            Info.DisplayName      = LOCTEXT("DisplayName", "AmbiBin");
            Info.Description      = LOCTEXT("Description", "1st order ambisonics binaural decoder using Spatial Audio Framework.");
            Info.Author           = PluginAuthor;
            Info.PromptIfMissing  = PluginNodeMissingPrompt;
            Info.DefaultInterface = GetVertexInterface();
            Info.CategoryHierarchy = { LOCTEXT("NodeCategory", "Utils") };

            return Info;
        };

        static const FNodeClassMetadata Info = InitNodeInfo();

        return Info;
    }

    /// <summary>
    /// Create operator
    /// </summary>
    /// <param name="InParams"></param>
    /// <param name="OutErrors"></param>
    /// <returns></returns>
    TUniquePtr<IOperator> FAmbiBinOperator::CreateOperator(const FCreateOperatorParams& InParams, FBuildErrorArray& OutErrors)
    {
        using namespace AmbiBin;

        const FDataReferenceCollection& InputCollection = InParams.InputDataReferences;
        const FInputVertexInterface& InputInterface     = GetVertexInterface().GetInputInterface();

        FAudioBufferReadRef InAudioInput1 = InputCollection.GetDataReadReferenceOrConstruct<FAudioBuffer>(METASOUND_GET_PARAM_NAME(InParamNameAudioInput1), InParams.OperatorSettings);
        FAudioBufferReadRef InAudioInput2 = InputCollection.GetDataReadReferenceOrConstruct<FAudioBuffer>(METASOUND_GET_PARAM_NAME(InParamNameAudioInput2), InParams.OperatorSettings);
        FAudioBufferReadRef InAudioInput3 = InputCollection.GetDataReadReferenceOrConstruct<FAudioBuffer>(METASOUND_GET_PARAM_NAME(InParamNameAudioInput3), InParams.OperatorSettings);
        FAudioBufferReadRef InAudioInput4 = InputCollection.GetDataReadReferenceOrConstruct<FAudioBuffer>(METASOUND_GET_PARAM_NAME(InParamNameAudioInput4), InParams.OperatorSettings);
        FFloatReadRef InRoll = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<float>(InputInterface, METASOUND_GET_PARAM_NAME(InParamNameRoll), InParams.OperatorSettings);
        FFloatReadRef InPitch = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<float>(InputInterface, METASOUND_GET_PARAM_NAME(InParamNamePitch), InParams.OperatorSettings);
        FFloatReadRef InYaw = InputCollection.GetDataReadReferenceOrConstructWithVertexDefault<float>(InputInterface, METASOUND_GET_PARAM_NAME(InParamNameYaw), InParams.OperatorSettings);

        return MakeUnique<FAmbiBinOperator>(InParams.OperatorSettings, InAudioInput1, InAudioInput2, InAudioInput3, InAudioInput4, InRoll, InPitch, InYaw);
    }


    //------------------------------------------------------------------------------------
    // FAmbiBin
    //------------------------------------------------------------------------------------
    FAmbiBin::FAmbiBin(const FNodeInitData& InitData)
        : FNodeFacade(InitData.InstanceName, InitData.InstanceID, TFacadeOperatorClass<FAmbiBinOperator>())
    {
    }

    METASOUND_REGISTER_NODE(FAmbiBin)
}

#undef LOCTEXT_NAMESPACE
