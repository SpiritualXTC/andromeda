#include <andromeda/Renderer/context.h>

#include <cassert>
#include <thread>
#include <chrono>

#include <andromeda/Engine/system.h>
#include <andromeda/opengl.h>

#include <andromeda/Utilities/log.h>




using namespace andromeda;


/*

*/
Context::Context(std::weak_ptr<System> system) : Module(Module::Render , Module::Lowest)
{
	log_verbose("Context: Create");

	assert(!system.expired());
	addDependancy<System>(system);



}


/*

*/
Context::~Context()
{
	log_verbose("Context: Destroy");
}


/*

*/
void Context::update()
{
	// Currently a pretty insane tearing issue when in fullscreen/borderless mode.
	// But only when running with teh Intel HD 4000. 
	// The AMD X9 appears to work fine.

	swap();
}



