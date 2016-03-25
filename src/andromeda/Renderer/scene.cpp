#include <andromeda/Renderer/scene.h>

#include <cassert>

#include <andromeda/Renderer/scene_graph.h>
#include <andromeda/Renderer/view.h>

using namespace andromeda;


/*

*/
Scene::Scene(const std::string & name, std::shared_ptr<ISceneGraph> sceneGraph)
	: _name(name)
	, _sceneGraph(sceneGraph)
{
	assert(_sceneGraph);

}


/*

*/
Scene::~Scene()
{

}




/*

*/
std::shared_ptr<View> Scene::addScreenView(const std::string & name, Float x, Float y, Float width, Float height, Int32 order)
{
	// Create the View
	std::shared_ptr<View> view = std::make_shared<ScreenView>(_sceneGraph, x, y, width, height, order);

	// Add the View
	Boolean b = addView(view);
	
	// Validate
	if (!b) return nullptr;

	// Return the View
	return view;
}


/*

*/
Boolean Scene::addTextureView(const std::string & name, const Int32 texWidth, const Int32 texHeight)
{
	std::shared_ptr<View> view = std::make_shared<TextureView>(_sceneGraph);

	return addView(view);;
}



/*

*/
Boolean Scene::addView(std::shared_ptr<View> view)
{
	assert(view);

	// Create some Dummy Views	
	_views.insert(view);

	return true;
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
	assert(_sceneGraph);

	_sceneGraph->update(timeStep);
}



/*
	sync():
*/
void Scene::sync()
{
	assert(_sceneGraph);

}



/*
	render():
*/
void Scene::render()
{
	// Loop through all views!
	for (auto view : _views)
	{
		// Render the View
		view->render();
	}

}