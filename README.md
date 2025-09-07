Presented at International Conference on Immersive and 3D Audio (I3DA) 2025 in Bologna, Italy.

# AmbiTools

**_AmbiTools (Ambisonic Virtual Acoustics Playback Toolkit)_** is an open-source framework for curating virtual reality scenes to support musicological and archeological studies that examine the effects of room acoustics. The toolkit is structured as an Unreal Engine 5 plugin and its Application Programming Interface (APIs) as well as template assets and applications that provide off-the-shelf interactive experiences. 

The toolkit is capable of computing the real-time convolution of first-order ambisonic room impulse responses (IRs) with live, synthesized, or recorded source signals. Other core features include:
1. Playing back first-order ambisonic signals
2. Displaying 360° images and videos
3. Defining scenes as a collection of audiovisual assets
4. Designing graphical user interface (GUI)

The toolkit embraces two distinct workflows: rapid prototyping of virtual environments for data analysis during fieldwork and detailed construction of VR scenes for public presentations and archives. In doing so, the toolkit enables curation of virtual scenes without the need to directly use a game engine while offering extensible APIs for developers who wish to customize the features inside the Unreal Engine project.

<img width="350" height="250" alt="image" src="https://github.com/user-attachments/assets/a10520e8-f52a-4972-b441-f8a5956fb9e8">
<img width="350" height="250" alt="image" src="https://github.com/user-attachments/assets/a090b6d9-1629-4957-958d-8f92b8b8daec">

## Project Compilation
The **AmbiTools** plugin is supported on Windows 11 only. This toolkit internally utilizes [Chunreal—the ChucK music programming language in Unreal Engine](https://github.com/ccrma/chunreal) by Eito Murakami and Ge Wang and [Spatial Audio Framework (SAF)](https://github.com/leomccormack/Spatial_Audio_Framework) by Leo McCormack et al.

### 1. Install Intel Math Kernel Library (MKL)
The **AmbiTools** plugin requires  [Intel® Math Kernel Library (MKL) for Windows OS](https://www.intel.com/content/www/us/en/docs/onemkl/get-started-guide/2025-1/overview.html) installed on your computer.

### 2. Set up Unreal Engine 5
If this is your first time using Unreal Engine, install the [Epic Games Launcher](https://store.epicgames.com/en-US/download) and create an account. Install Unreal Engine 5.3 or above from the Epic Games Launcher. 

### 3. Set up Visual Studio
Set up your IDE for compiling UE projects by following these tutorials:

https://docs.unrealengine.com/5.3/en-US/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine/

https://docs.unrealengine.com/5.3/en-US/how-to-generate-unreal-engine-project-files-for-your-ide/

### 4. Compile 
Locate **AmbiConvListener.uproject** in the repository. Right click on it and select **Generate Visual Studio Project Files**. Open the generated Visual Studio 2022 solution and select Build.
