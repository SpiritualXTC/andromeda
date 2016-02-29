#include "context_windows.h"

#include <cassert>

#include <andromeda/Engine/system.h>
#include <andromeda/opengl.h>

#include <andromeda/Utilities/log.h>


#include "../Platform/platform_windows.h"


// Libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib, "glew32.lib")



using namespace andromeda;

ContextWindows::ContextWindows(std::weak_ptr<System> system, std::weak_ptr<PlatformWindows> platWin) : Context(system)
{
	log_verbose("Context: Windows OpenGL");
	

	assert(! platWin.expired());

	_hDC = platWin.lock()->getHDC();


	// Select a Pixel Format
	PIXELFORMATDESCRIPTOR pfd;
	memset((void*)&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;


	// Choose Pixel Format
	Int32 format = ChoosePixelFormat(_hDC, &pfd);

	// Set Pixel Format
	SetPixelFormat(_hDC, format, &pfd);

	// Create GL Context
	_hGL = wglCreateContext(_hDC);
	if (!_hGL)
	{
		//A_LOGD(": GL Failure\n");
	}

	wglMakeCurrent(_hDC, _hGL);


	// Initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		//A_LOGD("> Failed to initalise GLEW\n");
	}



	// OpenGL Version

	//A_LOGD("> OpenGL Version: %s\n", oglv);
	const GLubyte *oglv = glGetString(GL_VERSION);
}


ContextWindows::~ContextWindows()
{
	// Disable Open GL
	wglMakeCurrent(_hDC, NULL);

	if (_hGL)
		wglDeleteContext(_hGL);

	_hGL = NULL;

	log_verbose("Windows OpenGL Context Destroyed");
}


void ContextWindows::swap()
{
	SwapBuffers(_hDC);
}