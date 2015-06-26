#include <andromeda/Game/application.h>

#include <cassert>

#include <andromeda/Engine/engine.h>
#include <andromeda/Engine/system.h>
#include <andromeda/Graphics/renderer.h>
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
	std::shared_ptr<Timing> timing = getDependancyPtr<Timing>();

	assert(timing);

	Double ft = timing->frametime();

	update(ft);
}