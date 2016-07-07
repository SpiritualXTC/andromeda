

TODO:
- Finish the TODO List :)
- XML Helper Library (XML is loaded via Boost into a Boost::property_tree)
 - Implement so it could be JSON friendly as well
- zLib Support
- Break the mega-library up into chunks:
	AndromedaCore			: Platform Agnostic
	AndomredaSDL			: SDL "Platform" Implementation (HAHA - Ezy Mode)
	AndromedaWindows		: Windows Functionality
	AndromedaAndroid		: Android Functionality
	AndromedaGL				: OpenGL Functionality shared across multiple platforms (TODO)
	AndromedaCL				: OpenCL Functionality shared across multiple platforms (TODO)
	AndromedaFX				: NVFX Wrapper (This may be too "hard-wired")
	AndromedaXEffect		: XML Effect/Shader System
	AndromedaZLib			: ZLib support via a wrapper that taps into the virtual resource management
 
 - Change ALL header include gates to '#pragma once' rather than the old style gates

 - Setup Forward Declaration style
	class XYZ {};
	typdef andromeda::XYZ a_XYZ;



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

nvFX (Process of removing this library -- its buggy AF and undocumented)
 - Currently Required
 - 3rd party shader library (May NOT compile on Android)
 - Many many many bugs
  - Might try and fix bugs, and compile a new version from source...
 - An alternative solution built around an interface used by the nvFX wrapper may be a good idea -- especially for Android
 - Considering removing due to bugs... and rolling my own :(
  - First gen will be based on an XML structure (Currently in Progress)

SDL (Remove)
 - Used by a temporary testing framework


SOIL (Look for an alternative)
 - Currently Required
 - Loads images
 - Doesn't like loading from images memory for some file types?

zLib
 - Not used yet
