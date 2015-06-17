#include <andromeda/platform/platform.h>

#include <cassert>

#include <andromeda/Engine/system.h>
#include <andromeda/Events/event_manager.h>

#include <andromeda/Input/keyboard.h>
#include <andromeda/Input/mouse.h>

#include <andromeda/Platform/platform.h>

using namespace andromeda;


/*

*/
Platform::Platform(std::weak_ptr<System> system) : Module(Module::Critical, Module::High, true)
{
	log_verbose("Platform: Create");

	// Add System Dependancy
	assert(!system.expired());
	addDependancy<System>(system);

	// Register Events
	
}

/*

*/
Platform::~Platform()
{
	log_verbose("Platform: Destroy");
}



/*

*/
void Platform::close()
{
	std::shared_ptr<System> system = getDependancyPtr<System>();

	if (system)
		system->close();

	return;
}


/*

*/
void Platform::activate()
{
	std::shared_ptr<System> system = getDependancyPtr<System>();
	if (system)
		system->resume();
	return;
}

/*

*/
void Platform::deactivate()
{
	std::shared_ptr<System> system = getDependancyPtr<System>();
	if (system)
		system->pause();
}








/*

*/
void Platform::resize(Int32 width, Int32 height)
{
	// Resize the System!
	std::shared_ptr<System> system = getDependancyPtr<System>();

	if (system)
		system->changeDisplaySettings(width, height);
}


/*

*/
void Platform::keyDown(Int8 key)
{
	std::shared_ptr<Keyboard> kb = getDependancyPtr<Keyboard>();

	if (kb)
		kb->keyDown(key);

}

/*

*/
void Platform::keyUp(Int8 key)
{
	std::shared_ptr<Keyboard> kb = getDependancyPtr<Keyboard>();

	if (kb)
		kb->keyUp(key);
}