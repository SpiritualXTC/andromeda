#include <andromeda/platform/platform.h>

#include <cassert>

#include <andromeda/andromeda.h>
#include <andromeda/Engine/system.h>
#include <andromeda/Events/event_manager.h>

#include <andromeda/Input/keyboard.h>
#include <andromeda/Input/mouse.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
Platform::Platform()
	: Module(Module::Critical, Module::High, true)
{
	log_verbosep("Platform: Create");

	
}

/*

*/
Platform::~Platform()
{
	log_verbosep("Platform: Destroy");
}














/*

*/
void Platform::close()
{
	std::shared_ptr<System> system = Andromeda::instance()->getSystem();

	if (system)
		system->close();

	return;
}




/*

*/
void Platform::resize(Int32 width, Int32 height)
{
	log_errp("Platform :: Resize :: %1%x%2%", width, height);


	// Resize the System!
	notify(this);


//	std::shared_ptr<System> system = Andromeda::instance()->getSystem();

//	if (system)
//		system->changeDisplaySettings(width, height);
}






/*

*/
void Platform::activate()
{
	Andromeda::instance()->resume();

	return;
}

/*

*/
void Platform::deactivate()
{
	Andromeda::instance()->pause();
}

















