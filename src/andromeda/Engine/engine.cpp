#include <andromeda/Engine/engine.h>

#include <cassert>
#include <algorithm>
#include <chrono>


#include <andromeda/Engine/config.h>
#include <andromeda/Engine/module.h>
#include <andromeda/Engine/system.h>
#include <andromeda/Graphics/renderer.h>
#include <andromeda/Utilities/timing.h>


#include <andromeda/Utilities/log.h>

// These are only here so, the engine can assign dependancies to the sytem automagically.
#include <andromeda/Graphics/context.h>
#include <andromeda/Platform/platform.h>




using namespace andromeda;


/*

*/
Engine::Engine()
{
	log_verbose("Engine: Created");

	// Create Configuration Module
	addModule<Config>();
	
	// Create System Module : (Running Configuration)
	addModule<System>(std::make_shared<System>(this, getModulePtr<Config>()));

	// Create Timing
	addModule<Timing>();

	// Create ResourceManager



	// Add the Renderer
	addModule<Renderer>();
}



/*

*/
Engine::~Engine()
{
	// Unregister Events
	pause(true);

	_active.clear();
	_modules.clear();



	log_verbose("Engine: Destroyed");
}


/*

*/
void Engine::quit()
{
	_running = false;
}


/*

*/
void Engine::run()
{
	_running = true;


	log_verbose("Engine: Running");

	
	// Additional Dependancies!
	setDependancy<System, Platform>();
	setDependancy<System, Context>();


	// Start all System Components
	resume();

	// Output all active modules!
	for (auto it : _active)
		log_verbose("Module: ", it->priority());
	
	// Loop
	while (_running)
	{
		for (auto module : _active)
			module->update();	
	}

	log_verbose("Engine: Stopping");

	// Stop all System Components
	pause(true);

	log_verbose("Engine: Stopped");
}




/*
	isActive():

	Searches for the System in the active list
*/
Boolean Engine::isRunning(std::shared_ptr<IModule> system)
{
	return std::find(_active.begin(), _active.end(), system) != _active.end();
}




/*
	Starts all the Modules
*/
void Engine::resume()
{
	// Loop through all Installed Modules
	for (auto it : _modules)
		resume(it.second);

	for (auto it : _modules)
	{
		log_warn("Module: ", it.second->priority(), isRunning(it.second));
	}
}



/*
	Pause all the Modules
*/
void Engine::pause(Boolean stop)
{
	/*
		This is to stop a crash while trying to remove elements from the list during an iteration!
	*/

	// Duplicate the Array
	std::multiset<std::shared_ptr<IModule>> copy = _active;

	// Loop through all Active Modules in the duplicate array
	for (auto it : copy)
		pause(it, stop);

	// Clear duplicate array
	copy.clear();
}




/*
	Starts the Module
*/
Boolean Engine::resume(std::shared_ptr<IModule> module)
{
	assert(module);

	// The module is already running. Don't resume it :)
//	if (isRunning(module))
//		return false;

	// Resume the Component
	module->onResume();

	// Insert the Module into the Running List
	if (! isRunning(module))
		_active.insert(module);

	// Verify it is in the Running List?
	return isRunning(module);
}

/*
	Stops the Module
*/
Boolean Engine::pause(std::shared_ptr<IModule> module, Boolean stop)
{
	assert(module);

	// The module isn't running. Don't try to pause it :)
	if (!isRunning(module))
		return false;

	// Pause the Module
	module->onPause();

	// Remove from List: System Modules cannot be removed unless they are being stopped. (IE Removed/Uninstalled, whatever)
	// They remain in the List, to do kernel/system level updates(). (Such as the Message Pump, in Windows)
	if (!module->isSystem() || stop)
		_active.erase(module);

	// Is it in the Running List?
	return !isRunning(module);
}


