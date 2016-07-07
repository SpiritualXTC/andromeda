#include <andromeda/Renderer/view.h>

#include <glm/gtc/constants.hpp>

#include <andromeda/graphics.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/layer.h>
#include <andromeda/Renderer/layer_group.h>
#include <andromeda/Renderer/projection.h>
#include <andromeda/Renderer/scene_graph.h>
#include <andromeda/Renderer/scene_graph_view_cache.h>

#include <andromeda/Utilities/log.h>



#include "render_group.h"

using namespace andromeda;

/*

*/
View::View(Float x, Float y, Float width, Float height, Int32 order)
	: _zOrder(order)
{
	assert(_zOrder != View::_ZOrder::Target);

	// Set the Region
	_view = Region2f({ x, y }, { width + x, height + y });

	// TODO: Fix Meh
	// Create a dummy/default Render Group ? 
	// It might be beneficial for this to always be here.
	// Render Groups are now automatically created as they are required
//	addRenderGroup("");
}


/*

*/
View::~View()
{

}







/*
	Adds a LayerGroup
*/
Boolean View::addLayerGroup(const std::string & groupName, const std::shared_ptr<SceneGraph> & sg)
{
	// Search for a LayerGroup with the same name
	const auto & it = _layerGroups.find(groupName);
	if (it != _layerGroups.end())
		return false;

	// Create LayerGroup
	std::shared_ptr<LayerGroup> lg = std::make_shared<LayerGroup>(groupName, sg, this);

	// Add LayerGroup
	_layerGroups[groupName] = lg;

	return true;
}



/*
	Gets the RenderGroup
*/
std::shared_ptr<RenderGroup> View::getRenderGroup(const std::string & group)
{
	// Find the Group
	const auto & it = _renderGroups.find(group);

	// Found ??
	if (it != _renderGroups.end())
	{
		// Retrieve
		return it->second;
	}

	// Create and Insert
	std::shared_ptr<RenderGroup> rg = std::make_shared<RenderGroup>(group);
	_renderGroups[group] = rg;

	return rg;
}


/*
	Gets the LayerGroup
*/
std::shared_ptr<LayerGroup> View::getLayerGroup(const std::string & group)
{
	std::shared_ptr<LayerGroup> g;

	// Find the Group
	const auto & it = _layerGroups.find(group);

	// Found ??
	return it == _layerGroups.end() ? nullptr : it->second;
}





/*
	Adds a Layer to the View
*/
Boolean View::addLayer(const std::string & layerName, std::shared_ptr<Effect> effect, const std::string & technique, const std::string & layerGroup, const std::string & renderGroup)
{
	/*
		TODO:
		Change the Layers to an ordered_map.
		The KEY is the layerName, and order it by the layers zOrder
	*/

	std::shared_ptr<RenderGroup> rg = getRenderGroup(renderGroup);
	std::shared_ptr<LayerGroup> lg = getLayerGroup(layerGroup);

	assert(rg);
	assert(lg);


	// Create Layer
	std::unique_ptr<Layer> layer = std::make_unique<Layer>(lg->getCamera(), effect, rg);

	_layers[layerName] = std::move(layer);

	return true;
}



/*

*/
Boolean View::addRenderable(IRenderable * renderable, const std::string & group)
{
	// Gets the Group
	std::shared_ptr<RenderGroup> rg = getRenderGroup(group);

	assert(rg);

	// Add Renderable
	rg->addRenderable(renderable);

	return true;
}

/*

*/
Boolean View::removeRenderable(IRenderable * renderable, const std::string & group)
{
	// Gets the Group
	std::shared_ptr<RenderGroup> rg = getRenderGroup(group);

	assert(rg);

	// Remove Renderable
	rg->removeRenderable(renderable);

	return true;
}



/*

*/
std::shared_ptr<Camera> & View::getCamera(const std::string & layerGroup)
{ 
	const auto & it = _layerGroups.find(layerGroup);

	if (it == _layerGroups.end())
		throw std::exception();

	return it->second->getCamera();
}



