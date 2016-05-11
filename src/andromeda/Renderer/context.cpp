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
Context::Context() : Module(Module::Render , Module::Lowest)
{
	log_verbosep("Context :: <init>();");
}


/*

*/
Context::~Context()
{
	log_verbosep("Context :: <destroy>();");
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



