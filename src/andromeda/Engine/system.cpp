#include <andromeda/Engine/system.h>

#include <cassert>

#include <andromeda/andromeda.h>

#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>
#include <andromeda/Platform/platform.h>

#include <andromeda/Utilities/log.h>


using namespace andromeda;

// TODO: Move the Resize event to Display



/*

*/
System::System(IAndromedaConfig * config)
{
	log_verbosep("System :: <init>();");




	// Register System Events
	registerEvent<CloseEventArgs>(System::Close);
	registerEvent<ResizeEventArgs>(System::Resize);
	registerEvent<AppEventArgs>(System::Pause);
	registerEvent<AppEventArgs>(System::Resume);

	
	// Get Configuration Settings Relevant to the System
	DisplayParameters displayParam;

	// DEFAULT Configuration for the Display
	displayParam.resolution.width = 800;
	displayParam.resolution.height = 600;
	displayParam.mode = DisplayMode::Windowed;


	// TEMP
//	_displayParam = displayParam;


	// Create Display
	_display = config->initDisplay(displayParam);

	// Create Platform
	_platform = config->initPlatform();


	_platform->add(_display);

	assert(_platform);


	// Create Input Devices

	// Create Context
	_context = config->initContext();
	assert(_context);

	// TODO: Throw Exceptions for Required Elements (Platform, System, Display, Context, etc)
}


/*

*/
System::~System()
{
	// Unregister System Events
	unregisterEvent<AppEventArgs>(System::Resume);
	unregisterEvent<AppEventArgs>(System::Pause);
	unregisterEvent<ResizeEventArgs>(System::Resize);
	unregisterEvent<CloseEventArgs>(System::Close);

	log_verbosep("System: Destroyed");
}



/*

*/
Boolean System::changeDisplaySettings(DisplayParameters & dp)
{
	/*
		TODO:

		Restructure how display settings is done...

		// Changes Screen Resolution
		setFullscreen(int width, int height, int bpp, int freq);

		// Has ZERO effect on Screen Resolution : Unless switching from Fullscreen in which case it needs to restore resolution
		setWindowed(int width, int height, bool borderless);

		// DisplayMode is essentially pointless

		isBorderless()	: True if Borderless
		isFullscreen()	: True if Borderless Windowed OR Fullscreen (?)
		isExclusive()	: True if Fullscreen (?)
	*/



	log_warnp("System :: Change Display Settings");

	// Change Display Settings for the display
	
	Boolean result = true;
	


	// Get Current Screen Resolution
	Int32 screenWidth = 0;
	Int32 screenHeight = 0;

	_display->getScreenResolution(screenWidth, screenHeight);



	// Modify Params if needed!

	//
	if (dp.mode != DisplayMode::Windowed)
	{
		// Borderless
		// Fullscreen

		// Use Native Resolution
		if (dp.resolution.width == 0 || dp.resolution.height == 0)
		{

			// Use Current Screen Resolution for the Updated Settings
			dp.resolution.width = screenWidth;
			dp.resolution.height = screenHeight;
		}
	}



	// Change Display Settings Using Adjusted Parameters
	result &= _display->changeDisplaySettings(dp);

	// Change Dimensions of the window
	if (result)
	{
		result &= _platform->changeWindowSettings(dp, screenWidth, screenHeight);
	}

	return result;
}


#if 0
/*

*/
Boolean System::changeDisplaySettings(const DisplayParameters & dp)
{
	log_warn("System :: changeDisplaySettings() DEPRECATED function in use");

	Boolean b = true;

//	std::shared_ptr<Platform> platform = getDependancyPtr<Platform>();

	b = _platform->changeDisplaySettings(dp);
	
	// Update Stored DisplayParameters
	if (b)
	{
		log_debug("Display Settings have updated");
		_displayParam = dp;
	}

	// Fire off Resize Event
	dispatchResizeEvent();

	return b;
}
#endif


/*
	init():


*/
Boolean System::init()
{
	log_debugp("System :: run();");

	assert(_platform);

	if (!_platform)
		return false;


	// Show the Platform
	_platform->show();

	// Send initial resize event!
	//dispatchResizeEvent();

	// TEMPORARY :: May or may NOT be needed
	_display->notify(_platform.get());

	return true;
}


/*
	destroy():


*/
Boolean System::destroy()
{
	// Restore Display Resolution
	_display->restoreScreenResolution();

	return true;
}




/*
	I NEED FIXING :(
*/
Boolean System::close()
{
	log_warn("System :: close() DEPRECATED function in use");

	CloseEventArgs e;
	e.cancel = false;

	// Send the Close Event
	dispatch<CloseEventArgs>(System::Close, e);


	if (!e.cancel)
	{
		// Quit 
		Andromeda::instance()->quit();
	}
	else
		log_warn("Quitting was cancelled");

	return true;
}
