#include <andromeda/Engine/engine.h>

#include <cassert>
#include <algorithm>

#include <andromeda/Engine/module.h>

#include <andromeda/Utilities/log.h>




using namespace andromeda;


/*

*/
Engine::Engine()
{
	log_verbose("Engine :: <init>()");
}



/*

*/
Engine::~Engine()
{
	// Unregister Events
	pause(true);

	_active.clear();
	_map.clear();
	

	log_debugp("Engine :: <destroy>()");
}


/*

*/
void Engine::stop()
{
	log_debugp("Engine :: quit()");
	_running = false;
}


/*

*/
void Engine::run()
{
	log_debugp("Engine :: run()");

	// Debug Output
	debugOutput();
	
	// Loop
	_running = true;
	while (_running)
	{
		// Update the Module
		for (auto module : _active)
			module->update();	
	}

	log_verbose("Engine :: run() :: Stopping");

	// Stop all Modules
	pause(true);

	// Debug Output
	debugOutput();

	log_verbose("Engine :: run() :: Stopped");
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
	log_warn("Engine :: resume()");


	// Loop through all Installed Modules
	for (auto it : _map)
		resume(it.second);
}








/*
	Starts the Module
*/
Boolean Engine::resume(std::shared_ptr<IModule> module)
{
	assert(module);

	// The module is already running. Don't resume it :)
	// This option doesn't really work well as System Modules, once added are ALWAYS running until they are stopped
//	if (isRunning(module) && ! module->isSystem())
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
Pause all the Modules
*/
void Engine::pause(Boolean stop)
{
	log_infop("Engine :: pause() :: Stop = %1%", stop);

	/*
		This is to stop a crash while removing elements from the list while iterating
	*/

	// Duplicate the Active Array
	std::multiset<std::shared_ptr<IModule>> copy = _active;

	// Loop through all Active Modules in the duplicated array
	for (auto it : copy)
		pause(it, stop);

	// Clear duplicate array
	copy.clear();
}


/*
	pause():

	Stops the Module.
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

	// Stop the Module
	if (stop)
	{
		module->onStop();
	}

	// Is it in the Running List?
	// System Modules will return false on this call...
	return !isRunning(module);
}


/*

*/
void Engine::debugOutput()
{
	log_infop("All Modules");
	for (auto it : _map)
	{
		log_warnp("Module :: Priority = %1%, Running = %2%", it.second->priority(), isRunning(it.second));
	}
}

