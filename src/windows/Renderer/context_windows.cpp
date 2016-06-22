#include "context_windows.h"

#include <cassert>

#include <andromeda/Engine/system.h>
#include <andromeda/opengl.h>

#include <andromeda/Utilities/log.h>


#include "../Platform/platform_windows.h"

using namespace andromeda;
using namespace andromeda::windows;


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
	pfd.cDepthBits = 32;
	
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

	// Initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		log_errp("Context :: <init>() :: Failed to initalise GLEW\n");
	}

	// OpenGL Version
	const GLubyte *oglv = glGetString(GL_VERSION);

	log_debugp("Context :: <init>() :: OpenGL Version %1%", oglv);
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