//-----------------------------------------------------------------------------
// file: AmbiTools.cpp
// desc: AmbiTools plugin module definition.
//
// Template plugin code provided by Epic Games.
// 
// author: Eito Murakami (https://ccrma.stanford.edu/~eitom/)
// date: Winter 2025
//-----------------------------------------------------------------------------

#include "AmbiTools.h"
#include "MetasoundFrontendRegistries.h"

#define LOCTEXT_NAMESPACE "FAmbiToolsModule"

// Define custom log category "LogAmbi"
DEFINE_LOG_CATEGORY(LogAmbi);

void FAmbiToolsModule::StartupModule()
{
    // Register MetaSound Nodes
    FMetasoundFrontendRegistryContainer::Get()->RegisterPendingNodes();

    // Note: You must have Intel Math Kernel Library (MKL) installed on your computer to compile this plugin!
    const FString BasePluginDir = IPluginManager::Get().FindPlugin("AmbiTools")->GetBaseDir();
    const FString mklPath = "C:/Program Files (x86)/Intel/oneAPI/mkl/latest/bin/mkl_rt.2.dll";
    mklHandle = FPlatformProcess::GetDllHandle(*mklPath);
    if (!mklHandle)
    {
        FAmbiToolsModule::Log("Failed to load MKL.");
    }
    else
    {
        FAmbiToolsModule::Log("Loaded MKL.");
    }
}

void FAmbiToolsModule::ShutdownModule()
{ 
}

/// <summary>
/// static function to output custom log
/// </summary>
/// <param name="message"></param>
void FAmbiToolsModule::Log(FString message)
{
    UE_LOG(LogAmbi, Log, TEXT("%s"), *message);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FAmbiToolsModule, AmbiTools)
