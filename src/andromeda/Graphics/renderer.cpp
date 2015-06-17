#include <andromeda/Graphics/renderer.h>

#include <cassert>

#include <andromeda/Events/event_manager.h>
#include <andromeda/Graphics/opengl.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
Renderer::Renderer() : Module(Module::Render)
{
	bind<ResizeEventArgs>(System::Resize, std::bind(&Renderer::resize, this, std::placeholders::_1));


	
	_views.insert(std::make_shared<View>());
	_views.insert(std::make_shared<View>());
}



/*

*/
Renderer::~Renderer()
{

}


/*

*/
void Renderer::update()
{
	Float r = (rand() % 100) / 100.0f;
	Float g = (rand() % 100) / 100.0f;
	Float b = (rand() % 100) / 100.0f;

	glClearColor(r, g, b, 1.0f);

	//GL_STENCIL_BUFFER_BIT
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Loop through all views!
	for (auto view : _views)
	{

	}

	// Swapping is handled by the context module :)
}


/*
	Check for OpenGL Errors
*/
void Renderer::errorCheck()
{
	Int32 err = 0;

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		// Send error message to log :)
		log_warn("GL Error: ", gluErrorString(err));
	}
}



/*

*/
Boolean Renderer::resize(ResizeEventArgs & e)
{
	glViewport(0, 0, e.displayWidth, e.displayHeight);

	log_warn("RESIZE: ", e.displayWidth, e.displayHeight);

	return true;
}