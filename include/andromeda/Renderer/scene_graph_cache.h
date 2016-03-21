#ifndef _ANDROMEDA_RENDERER_SCENE_GRAPH_CACHE_H_
#define _ANDROMEDA_RENDERER_SCENE_GRAPH_CACHE_H_


#include "scene_graph.h"


namespace andromeda
{
	class View;


	/*
		Extremely Basic Scene Graph Caching

		Contains the SceneGraph of objects that are for all intensive purposes... "visible"
	*/
	class SceneGraphCache : public ISceneGraph
	{
	public:
		SceneGraphCache(View * view);
		virtual ~SceneGraphCache();

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


		void for_each(std::function<void(std::shared_ptr<GameObject>)> cb) override;

		/*
			Process the Source Graph to manipulate the cache
		*/
		Boolean process(std::shared_ptr<ITransform> transform, std::shared_ptr<ISceneGraph> source);


		// OBJECT RETRIEVAL :: TESTING
		std::shared_ptr<GameObject> operator[](const char * const name) override
		{
			return getGameObject(name);
		}


	private:
		View * _view;
		std::unordered_map<std::string, std::shared_ptr<GameObject>> _objects;
	};

}

#endif
