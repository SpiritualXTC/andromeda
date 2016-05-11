#include <andromeda/Renderer/view.h>

#include <glm/gtc/constants.hpp>

#include <andromeda/graphics.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/camera_builder.h>
#include <andromeda/Renderer/layer.h>
#include <andromeda/Renderer/projection.h>
#include <andromeda/Renderer/scene_graph.h>
#include <andromeda/Renderer/scene_graph_cache.h>
#include <andromeda/Renderer/visibility.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
View::View(const std::shared_ptr<SceneGraph> sceneGraph, std::shared_ptr<IProjection> projection, std::shared_ptr<IVisibility> visibility, Float x, Float y, Float width, Float height, Int32 order)
	: _sceneGraph(sceneGraph)
	, _projection(projection)
	, _visibility(visibility)
	, _zOrder(order)
{
	assert(_sceneGraph);
	assert(_zOrder != View::_ZOrder::Target);

	// Create Region
	_view = Region2f({ x, y }, { width + x, height + y });

	// Create Default Projection
	if (! _projection)
		_projection = std::make_shared<ProjectionPerspective>();

	// Create a default Layer [Temporary]
	log_warn("Creating default layer");
	_layers["default"] = std::make_unique<Layer>("");

	// Create Scene Graph Cache
	_sceneGraphCache = std::make_shared<SceneGraphCache>(this, _visibility.get());

	// Create the Camera
	setCameraTarget();
}

/*

*/
View::~View()
{

}




/*

*/
Boolean View::addRenderable(const std::string & layer, IRenderable * renderable)
{
	// TODO: ReWrite this function
	
	// ADD TO ALL LAYERS
	for (const auto & layer : _layers)
		layer.second->addRenderable(renderable);


	return false;
}

/*

*/
Boolean View::removeRenderable(const std::string & layer, IRenderable * renderable)
{
	// TODO: ReWrite this function

	// ADD TO ALL LAYERS
	for (const auto & layer : _layers)
		layer.second->removeRenderable(renderable);

	return false;
}



/*
	resize():

	Resize the Viewport
*/
void View::resize(const Int32 width, const Int32 height)
{
	// Must have projection matrix
	assert(_projection);

	// Set Screen Dimensions
	_screen.minimum = glm::ivec2(0, 0);
	_screen.maximum = glm::ivec2(width, height);

	// Recalculate Screen Region
	glm::fvec2 screen(width, height);

	_display.minimum = _view.minimum * screen;
	_display.maximum = _view.maximum * screen;

	// Recalculate Projection
	glm::fvec2 display(_display.size());

	_projection->calculate(display.x, display.y);

	return;
}

/*
	render():

	Render the View
*/
void View::render()
{
	assert(_sceneGraph);

	// Viewport Attributes
	Int32 left = _display.minimum.x;
	Int32 top = _display.minimum.y;
	Int32 width = _display.maximum.x - _display.minimum.x;
	Int32 height = _display.maximum.y - _display.minimum.y;

	// Flip Top to Bottom, offset by height
	Int32 bottom = _screen.maximum.y - top;
	bottom -= height;



	// THE RENDER TARGET NEEDS TO DO SHIT HERE
	// IViewTarget Interface
	//IViewTarget->begin();

	// Set Viewport
	glViewport(left, bottom, width, height);

	// Camera
	assert(_camera);
	_camera->calculate();

	if (_visibility)
		_visibility->update(_projection, _camera);








	// Process the SceneGraph :: With respect to the Camera and the SceneGraphCache
	_sceneGraph->process(_sceneGraphCache);


	// Render layers
	for (const auto & layer : _layers)
	{
		// Render the Layer
		layer.second->render(_projection, _camera);
	}



	// THE RENDER TARGET NEEDS TO CLEAN SHIT UP HERE
	// IViewTarget Interface
	//IViewTarget->end();

}






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

