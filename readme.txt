   _____              .___                                .___       
  /  _  \   ____    __| _/______  ____   _____   ____   __| _/____   
 /  /_\  \ /    \  / __ |\_  __ \/  _ \ /     \_/ __ \ / __ |\__  \  
/    |    \   |  \/ /_/ | |  | \(  <_> )  Y Y  \  ___// /_/ | / __ \_
\____|__  /___|  /\____ | |__|   \____/|__|_|  /\___  >____ |(____  /
        \/     \/      \/                    \/     \/     \/     \/ 

Installation:


Directories:
andromeda/				: Dource/Include locations
ATest/					: Deprecated. Gut for new tests
bin/					: Binaries
build/					: Project Files
Debug/					: Intermediate files
Docs/					: General Random Notes / Documentation
extern/					: Optional 3rd party location
include/				: DEPRECATED: Gut for replacement
res/					: Resources
resource/				: Resources
src/					: DEPRECATED: Gut for replacement
test/					: New Test Environment

TODO: REmove all project files once the new system is up and running
		
		

TODO: (Overview)
2018
- CMake 								[-] (In Progress)
	- Project Structure					[-] (In Progress)
	- Library Linking					[-] (In Progress)
	- Test Project						[-] (In Progress)
	- Full Library Rebuild				[ ]
- Review 2016 TODOS						[ ]
- Rebuild SceneGraph for 2.5D only		[ ]

2016
- Resource Management overhaul			[ ]
- File Management/Loading				[ ]
- Texture Annotations					[ ]
- Shader Annotations					[ ]
- Abstract OpenGL						[ ]
- XML Helper Library					[ ]
- zLib Support							[ ]
- RocketLib Support						[ ]
- Change ALL header include gates		[ ]








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
 - Version 1.67.0

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
