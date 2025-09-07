using System.IO;
using UnrealBuildTool;

public class AmbiTools : ModuleRules
{
    public AmbiTools(ReadOnlyTargetRules Target) : base(Target)
    {
        // Allow C++ try catch
        bEnableExceptions = true;

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Disable some warnings
        bEnableUndefinedIdentifierWarnings = false;
        
        // Add include paths
        PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source/AmbiTools/SAF/include"));
        PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source/AmbiTools/SAF/framework/include"));

        // Add preprocessor macro
        PublicDefinitions.Add("SAF_USE_INTEL_MKL_LP64");

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "MetasoundFrontend",
                "MetasoundGraphCore",
            }
        );
            
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Projects",
                "oneAPI"
            }
        );
    }
}
