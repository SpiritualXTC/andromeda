#include "andromeda_windows.h"

// Library Includes
#include <andromeda/andromeda.h>
#include <andromeda/Engine/display.h>
#include <andromeda/Engine/engine.h>
#include <andromeda/Engine/system.h>

#include <andromeda/Renderer/context.h>

#include <andromeda/Input/keyboard.h>
#include <andromeda/Input/mouse.h>

#include <andromeda/Utilities/log.h>




// Platform Dependant Library Includes
#include "Engine/display_windows.h"
#include "Renderer/context_windows.h"
#include "Platform/platform_windows.h"

/*
	TODO:
	Fix up the graphics initialiser / headers
*/
#include <opengl/graphics_gl.h>




using namespace andromeda;
using namespace andromeda::windows;


















/*
	Initialise the Engine Under Windows
*/
Boolean andromeda::initialise(HINSTANCE hInstance)
{
	// Setup the Platform Config
	AndromedaConfigWindows config(hInstance);

	// Initialise Andromeda
	Andromeda::initialise(&config);

	return true;
}






/*

*/
AndromedaConfigWindows::AndromedaConfigWindows(HINSTANCE hInstance)
	: _hInstance(hInstance)
{

}


/*
	Configure the resource management
*/
void AndromedaConfigWindows::init()
{
	// Old Method
//	std::shared_ptr<CommonResourceScan> search = std::make_shared<CommonResourceScan>();
//	resources->addSearch(search);

	// TODO: Clean this up
	// Add Root Directory as a location ?
}


/*

*/
std::shared_ptr<Display> AndromedaConfigWindows::initDisplay(const DisplayParameters & dp)
{
	return std::make_shared<DisplayWindows>(dp);
}


/*
	Create Platform
*/
std::shared_ptr<Platform> AndromedaConfigWindows::initPlatform()
{
	_platform = std::make_shared<PlatformWindows>(_hInstance);

	_hWnd = _platform->getHWND();
	_hDC = _platform->getHDC();
	
	return _platform;
}


/*
	Create Context
*/
std::shared_ptr<Context> AndromedaConfigWindows::initContext()
{
	return std::make_shared<ContextWindows>(_hDC);
}

/*
	Create Graphics

	TODO:
	Determine whether the context should create the Graphics or NOT.
*/
std::shared_ptr<Graphics> AndromedaConfigWindows::initGraphics()
{
	return std::make_shared<GraphicsOpenGL>();
}
