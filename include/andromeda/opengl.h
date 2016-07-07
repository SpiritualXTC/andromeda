#ifndef _ANDROMEDA_GRAPHICS_OPENGL_H_
#define _ANDROMEDA_GRAPHICS_OPENGL_H_

/*
	Selects which OpenGL Libraries to include!

	TODO:
	This shouldn't be here :)
*/



#include <boost/predef.h>



/* Windows */
#if BOOST_OS_WINDOWS
/* Windows Support */
#include <gl/glew.h>


#endif



/* Android */
#if BOOST_OS_ANDROID
/* Android Support */
#endif


/* Linux */
#if BOOST_OS_LINUX
/* Linux Support */
#endif


#endif