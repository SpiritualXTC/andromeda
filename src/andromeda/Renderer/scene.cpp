#include <andromeda/Renderer/scene.h>

#include <cassert>

#include <andromeda/Renderer/scene_graph.h>
#include <andromeda/Renderer/view.h>
#include <andromeda/Renderer/visibility.h>

using namespace andromeda;


/*

*/
Scene::Scene(const std::string & name, std::shared_ptr<SceneGraph> sceneGraph)
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
Boolean Scene::addLayer(const std::string & group, std::shared_ptr<Effect> & effect)
{
	/*
		TODO: Layer Groups
	*/
	_layerGroup.effect = effect;

	return true;
}


/*

*/
std::shared_ptr<View> Scene::addScreenView(const std::string & name, Float x, Float y, Float width, Float height, Int32 order)
{
	// Create the Visibility Object :: TEMP
	std::shared_ptr<IVisibility> visibility = std::make_shared<VisibilityRegion>();

	// Create the View
	std::shared_ptr<View> view = std::make_shared<ScreenView>(_sceneGraph, nullptr, visibility, x, y, width, height, order);

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


	// Add Layers

	/*
		TODO:
		Layer Groups
	*/

	log_warn("Scene :: addView() :: Adding Primitive Layers");
	view->addLayer(_layerGroup.name, _layerGroup.effect);


	// Insert the View
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