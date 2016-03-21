#include <andromeda/Renderer/view.h>

#include <glm/gtc/constants.hpp>

#include <andromeda/Game/camera.h>


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

	// Create a Camera
	_camera = std::shared_ptr<Camera>(new Camera());

	// Create a default Layer [Temporary]
	log_warn("Creating default layer");
	_layers["default"] = std::make_unique<Layer>("");

	// Create Scene Graph Cache
	_sceneGraphCache = std::make_shared<SceneGraphCache>(this);
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


