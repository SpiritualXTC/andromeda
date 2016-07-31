#include <andromeda/Renderer/scene.h>

#include <cassert>

#include <andromeda/Renderer/scene_graph.h>
#include <andromeda/Renderer/view.h>

using namespace andromeda;


/*

*/
Scene::Scene(const std::string & name, std::shared_ptr<SceneGraph> sceneGraph)
	: _name(name)
{

	// Adds a scene graph if one is passed in
	if (sceneGraph)
		addSceneGraph(sceneGraph);
}


/*

*/
Scene::~Scene()
{

}



/*
	Adds a SceneGraph
*/
Boolean Scene::addSceneGraph(const std::shared_ptr<SceneGraph> & sg, const std::string & groupName)
{
	assert(sg);

	_graphs[groupName] = sg;

	return true;
}





#if 0
/*

*/
std::shared_ptr<View> Scene::addScreenView(const std::string & name, Float x, Float y, Float width, Float height, Int32 order)
{
	// Create the View
	std::shared_ptr<View> view = std::make_shared<ScreenView>(x, y, width, height, order);

	// Add the View
	Boolean b = addView(view);
	
	// Validate
	if (!b) return nullptr;

	// Return the View
	return view;
}
#endif


/*

*/
std::shared_ptr<View> Scene::addView(std::shared_ptr<View> view)
{
	assert(view);

	// Insert the View
	_views.insert(view);

	return view;
}


/*

*/
Boolean Scene::removeView(std::shared_ptr<View> view)
{
	assert(view);

	_views.erase(view);
	return true;
}


/*
	clearViews():
*/
Boolean Scene::clearViews()
{
	_views.clear();
	return true;
}




/*
	update():
*/
void Scene::update(const Float timeStep)
{
	// If the scene isn't enabled, do not update
	// If the scene is paused, do not update
	if (!_enabled || _paused) return;

	// Update Scene Graph
	for (const auto & it : _graphs)
		it.second->update(timeStep);
}


#if 0
/*
	sync():
*/
void Scene::sync()
{
	assert(_sceneGraph);

}
#endif


/*
	render():
*/
void Scene::render()
{
	// If the scene isn't enabled, do not draw
	if (!_enabled) return;

	// Loop through all views!
	for (auto view : _views)
	{
		// Render the View
		view->render();
	}
}







