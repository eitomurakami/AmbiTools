using System.IO;
using UnrealBuildTool;

public class oneAPI : ModuleRules
{
	public oneAPI(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

        // Note: You must have Intel Math Kernel Library (MKL) installed on your computer to compile this plugin!
        const string MKL_DIR = "C:/Program Files (x86)/Intel/oneAPI/mkl/latest/";

        // Add the import library
        PublicAdditionalLibraries.Add(Path.Combine(MKL_DIR, "lib/mkl_rt.lib"));

        // Delay-load the DLL, so we can load it from the right place first
        PublicDelayLoadDLLs.Add("mkl_rt.2.dll");

        // Ensure that the DLL is staged next to the executable
        // Note: You must have Intel Math Kernel Library (MKL) installed on your computer to compile this plugin!
        // Which DLLs you need depend on your computer architecture. Please refer to Intel's documentation on linking DLLs:
        // https://www.intel.com/content/www/us/en/docs/onemkl/developer-guide-windows/2025-2/overview.html
        RuntimeDependencies.Add("$(BinaryOutputDir)/mkl_rt.2.dll", Path.Combine(MKL_DIR, "bin/mkl_rt.2.dll"));
        RuntimeDependencies.Add("$(BinaryOutputDir)/mkl_core.2.dll", Path.Combine(MKL_DIR, "bin/mkl_core.2.dll"));
        RuntimeDependencies.Add("$(BinaryOutputDir)/mkl_def.2.dll", Path.Combine(MKL_DIR, "bin/mkl_def.2.dll"));
        RuntimeDependencies.Add("$(BinaryOutputDir)/mkl_intel_thread.2.dll", Path.Combine(MKL_DIR, "bin/mkl_intel_thread.2.dll"));
        RuntimeDependencies.Add("$(BinaryOutputDir)/mkl_vml_def.2.dll", Path.Combine(MKL_DIR, "bin/mkl_vml_def.2.dll"));

        // Add include path
        PublicIncludePaths.Add(Path.Combine(MKL_DIR, "include"));
    }
}
