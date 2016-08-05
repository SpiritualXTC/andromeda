#pragma once

/*
	andromeda_main.h:
		This file should only be included in an applications main.h as it defines the application specific engines' entry point

*/

#include <boost/predef.h>


/*
	Macro Definations used in this file.

	ANDROMEDA_USE_SDL
		Tells andromeda to attempt to load SDL instead of the platform specific

	ANDROMEDA_PLATFORM_FOUND
		Specifies when a platform is found
*/



/*
	Selects the Specific Andromeda Platform Header
*/


// Check for "Special" Implementations
#if defined(ANDROMEDA_USE_SDL)
// SDL

#endif





/*
	Define engine entry point
*/
#if !defined(ANDROMEDA_PLATFORM_FOUND)

/* Windows */
#if BOOST_OS_WINDOWS
// Windows

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