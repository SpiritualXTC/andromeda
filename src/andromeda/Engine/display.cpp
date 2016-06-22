#include <andromeda/Engine/display.h>

#include <andromeda/Engine/system.h>

#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>

#include <andromeda/Platform/platform.h>

using namespace andromeda;

/*

*/
Display::Display(const DisplayParameters & dp)
	: _display(dp)
{
	registerEvent<ResizeEventArgs>(Display::Resize);

	_displayWidth = dp.resolution.width;
	_displayHeight = dp.resolution.height;
}


/*

*/
Display::~Display()
{
	unregisterEvent<ResizeEventArgs>(Display::Resize);
}



/*

*/
Boolean Display::getDisplayFormat(Int32 & width, Int32 & height)
{
	width = _displayWidth;
	height = _displayHeight;

	return true;
}



/*

*/
Boolean Display::changeDisplaySettings(const DisplayParameters & dp)
{
	Boolean result = true;


	// TODO
	// Resolution Changes should ONLY take effect when switching between Windowed/Borderless and Fullscreen
	// Not, when changing b/w Windowed & Not Windowed

#if 0
	// Change Screen Resolution ?
	if (_display.mode != DisplayMode::Windowed && dp.mode == DisplayMode::Windowed)
	{
		// Borderless/Fullscreen to Windowed
		// TODO: Restore Previous Native Resolution
		result = restoreScreenResolution();
	}
	else if (_display.mode == DisplayMode::Windowed && dp.mode != DisplayMode::Windowed)
	{
		// Windowed to Borderless/Fullscreen
		// Change Screen Resolution

		result = changeScreenResolution(dp.resolution.width, dp.resolution.height);
	}
	else if (_display.mode != DisplayMode::Windowed && dp.mode != DisplayMode::Windowed)
	{
		// Borderless/Fullscreen to Borderless/Fullscreen
		// Change Screen Resolution
		result = changeScreenResolution(dp.resolution.width, dp.resolution.height);
	}
	else
	{
		// Windowed to Windowed
		// Do Nothing
	}
#endif


	// Failed to change Screen Resolution
	if (!result)
		return false;



	// Update Display Parameters
	_display = dp;

	// TODO: resize() is currently called when the OS/Platform notify()'s the display when the window itself is resized
	// Call here anyway. It just means that resize() MAY get called twice with some settings.
	if (_display.mode != DisplayMode::Windowed)
	{
		resize(_display.resolution.width, _display.resolution.height);
	}

	return true;
}






/*
	
*/
void Display::notify(const Platform * const platform)
{
	if (_display.mode == DisplayMode::Windowed)
	{
		Int32 width;
		Int32 height;

		// Get Client Resolution
		platform->getClientResolution(width, height);

		// Resize
		resize(width, height);
	}
}



/*

*/
Boolean Display::resize(Int32 width, Int32 height)
{
	log_debugp("Display :: resize() :: %1%x%2%", width, height);

	// Oh Shit
	if (width == 0 || height == 0)
	{
		log_errp("Oh Shit");
		return false;
	}

	// Update Internal Display Resolution
	_displayWidth = width;
	_displayHeight = height;

	// Dispatch Event
	ResizeEventArgs e;
	e.displayWidth = _displayWidth;
	e.displayHeight = _displayHeight;

	andromeda::dispatch<ResizeEventArgs>(Display::Resize, e);

	return true;
}