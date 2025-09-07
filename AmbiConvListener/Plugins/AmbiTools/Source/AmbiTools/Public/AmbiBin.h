//-----------------------------------------------------------------------------
// file: AmbiBin.h
// desc: 
//
// Template MetaSound code provided by Epic Games.
// 
// author: Eito Murakami (https://ccrma.stanford.edu/~eitom/)
// date: Winter 2025
//-----------------------------------------------------------------------------

#include "AmbiTools.h"

#include "MetasoundEnumRegistrationMacro.h"
#include "MetasoundParamHelper.h"
#include "MetasoundParamHelper.h"
#include "AmbiTools/SAF/include/ambi_bin.h"

namespace Metasound
{
#define LOCTEXT_NAMESPACE "Metasound_AmbiBin"

    namespace AmbiBin
    {
        METASOUND_PARAM(InParamNameAudioInput1, "Audio Input 1", "Audio input 1.")
        METASOUND_PARAM(InParamNameAudioInput2, "Audio Input 2", "Audio input 2.")
        METASOUND_PARAM(InParamNameAudioInput3, "Audio Input 3", "Audio input 3.")
        METASOUND_PARAM(InParamNameAudioInput4, "Audio Input 4", "Audio input 4.")
        METASOUND_PARAM(InParamNameRoll, "Roll", "Roll")
        METASOUND_PARAM(InParamNamePitch, "Pitch", "Pitch")
        METASOUND_PARAM(InParamNameYaw, "Yaw", "Yaw")
        METASOUND_PARAM(OutParamNameAudioOutputLeft, "Audio Output Left", "Audio output left.")
        METASOUND_PARAM(OutParamNameAudioOutputRight, "Audio Output Right", "Audio output right.")
    }

#undef LOCTEXT_NAMESPACE


    //------------------------------------------------------------------------------------
    // FAmbiBinOperator
    //------------------------------------------------------------------------------------
    class FAmbiBinOperator : public TExecutableOperator<FAmbiBinOperator>
    {
    public:
        static const FNodeClassMetadata& GetNodeInfo();
        static const FVertexInterface& GetVertexInterface();
        static TUniquePtr<IOperator> CreateOperator(const FCreateOperatorParams& InParams, FBuildErrorArray& OutErrors);

        FAmbiBinOperator(const FOperatorSettings& InSettings, const FAudioBufferReadRef& InAudioInput1, const FAudioBufferReadRef& InAudioInput2, const FAudioBufferReadRef& InAudioInput3, const FAudioBufferReadRef& InAudioInput4, const FFloatReadRef& InRoll, const FFloatReadRef& InPitch, const FFloatReadRef& InYaw);
        ~FAmbiBinOperator();

        virtual FDataReferenceCollection GetInputs()  const override;
        virtual FDataReferenceCollection GetOutputs() const override;

        void Execute();

    private:
        void* hAmbi;

        // audio input
        FAudioBufferReadRef  AudioInput1;
        FAudioBufferReadRef  AudioInput2;
        FAudioBufferReadRef  AudioInput3;
        FAudioBufferReadRef  AudioInput4;

        // rotation
        FFloatReadRef Roll;
        FFloatReadRef Pitch;
        FFloatReadRef Yaw;

        // audio output
        FAudioBufferWriteRef AudioOutputLeft;
        FAudioBufferWriteRef AudioOutputRight;
    };

    //------------------------------------------------------------------------------------
    // FAmbiBin
    //------------------------------------------------------------------------------------
    class FAmbiBin : public FNodeFacade
    {
    public:
        // Constructor used by the Metasound Frontend.
        FAmbiBin(const FNodeInitData& InitData);
    };
}
