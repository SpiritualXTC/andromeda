#ifndef _ANDROMEDA_GRAPHICS_SCENE_GRAPH_H_
#define _ANDROMEDA_GRAPHICS_SCENE_GRAPH_H_

#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>

#include <andromeda/glm.h>

#include <andromeda/stddef.h>

#include "renderable.h"

namespace andromeda
{
	// Forward Declarations
	class ITransform;
	class GameObject;
	class SceneGraphCache;


	/*
		this shouldnt be an interface, but an abstract class with pure virtual functions
	*/
	class SceneGraph
	{
	public:
		SceneGraph() {}
		virtual ~SceneGraph() {}

		virtual std::shared_ptr<GameObject> getGameObject(const std::string & name) = 0;

		virtual Boolean hasObject(const std::string & name) = 0;
		virtual Boolean hasObject(std::shared_ptr<GameObject> object) = 0;


		virtual Boolean addGameObject(std::shared_ptr<GameObject> object) = 0;
		virtual Boolean removeGameObject(const std::string & name) = 0;
		virtual Boolean removeGameObject(std::shared_ptr<GameObject> object) = 0;

		virtual const Int32 getObjectCount() const = 0;

	

		virtual std::shared_ptr<GameObject> operator[](const char * const name) = 0;

		virtual void update(const Float timeStep) = 0;

		virtual Boolean process(std::shared_ptr<SceneGraphCache> sgCache) = 0;
	};




}


#endif