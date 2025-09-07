//-----------------------------------------------------------------------------
// file: AmbiTools.h
// desc: AmbiTools plugin module header.
//
// Template plugin code provided by Epic Games.
// 
// author: Eito Murakami (https://ccrma.stanford.edu/~eitom/)
// date: Winter 2025
//-----------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "mkl.h"

// Declare custom log category "LogAmbi"
DECLARE_LOG_CATEGORY_EXTERN(LogAmbi, Log, All);

class FAmbiToolsModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    // static function to output custom log
    static void Log(FString message);

private:
    void* mklHandle;
};
