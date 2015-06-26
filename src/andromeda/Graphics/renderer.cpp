#include <andromeda/Graphics/renderer.h>

#include <cassert>

#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>

#include <andromeda/Graphics/opengl.h>
#include <andromeda/Graphics/renderable.h>
#include <andromeda/Graphics/render_list.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
Renderer::Renderer() : Module(Module::Render)
{
	log_verbose("Renderer: Create");

	
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
Boolean Renderer::addRenderable(std::shared_ptr<IRenderable> renderable)
{
	assert(renderable);

	Int32 group = renderable->group();

	// Create the Render List
	if (_renderLists[group] == nullptr)
	{
		_renderLists[group] = std::make_shared<RenderList>(group);
	}

	// Add the Renderable
	return _renderLists[group]->addRenderable(renderable);
}

/*

*/
Boolean Renderer::removeRenderable(std::shared_ptr<IRenderable> renderable)
{
	assert(renderable);

	Boolean b = false;
	Int32 group = renderable->group();

	// Group Doesn't Exist. Just Ignore It :)
	if (_renderLists[group] == nullptr)
		return false;

	std::shared_ptr<RenderList> list = _renderLists[group];

	// Remove Renderable
	b = list->removeRenderable(renderable);

	// Delete List ?
	if (list->size() == 0)
		_renderLists[group] = nullptr;

	return b;
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
		view->render(_renderLists[view->group()]);
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
Boolean Renderer::onResize(ResizeEventArgs & e)
{
	//glViewport(0, 0, e.displayWidth, e.displayHeight);

	// Send resize info to views
	for (auto view : _views)
		view->resize(e.displayWidth, e.displayHeight);

	log_event("ON_RESIZE: ", e.displayWidth, e.displayHeight);

	return true;
}
