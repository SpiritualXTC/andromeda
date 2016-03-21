

TODO:
- Make a Complete TODO List :)

- zLib Support
- Break the mega-library up into chunks. Something like:
	AndromedaCore			: Platform Agnostic
	AndomredaSDL			: SDL Implementation [HAHA]
	AndromedaWindows		: Windows Functionality
	AndromedaAndroid		: Android Functionality
	AndromedaGL				: OpenGL Functionality shared across multiple platforms (Not sure if it would be needed)
	AndromedaCL				: OpenCL Functionality shared across multiple platforms
	AndromedaFX				: NVFX Wrapper (This may be too "hard-wired")
	AndromedaZLib			: ZLib support via a wrapper that taps into the virtual resource management
 


Particle System
 - GPU & CPU implementations
	(and obviously a common interface)
	
Resource Management
 - Better loading mechanisms 
 - Better functionality for dealing with resource streams
 - Binary Support in file system
 - Virtual Stream Support


DEPENDANCIES:
glew
 - Required for Windows (Maybe others)

glm
 - Required

boost
 - Required

nvFX
 - Currently Required
 - 3rd party shader library (May NOT compile on Android)
 - Many many many bugs
  - Might try and fix bugs, and compile a new version from source...
 - An alternative solution built around an interface used by the nvFX wrapper may be a good idea -- especially for Android

SDL
 - Not used

SOIL
 - Currently Required
 - Loads images
 - Look for an alternative (maybe)

zLib
 - Not used


Directories:

include/				: Root Include Directory
include/andromeda		: Root Directory for Andromeda Includes

src/					: Root Directory for Andromeda Source
src/andromeda			: Andromeda Source
src/common				: Andromeda Source with "common-use" platform dependant code
src/windows				: Andromeda Source with windows specific code 