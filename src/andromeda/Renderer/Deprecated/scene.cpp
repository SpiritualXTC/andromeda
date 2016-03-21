#include <andromeda/Renderer/scene.h>

#include <cassert>

#include <andromeda/Game/game_object.h>
#include <andromeda/Game/transform.h>
#include <andromeda/Game/transform_component.h>
#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/layer.h>
#include <andromeda/Renderer/scene_graph.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


#if 0
/*

*/
Scene::Scene()
{

}
#endif

/*

*/
Scene::Scene(std::shared_ptr<ISceneGraph> sceneGraph)
	: _sceneGraph(sceneGraph)
{
	assert(_sceneGraph);
	
	// Create a default Layer
	log_warn("Creating default layer");
	_layers["default"] = std::make_shared<Layer>("");
}

/*

*/
Scene::~Scene()
{

}



/*
	temp function
*/
Boolean Scene::addGameObject(std::shared_ptr<GameObject> object)
{
	assert(_sceneGraph);

	Boolean b = _sceneGraph->addGameObject(object);

	// Add to each layer :: TEMP
	for (auto layer : _layers)
		layer.second->addRenderable(object->getRenderable());

	return b;
}


/*
	temp function
*/
Boolean Scene::removeGameObject(std::shared_ptr<GameObject> object)
{
	assert(_sceneGraph);
	
	Boolean b = _sceneGraph->removeGameObject(object);

	// Remove from each layer :: TEMP
	for (auto layer : _layers)
		layer.second->removeRenderable(object->getRenderable());

	return b;
}





/*

*/
Boolean Scene::render(std::shared_ptr<IProjection> projection, std::shared_ptr<Camera> camera)
{
	// NEED TO KNOW SOMETHING ABOUT THE VIEW THAT IS DRAWING THE SCENE
	
	const std::string ACTIVE_CAMERA_NAME = "temporary";

	

	// Get Active Camera from View
//		int camera = _cameras[ACTIVE_CAMERA_NAME];

	std::shared_ptr<ITransform> transform = nullptr;

	// Get Reference to Camera Target
	std::shared_ptr<GameObject> target = (*_sceneGraph)["camera"];	// Pull this from the View

	if (target)
	{
		// Get Transform Component of the Target
		std::shared_ptr<TransformComponent> transform_component = target->getComponentPtr<TransformComponent>();

		// Cast to transform object
		transform = std::static_pointer_cast<ITransform>(transform_component);


		// ADVANCED VERSION...
		// Look for CameraComponent instead
	}

	






// TODO
	// Scan Game Objects :: Determine whether it can be rendered or not :: build list of rendered game objects
	// Determine what renderables need to be added to what layer
	// Look for SceneComponent :)

#if 0


	// Loop through all layers
	for (const auto layer : _layers)
	{
		// Get Active Technique Name : Should the View or the Scene manage the active technique?
		// As multiple view points may manage a scene....probably the view should
		std::string technique = "default";// view->getActiveTechniqueName();

		// Render the Layer
		layer.second->render(projection, camera, technique);
	}
#endif
	
	return true;
}