#include <andromeda/Graphics/renderer.h>

#include <cassert>

#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>

#include <andromeda/Graphics/opengl.h>
#include <andromeda/Graphics/renderable.h>
#include <andromeda/Graphics/render_list.h>
#include <andromeda/Graphics/scene_graph.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
Renderer::Renderer() : Module(Module::Render)
{
	log_verbose("Renderer: Create");

	
	_sceneGraph = std::make_shared<SceneGraph>();
}



/*

*/
Renderer::~Renderer()
{
	log_verbose("Renderer: Destroy");
}


/*
	addView():
*/
Boolean Renderer::addView(std::shared_ptr<View> view)
{
	// Create some Dummy Views	
	_views.insert(view);

	return true;
}

/*
	removeView():
*/
Boolean Renderer::removeView(std::shared_ptr<View> view)
{
	_views.erase(view);
	return true;
}

/*
	clearViews():
*/
Boolean Renderer::clearViews()
{
	_views.clear();
	return true;
}


/*

*/
Boolean Renderer::addRenderable(Int32 group, std::shared_ptr<IRenderable> renderable)
{
	assert(renderable);

	return _sceneGraph->addRenderable(group, renderable);
}

/*

*/
Boolean Renderer::removeRenderable(Int32 group, std::shared_ptr<IRenderable> renderable)
{
	assert(renderable);

	return _sceneGraph->removeRenderable(group, renderable);
}



/*

*/
Boolean Renderer::clearRenderables()
{
	_renderLists.clear();
	return true;
}





/*

*/
void Renderer::update()
{

	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

	//GL_STENCIL_BUFFER_BIT
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Loop through all views!
	for (auto view : _views)
	{
		// Render the View
		view->render(_sceneGraph);
	}

	// Swapping is handled by the context module :)


	errorCheck();
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
		log_err("GL Error: ", gluErrorString(err));
	}
}


/*

*/
Boolean Renderer::onResize(ResizeEventArgs & e)
{
	//glViewport(0, 0, e.displayWidth, e.displayHeight);

	// Send resize info to views
	for (auto view : _views)
		view->resize(e.displayWidth, e.displayHeight);

	log_event("ON_RESIZE: ", e.displayWidth, e.displayHeight);

	return true;
}
