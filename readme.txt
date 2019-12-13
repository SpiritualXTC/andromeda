   _____              .___                                .___       
  /  _  \   ____    __| _/______  ____   _____   ____   __| _/____   
 /  /_\  \ /    \  / __ |\_  __ \/  _ \ /     \_/ __ \ / __ |\__  \  
/    |    \   |  \/ /_/ | |  | \(  <_> )  Y Y  \  ___// /_/ | / __ \_
\____|__  /___|  /\____ | |__|   \____/|__|_|  /\___  >____ |(____  /
        \/     \/      \/                    \/     \/     \/     \/ 





TODO:
- Rebuild project from scratch!

- premake5 			[build tools]
- Libraries
	- General		[Boost]
	- Assets		[AssImp]
	- Physics 		[Bullet]
	- UI			[imgui]
	- Graphics		[OpenGL / GLEW]
	- Compute		[OpenCL]
	- SceneGraph	[OpenSceneGraph]
	- FreeType		[FreeType]
	- GLM			[Math]
	- Extras
		- osgbullet	[Integration of Bullet and OpenSceneGraph]



File Structure:
andromeda
	/Build					[Build Scripts / Premake Files]
	/Bin					[Binary Outputs]
		/%cfg
	/Immediate
		/%cfg
	/Vendor					[3rd Party Includes :: Would be great if it supported linking later, but leave it as is for now]
	/Project				[Generated Project Files *.vs, *.make, etc]
	
	/Andromeda				[Interfaces/Header Only should be /Andromeda ?]
		/Core				[Core Engine Interfaces]
		/Compute			
		/Graphics
		/Physics
		/UI
		/Util				[Logging, etc]
			
	/Source					[Source]
		/Core
		/Platform			[Platform Specific Logic / GUI Management]
			/%platform		[cfg = Windows / Android / Linux / etc]
		/OpenGL				[Open GL]
			/%platform		[Open GL Platform Specific Requirements]
		/OpenCL				[Open CL]
		/Bullet				[Physics]
		/UI					[User Interface]
		/Util
		
		Extras:
		/XEffect			[May remove this]
	/Data					[Resource Files]
		*.dat				[Packaged Resource Files]
		/Textures
		/Shaders
		/Meshes
		/Fonts
	/Resource				[Resource Project Files, blender/photoshop etc]



TODO: (Overview) [OLD]
- Resource Management overhaul
- File Management/Loading
- Texture Annotations
- Shader Annotations
- Abstract OpenGL
- XML Helper Library
- zLib Support
- ImgUI
- Change ALL header include gates








Library:
- Break the mega-library up into chunks / Move Project over to CMake
	AndromedaCore			: Platform Agnostic
	AndomredaSDL			: SDL "Platform" Implementation (HAHA - Ezy Mode)
	AndromedaWindows		: Windows Functionality
	AndromedaAndroid		: Android Functionality
	AndromedaGL				: OpenGL Functionality shared across multiple platforms (TODO)
	AndromedaCL				: OpenCL Functionality shared across multiple platforms (TODO)
	AndromedaXEffect		: XML Effect/Shader System
	AndromedaZLib			: ZLib support via a wrapper that taps into the virtual resource management
 



Particle System
 - GPU & CPU implementations
	(and obviously a common interface)
	
Resource Management
 - Better loading mechanisms 
 - Better functionality for dealing with resource streams
 - Binary Support in file system
 - Virtual Stream Support


3rd Party DEPENDANCIES:
boost
 - Required
 - Version 1.6

glew
 - Required for Windows (Maybe others)

glm
 - Required

SDL (Remove)
 - Used by a temporary testing framework

SOIL (Look for an alternative) - May use DevIL
 - Currently Required
 - Loads images
 - Doesn't like loading from images memory for some file types?

zLib
 - Not used yet