/*

*/
void View::clear()
{
	// Clear all Layers. This needs to be done first!
	_layers.clear();

	// Clear all LayerGroups
	_layerGroups.clear();

	// Clear all RenderGroups
	_renderGroups.clear();
}







/*
	resize():

	Resize the Viewport
*/
void View::resize(const Int32 width, const Int32 height)
{
	// Must have projection matrix
//	assert(_camera);

	// Set Screen Dimensions
	_screen.minimum = glm::ivec2(0, 0);
	_screen.maximum = glm::ivec2(width, height);

	// Recalculate Screen Region
	glm::fvec2 screen(width, height);

	_display.minimum = _view.minimum * screen;
	_display.maximum = _view.maximum * screen;





	// OLD CAMERA
	// Recalculate Projection
	glm::fvec2 display(_display.size());


	// NEW CAMERA
	// Resize the new Camera
//	_camera->resize(display.x, display.y);

	for (const auto & it : _layerGroups)
		it.second->getCamera()->resize(display.x, display.y);

	return;
}

/*
	render():

	Render the View
*/
void View::render()
{
//	assert(_camera);
//	assert(_sceneGraph);


	/*
		This should be an automatic component of the Graphics API when setting a weighted viewport
	*/
	// Viewport Attributes
	Int32 left = _display.minimum.x;
	Int32 top = _display.minimum.y;
	Int32 width = _display.maximum.x - _display.minimum.x;
	Int32 height = _display.maximum.y - _display.minimum.y;

	// Flip Top to Bottom, offset by height
	Int32 bottom = _screen.maximum.y - top;
	bottom -= height;


	/*
		TODO: 
		ReAdd support for RenderTargets
		Do this after texturing is working and back in place :D
	*/

	
	// THE RENDER TARGET NEEDS TO DO SHIT HERE
	// IViewTarget Interface
	//IViewTarget->begin();

	// Set Viewport
	glViewport(left, bottom, width, height);
	// graphics()->setViewport(left, bottom, width, height);





	// TODO: Update LayerGroups
	// Layer groups contain the camera, for all the layers


	// Update Camera Position
//	_camera->update();

	// Process the SceneGraph :: With respect to the Camera and the SceneGraphViewCache
//	_sceneGraph->process(_camera, _sceneGraphViewCache);



	// Update Layer Groups
	for (const auto & lg : _layerGroups)
	{
		lg.second->render();
	}


	// Draw the Layers
	for (const auto & layer : _layers)
	{
		layer.second->render();
	}



	// Render layers
//	for (const auto & layer : _layers)
//	{
		// Render the Layer
	//	layer.second->render(_camera);

	//	layer.second->render(_projection, _camera);
//	}



	// THE RENDER TARGET NEEDS TO CLEAN SHIT UP HERE
	// IViewTarget Interface
	//IViewTarget->end();


	//TODO:
	// Investigate how this will work for a cube texture being used for a reflection map
	// Each SIDE would technically have its own camera -- but those cameras would all share the same source camera, but may be perpendicular to the source camera
}





#if 0
/*
	Set Camera Target using a default Camera
*/
Boolean View::setCameraTarget()
{
	return setCameraTarget(CameraBuilder().create());
}

/*
	Set Camera Target using a GameObject. GameObject must be in the SceneGraph
*/
Boolean View::setCameraTarget(const std::string & name)
{
	// Look for the Object in the SceneGraph
	std::shared_ptr<GameObject> go = _sceneGraph->getGameObject(name);

	if (!go)
		return false;

	// Create the Camera
	std::shared_ptr<ICamera> camera = CameraBuilder().create(go);

	if (camera)
		return setCameraTarget(camera);

	return false;
}

/*
	Set Camera Target using a Custom Camera
*/
Boolean View::setCameraTarget(std::shared_ptr<ICamera> & camera)
{
	assert(camera);

	_camera = camera;

	return !!_camera;
}
#endif
