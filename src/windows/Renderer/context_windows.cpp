#include "context_windows.h"

#include <cassert>

#include <andromeda/Engine/system.h>
#include <andromeda/opengl.h>

#include <andromeda/Utilities/log.h>

#include <gl\wglext.h>

#include "../Platform/platform_windows.h"

using namespace andromeda;
using namespace andromeda::windows;



bool WGLExtensionSupported(const char *extension_name) 
{
	PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

	_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

	if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL) 
	{
		return false;
	}

	return true;
}













/*

*/
ContextWindows::ContextWindows(HDC hDC)
	: _hDC(hDC)
{
	log_debugp("Context :: <init>() :: Windows OpenGL");
	
	// Select a Pixel Format
	PIXELFORMATDESCRIPTOR pfd;
	memset((void*)&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	
	
	pfd.iLayerType = PFD_MAIN_PLANE;

	// Choose Pixel Format
	Int32 format = ChoosePixelFormat(_hDC, &pfd);

	// Set Pixel Format
	SetPixelFormat(_hDC, format, &pfd);

	// Create GL Context
	_hGL = wglCreateContext(_hDC);
	if (!_hGL)
	{
		log_errp("Context :: <init>() :: Failed to initalise OpenGL\n");
	}

	wglMakeCurrent(_hDC, _hGL);



	// Additional Extensions
	PFNWGLSWAPINTERVALEXTPROC       wglSwapIntervalEXT = NULL;
	PFNWGLGETSWAPINTERVALEXTPROC    wglGetSwapIntervalEXT = NULL;

	if (WGLExtensionSupported("WGL_EXT_swap_control"))
	{
		// Extension is supported, init pointers.
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

		// this is another function from WGL_EXT_swap_control extension
		wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");


		wglSwapIntervalEXT(0);
	}






	// Initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		log_errp("Context :: <init>() :: Failed to initalise GLEW\n");
	}

	// OpenGL Version
	const GLubyte *oglv = glGetString(GL_VERSION);

	log_debugp("Context :: <init>() :: OpenGL Version %1%", oglv);


	/*
		TODO:
		Put some functionality for querying values into the Graphics API :)

		Version, Color/Depth/Stencil Bits, Driver, etc
	*/
	GLint depthBits = 0;
	GLint stencilBits = 0;

	glGetIntegerv(GL_DEPTH_BITS, &depthBits);
	glGetIntegerv(GL_STENCIL_BITS, &stencilBits);

	log_debugp("OpenGL Information");
	log_tree();
	log_debugp("Depth = %1%", depthBits);
	log_debugp("Stencil = %1%", stencilBits);
}

/*

*/
ContextWindows::~ContextWindows()
{
	// Disable Open GL
	wglMakeCurrent(_hDC, NULL);

	if (_hGL)
		wglDeleteContext(_hGL);

	_hGL = NULL;

	log_verbosep("Context :: <destroy>() :: Windows OpenGL Context Destroyed");
}

/*

*/
void ContextWindows::swap()
{
	SwapBuffers(_hDC);
}