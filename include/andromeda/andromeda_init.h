#pragma once

/*
	andromeda_main.h:
		This file should only be included in an applications main.h as it defines the application specific engine entry point


	Macro Definations used in this file.

	ANDROMEDA_USE_SDL
		Tells andromeda to attempt to load SDL instead of the platform specific

	ANDROMEDA_PLATFORM_FOUND
		Specifies when a platform is found
*/

#include <memory>

#include <boost/predef.h>

#include <andromeda/stddef.h>


namespace andromeda
{
	// Forward Declarations
	class Context;
	class Display;
	class Graphics;
	class Platform;
	
	struct DisplayParameters;


	/*
		Class used to initialise the engine
	*/
	class IAndromedaConfig
	{
	public:
		virtual void init() = 0;

		virtual std::shared_ptr<Display> initDisplay(const DisplayParameters & dp) = 0;
		virtual std::shared_ptr<Platform> initPlatform() = 0;
		virtual std::shared_ptr<Context> initContext() = 0;
		virtual std::shared_ptr<Graphics> initGraphics() = 0;
	};
}



/*
	Selects the Specific Andromeda Platform Header
*/


// Check for SDL Implementation Flag
#if defined(ANDROMEDA_USE_SDL)
// TODO:
// Setup an SDL2 Initialisation Path


#define ANDROMEDA_PLATFORM_FOUND
#endif





/*
	Define engine entry point
*/
#if !defined(ANDROMEDA_PLATFORM_FOUND)

/* Windows */
#if BOOST_OS_WINDOWS
// Windows
#include <Windows.h>
namespace andromeda
{
	Boolean initialise(HINSTANCE hInstance);
}


#define ANDROMEDA_PLATFORM_FOUND
#endif



/* Android */
#if BOOST_OS_ANDROID
// Android

#define ANDROMEDA_PLATFORM_FOUND
#endif


/* Linux */
#if BOOST_OS_LINUX
// Linux

#define ANDROMEDA_PLATFORM_FOUND
#endif

#endif







/*
	Unsupported Platform
*/
#if !defined(ANDROMEDA_PLATFORM_FOUND)
// Do An error or some such thing here
#endif