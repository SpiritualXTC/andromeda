#include "engine.h"

#include <common/log.h>

#include "module.h"

using namespace andromeda;


Engine::Engine() :
	_running(false)
{

}

Engine::~Engine()
{

}

Boolean Engine::run()
{
	_running = open();
	if (!_running)
		log_err("Engine :: Unable to Open");

	_running &= resume();
	if (!_running)
		log_err("Engine :: Unable to Resume");

	log_debug("Engine :: Running");

	while (_running)
	{
		update();
	}
	log_debug("Engine :: Stopping");

	pause();

	if (!close())
	{
		log_err("Engine :: Unable to Close");
		return false;
	}

	return true;
}

Boolean Engine::quit()
{
	_running = false;
	return true;
}


Boolean Engine::insert(ClassId id, std::shared_ptr<IModule> m)
{
	assert(m);

	if (exists(id))
		return false;
	_modules.insert({ id, m });
	return exists(id);
}

Boolean Engine::exists(ClassId id)
{
	return _modules.find(id) != _modules.end();
}

std::shared_ptr<IModule> Engine::find(ClassId id)
{
	auto result = _modules.find(id);
	return result == _modules.end() ? nullptr : result->second;
}





Boolean Engine::open()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->open();

	return b;
}

Boolean Engine::close()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->close();
	return b;
}

Boolean Engine::resume()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->resume();
	return b;
}

Boolean Engine::pause()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->pause();
	return b;
}

Boolean Engine::update()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->update();
	return b;
}




#if 0



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
	stop();

	_active.clear();
	_map.clear();
	

	log_debugp("Engine :: <destroy>()");
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
	stop();

	// Debug Output
	debugOutput();

	log_verbose("Engine :: run() :: Stopped");
}

/*
	isActive():

	Searches for the System in the active list
*/
Boolean Engine::isRunning(std::shared_ptr<IModuleOLD> system)
{
	return std::find(_active.begin(), _active.end(), system) != _active.end();
}

Boolean Engine::start(std::shared_ptr<IModuleOLD> module)
{
	assert(module);

	Boolean b = module->onOpen();
	if (b)
		b &= resume(module);
	return b;
}

/*
	Starts all the Modules
*/
void Engine::resume()
{
	log_warn("Engine :: resume()");

	// Iterate through all Modules
	for (auto it : _map)
		resume(it.second);
}

/*
	Resumes the Module
*/
Boolean Engine::resume(std::shared_ptr<IModuleOLD> module)
{
	assert(module);

	// Resume the Module
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
void Engine::pause()
{
	log_infop("Engine :: pause() :: Stop = %1%", _running);

	// Iterate through all modules
	for (auto it : _map)
		pause(it.second);
}

/*
	pause():

	Stops the Module.
*/
Boolean Engine::pause(std::shared_ptr<IModuleOLD> module)
{
	assert(module);
	
	// Pause the Module :: Successful pause will remove from active module list
	if (module->onPause())
		_active.erase(module);

	// Is it in the Running List? System Modules can't be paused
	return ! isRunning(module);
}

/*

*/
void Engine::stop()
{
	log_debugp("Engine :: quit()");
	if (_running)
	{
		// Leave it for the next iteration
		_running = false;
		return;
	}

	for (auto it : _map)
		stop(it.second);
}

/*

*/
Boolean Engine::stop(std::shared_ptr<IModuleOLD> module)
{
	assert(module);
	pause(module);
	return module->onClose();
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

#endif