#include <andromeda/Renderer/view.h>

#include <glm/gtc/constants.hpp>

#include <andromeda/Game/camera.h>
#include <andromeda/Game/camera_component.h>
#include <andromeda/Game/camera_static.h>
#include <andromeda/Game/camera_target.h>
#include <andromeda/Game/game_object.h>
#include <andromeda/Game/transform_component.h>

#include <andromeda/graphics.h>

#include <andromeda/Renderer/layer.h>
#include <andromeda/Renderer/projection.h>
#include <andromeda/Renderer/renderable.h>
#include <andromeda/Renderer/scene_graph_cache.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
View::View(const std::shared_ptr<ISceneGraph> sceneGraph, std::shared_ptr<IProjection> projection, Float x, Float y, Float width, Float height, Int32 order)
	: _sceneGraph(sceneGraph)
	, _projection(projection)
	, _zOrder(order)
{
	assert(_sceneGraph);

	// Create Region
	_view = Region2f({ x, y }, { width + x, height + y });

	// Create Default Projection
	if (! _projection)
		_projection = std::make_shared<ProjectionPerspective>();

	// Create a default Layer [Temporary]
	log_warn("Creating default layer");
	_layers["default"] = std::make_unique<Layer>("");

	// Create Scene Graph Cache
	_sceneGraphCache = std::make_shared<SceneGraphCache>(this);

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
	// Viewport Attributes
	Int32 left = _display.minimum.x;
	Int32 top = _display.minimum.y;
	Int32 width = _display.maximum.x - _display.minimum.x;
	Int32 height = _display.maximum.y - _display.minimum.y;

	// Flip Top to Bottom, offset by height
	Int32 bottom = _screen.maximum.y - top;
	bottom -= height;

	// Create a Default Camera
	if (!_camera)
		setCameraTarget();

	// Camera
	assert(_camera);
	_camera->calculate();

	// Set Viewport
	glViewport(left, bottom, width, height);

	// Render the Scene from this View
	// The view does need to pass some information to the scene, such as target object.
	// Target Object


	// THE RENDER TARGET NEEDS TO DO SHIT HERE



	// Process the SceneGraph. Nullptr here is bad! lol
	// But Current scenerio, it doesn't matter
	//_scene->process(nullptr, _sceneGraphCache);
	_sceneGraphCache->process(nullptr, _sceneGraph);


	// Loop through layers
	for (const auto & layer : _layers)
	{
		// Get Active Technique Name : Should the View or the Scene manage the active technique?
		// As multiple view points may manage a scene....probably the view should
		std::string technique = "default";// view->getActiveTechniqueName();


		// Render the Layer
		layer.second->render(_projection, _camera, technique);
	}



	// THE RENDER TARGET NEEDS TO CLEAN SHIT UP HERE

}






/*
	Set Camera Target using a default Camera
*/
Boolean View::setCameraTarget()
{
	// Create a Camera
	_camera = std::shared_ptr<CameraStatic>(new CameraStatic());

	return !! _camera;
}

/*
	Set Camera Target using a GameObject. GameObject must be in the SceneGraph
*/
Boolean View::setCameraTarget(const std::string & name)
{
	// Look for the Object in the SceneGraph
	std::shared_ptr<GameObject> go = _sceneGraph->getGameObject(name);

	// Validate
	if (!go) return false;

	// Look for CameraComponent
	std::shared_ptr<ICamera> camera = go->getComponentPtr<CameraComponent>();

	if (!camera)
	{
		// Look for TransformComponent
		std::shared_ptr<ITransform> transform = go->getComponentPtr<TransformComponent>();

		if (transform)
		{
			// Create a Target Camera
			camera = std::make_shared<CameraTarget>(transform);
		}
	}

	return setCameraTarget(camera);
}

/*
	Set Camera Target using a Custom Camera
*/
Boolean View::setCameraTarget(std::shared_ptr<ICamera> & camera)
{
	_camera = camera;

	return !!_camera;
}

