#include <andromeda/Renderer/renderer.h>

#include <cassert>

#include <andromeda/Events/event_manager.h>
#include <andromeda/Events/resize.h>

#include <andromeda/opengl.h>
#include <andromeda/Renderer/renderable.h>
#include <andromeda/Renderer/scene.h>
#include <andromeda/Renderer/scene_graph.h>\


#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
Renderer::Renderer() : Module(Module::Render)
{
	log_verbose("Renderer: Create");

	// Default States
	glEnable(GL_DEPTH_TEST);	
}



/*

*/
Renderer::~Renderer()
{
	log_verbose("Renderer: Destroy");
}

#if 0
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
#endif



/*
	addScene():
*/
Boolean Renderer::addScene(std::shared_ptr<Scene> scene)
{
	assert(scene);

	// Check if a scene with the matching name exists already
	if (hasScene(scene->getName()))
		return false;

	// Add Scene
	_scenes[scene->getName()] = scene;


	// Check whether it was added
	return hasScene(scene->getName());
}


/*
	removeScene():
*/
Boolean Renderer::removeScene(const std::string & name)
{
	
	// Check if a Scene with the matching name exists 
	if (!hasScene(name))
		return false;

	// Remove Scene
	_scenes.erase(name);

	// Check whether it was removed
	return hasScene(name);
}

/*
	removeScene():
*/
Boolean Renderer::removeScene(std::shared_ptr<Scene> scene)
{
	assert(scene);

	return removeScene(scene->getName());
}




/*
	hasScene():

	The Renderer Has the Scene
*/
Boolean Renderer::hasScene(const std::string & name)
{ 
	return _scenes.find(name) != _scenes.end(); 
}


/*
	getScene():

	Gets the scene with the matching name
*/
std::shared_ptr<Scene> Renderer::getScene(const std::string & name)
{
	// Check for the Scene
	if (!hasScene(name))
		return nullptr;

	// Return the Scene
	return _scenes[name];
}






/*

*/
void Renderer::update()
{

	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);

	//GL_STENCIL_BUFFER_BIT
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render All Scenes
	for (const auto scene : _scenes)
		scene.second->render();

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


