#ifndef _ANDROMEDA_RENDERER_SCENE_GRAPH_BASIC_H_
#define _ANDROMEDA_RENDERER_SCENE_GRAPH_BASIC_H_


#include <unordered_map>

#include "scene_graph.h"

namespace andromeda
{
	/*
		A Very basic Scene Graph
	*/
	class BasicSceneGraph : public ISceneGraph
	{
	public:
		BasicSceneGraph();
		virtual ~BasicSceneGraph();

		std::shared_ptr<GameObject> getGameObject(const std::string & name) override;

		Boolean hasObject(const std::string & name) override;
		Boolean hasObject(std::shared_ptr<GameObject> object) override;

		Boolean addGameObject(std::shared_ptr<GameObject> object) override;
		Boolean removeGameObject(const std::string & name) override;
		Boolean removeGameObject(std::shared_ptr<GameObject> object) override;

		const Int32 getObjectCount() const override
		{
			return _objects.size();
		}



//		Boolean process(std::shared_ptr<ITransform> transform, std::shared_ptr<ISceneGraph> sgCache);


		// OBJECT RETRIEVAL :: TESTING
		std::shared_ptr<GameObject> operator[](const char * const name) override
		{
			return getGameObject(name);
		}


		void for_each(std::function<void(std::shared_ptr<GameObject>)> cb) override;


		/*
			Update all the objects in the scene
		*/
		void update(const Float timeStep) override;


	private:
		std::unordered_map<std::string, std::shared_ptr<GameObject>> _objects;
	};
}

#endif
