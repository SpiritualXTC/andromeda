   _____              .___                                .___       
  /  _  \   ____    __| _/______  ____   _____   ____   __| _/____   
 /  /_\  \ /    \  / __ |\_  __ \/  _ \ /     \_/ __ \ / __ |\__  \  
/    |    \   |  \/ /_/ | |  | \(  <_> )  Y Y  \  ___// /_/ | / __ \_
\____|__  /___|  /\____ | |__|   \____/|__|_|  /\___  >____ |(____  /
        \/     \/      \/                    \/     \/     \/     \/ 

TODO: (Priority)
- Resource Managerment and strip the old manager out
- Fix Specular Highlighting
- Texture & Shader Annotations
- Deferred Shadows
- Add observer to the logger, remove logging events 
- Fix Environment Reflections
- Make the lighting system updatable outside of the renderer
	- Lighting is only a basic setup for testing the shaders currently


TODO: (Overview)
- Resource Management overhaul
- File Management/Loading
- Texture Annotations
- Shader Annotations
- Abstract OpenGL
- XML Helper Library
- zLib Support
- RocketLib Support
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
