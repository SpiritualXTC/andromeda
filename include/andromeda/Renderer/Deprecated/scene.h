#ifndef _ANDROMEDA_RENDERER_SCENE_H_
#define _ANDROMEDA_RENDERER_SCENE_H_

#include <memory>
#include <unordered_map>
#include <vector>


#include <andromeda/glm.h>

#include <andromeda/stddef.h>

#include "renderable.h"
#include "scene_graph.h"

namespace andromeda
{
	class GameObject;
	class ISceneGraph;
	class Layer;
	class Camera;

	class IProjection;


	/*
		New Scene Implementation

		Contains the scene in it's entirety,
		whether its renderered or not

		....
		And it doesn't look like it's needed ....
	*/
	class Scene
	{
	public:
	//	Scene();
		Scene(std::shared_ptr<ISceneGraph> sceneGraph);
		virtual ~Scene();




		// Adds an Object to the Scene Graph
		Boolean addGameObject(std::shared_ptr<GameObject> object);

		// Removes an Object from the Scene Graph
		Boolean removeGameObject(std::shared_ptr<GameObject> object);

		// Get Number of Objects in the Scene Graph
		Int32 getObjectCount() { return !! _sceneGraph ? _sceneGraph->getObjectCount() : -1; }

		// Render the Scene // TEMPORARY
		Boolean render(std::shared_ptr<IProjection> projection, std::shared_ptr<Camera> camera);	





	private:

		// Reference to the SceneGraph
		std::shared_ptr<ISceneGraph> _sceneGraph;			// Reference to the SceneGraph for this scene



		// Layers for this Scene
		std::unordered_map<std::string, std::shared_ptr<Layer>> _layers;		// Visual Style Layers
															// Create Default Layer using default shader
															// Special Systems will need to auto create their own layers (such as particle effects)
															// Might be possible to override the Layer class ?
	};
}

#endif
