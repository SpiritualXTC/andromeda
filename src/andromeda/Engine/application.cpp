#include <andromeda/Engine/application.h>

#include <cassert>

#include <andromeda/andromeda.h>
#include <andromeda/Engine/engine.h>
#include <andromeda/Engine/system.h>
#include <andromeda/Utilities/timing.h>

using namespace andromeda;


/*

*/
Application::Application()
	: Module(Module::Update)
{

}


/*

*/
Application::~Application()
{

}





/*

*/
void Application::update()
{
	// Get Timer
	std::shared_ptr<Timing> & timing = Andromeda::instance()->getTiming();

	assert(timing);

	// Get Frametime
	Double ft = timing->frametime();

	// Update the Application
	update(ft);
}