#include <andromeda/Engine/system.h>

#include <cassert>

#include <andromeda/Engine/engine.h>
#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>
#include <andromeda/Platform/platform.h>

#include <andromeda/Utilities/log.h>


using namespace andromeda;



/*

*/
System::System(Engine * engine, std::weak_ptr<Module<Config>> config) 
	: Module(Module::Idle, Module::Lowest, true)
	, _engine(engine)
{
	assert(! config.expired());
	assert(_engine);

	log_verbose("System: Created");

	

	// Add the Dependancy
	addDependancy<Config>(config);

	// Get Configuration Settings Relevant to the System
	_display.format.width = 800;
	_display.format.height = 600;
	_display.mode = DisplayMode::Windowed;



	registerEvent<CloseEventArgs>(System::Close);
	registerEvent<ResizeEventArgs>(System::Resize);
	registerEvent<AppEventArgs>(System::Pause);
	registerEvent<AppEventArgs>(System::Resume);
}


/*

*/
System::~System()
{
	// Unregister Events
	unregisterEvent<AppEventArgs>(System::Resume);
	unregisterEvent<AppEventArgs>(System::Pause);
	unregisterEvent<ResizeEventArgs>(System::Resize);
	unregisterEvent<CloseEventArgs>(System::Close);

	log_verbose("System: Destroyed");
}




/*

*/
Boolean System::enumerateDisplaySettings(std::set<DisplayFormat> & displayModes)
{
	std::shared_ptr<Platform> platform = getDependancyPtr<Platform>();

	return platform->enumerateDisplaySettings(displayModes);
}


/*

*/
Boolean System::getDisplayResolution(Int32 & width, Int32 & height)
{
	std::shared_ptr<Platform> platform = getDependancyPtr<Platform>();

	if (platform == nullptr)
		return false;

	return _display.mode == DisplayMode::Windowed ? platform->getClientResolution(width, height) : platform->getScreenResolution(width, height);
}

/*

*/
Boolean System::changeDisplaySettings(Int width, Int32 height)
{
	DisplayParameters dp = _display;
	
	dp.format.width = width;
	dp.format.height = height;

	return changeDisplaySettings(dp);
}

/*

*/
Boolean System::changeDisplaySettings(Int width, Int32 height, DisplayMode mode)
{
	DisplayParameters dp = _display;

	// Adjust Width ?
	if (width)
		dp.format.width = width;

	// Adjust Height
	if (height)
		dp.format.height = height;

	// Always Adjust Mode
	dp.mode = mode;

	return changeDisplaySettings(dp);
}


/*

*/
Boolean System::changeDisplaySettings(DisplayMode mode)
{
	DisplayParameters dp = _display;

	// Currently is Windowed. Changing to something else!
	// _display.mode == DisplayMode::Windowed &&
	
	// Mode is being changed to something that isn't Windowed. Make sure the resolution is valid.
	// Set to Current Resolution
	if (mode != DisplayMode::Windowed)
	{
		log_warn("Mode is being changed from windowed to non-windowed, and no resolution is set.");
		log_warn("Resolution is being adjusted to Native!");

		Int32 width = 0;
		Int32 height = 0;

		std::shared_ptr<Platform> platform = getDependancyPtr<Platform>();

		platform->getScreenResolution(width, height);

		dp.format.width = width;
		dp.format.height = height;
	}

	// New Display Mode
	dp.mode = mode;

	return changeDisplaySettings(dp);
}



/*

*/
Boolean System::changeDisplaySettings(DisplayFormat format)
{
	DisplayParameters dp = _display;

	dp.format = format;

	return changeDisplaySettings(dp);
}


/*

*/
Boolean System::changeDisplaySettings(const DisplayParameters & dp)
{
	Boolean b = true;

	std::shared_ptr<Platform> platform = getDependancyPtr<Platform>();

	b = platform->changeDisplaySettings(dp);
	
	// Update Stored DisplayParameters
	if (b)
	{
		log_debug("Display Settings have updated");
		_display = dp;
	}

	// Fire off Resize Event
	dispatchResizeEvent();

	return b;
}


/*
	
*/
Boolean System::updateDisplaySettings()
{
	return true;
}


/*
	
*/
Boolean System::run()
{
	std::shared_ptr<Platform> platform = getDependancyPtr<Platform>();

	if (!platform)
		return false;


	// Show the Platform
	platform->show();

	// Send initial resize event!
	dispatchResizeEvent();

	return true;
}


/*

*/
Boolean System::quit()
{
	_engine->quit();
	return true;
}




/*

*/
Boolean System::close()
{
	CloseEventArgs e;
	e.cancel = false;

	// Send the Close Event
	dispatch<CloseEventArgs>(System::Close, e);


	if (!e.cancel)
	{
		// Quit 
		_engine->quit();		
	}
	else
		log_warn("Quitting was cancelled");

	return true;
}


/*

*/
Boolean System::pause()
{
	log_warn("System::Pause()");

	_engine->pause(false);

	AppEventArgs e;
	
	dispatch<AppEventArgs>(System::Pause, e);

	return true;
}

/*

*/
Boolean System::resume()
{
	log_warn("System::Resume()");
	_engine->resume();



	AppEventArgs e;

	dispatch<AppEventArgs>(System::Resume, e);

	return true;
}



/*

*/
void System::dispatchResizeEvent()
{
	ResizeEventArgs e;

	// Retrieving Display Resolution Failed. Platform Probably not assigned yet.
	// Don't dispatch event
	if (!getDisplayResolution(e.displayWidth, e.displayHeight))
		return;

	// Dispatch Event
	dispatch<ResizeEventArgs>(System::Resize, e);
}

