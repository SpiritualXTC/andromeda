#ifndef _ANDROMEDA_RENDERER_SCENE_GRAPH_BASIC_H_
#define _ANDROMEDA_RENDERER_SCENE_GRAPH_BASIC_H_


#include <unordered_map>
#include <vector>

#include "scene_graph.h"

namespace andromeda
{
	/*
	std::shared_ptr<GameObject> operator ()(std::pair<std::string, std::shared_ptr<GameObject>> & pair)
	{
		return pair.second;
	}
	*/

	



	/*
		A Very basic Scene Graph
	*/
	class BasicSceneGraph : public SceneGraph
	{
	public:
		BasicSceneGraph();
		virtual ~BasicSceneGraph();

		std::shared_ptr<GameObject> getGameObject(const std::string & name) override;

		Boolean hasObject(const std::string & name) override;
		Boolean hasObject(std::shared_ptr<GameObject> object) override;

		Boolean addGameObject(const std::shared_ptr<GameObject> & object) override;
		Boolean removeGameObject(const std::string & name) override;
		Boolean removeGameObject(const std::shared_ptr<GameObject> & object) override;

		const UInt32 getObjectCount() const override
		{
			return _objects.size();
		}


		/*
			Process the Scene in relation to the view
		*/
		Boolean process(std::shared_ptr<RenderCache> & sgCache) override;	// 
	


		// OBJECT RETRIEVAL :: TESTING
		std::shared_ptr<GameObject> operator[](const char * const name) override
		{
			return getGameObject(name);
		}




		/*
			Update all the objects in the scene
		*/
		void update(const Float timeStep) override;


	private:
		std::unordered_map<std::string, std::shared_ptr<GameObject>> _objects;
	};
}

#endif
