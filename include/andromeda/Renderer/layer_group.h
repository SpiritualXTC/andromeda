#pragma once

/*
	TODO:
	This file does NOT need to be exposed to teh API
*/


#include <memory>
#include <string>
#include <vector>

#include <andromeda/stddef.h>




#include "camera.h"
#include "scene_graph_view_cache.h"

#include <andromeda/Renderer/layer.h>


namespace andromeda
{
	class Effect;
	class SceneGraphViewCache;



	/*
		TODO:
		Make it possible for layer groups to be automatically created, when a layer is added, rather than manually before layers are added.

		LayerGroups require a reference to the SceneGraph, which is stored by the Scene. The View therefore has no way of retrieving it directly
	*/



	/*
		A LayerGroup is a group of layers that share common properties... such as the Active Camera

		NB:
		A LayerGroup is NOT associated with the game objects drawn, an Object Group might be beneficial for that however... although that could be the cached scene graph :P
	*/
	class LayerGroup
	{
	public:
		LayerGroup(const std::string & name, const std::shared_ptr<SceneGraph> & sceneGraph, View * view);
		virtual ~LayerGroup();

		const std::string & getName() const { return _name; }


		std::shared_ptr<Camera> & getCamera() { return _camera; }
		const std::shared_ptr<Camera> & getCamera() const { return _camera; }


		void render();

	private:
		std::string _name;

		std::shared_ptr<Camera> _camera;				// This needs to be a smart pointer due to an observer with the matrices.... :/
		std::shared_ptr<SceneGraphViewCache> _cache;	// This needs to be a smart poitner due to the bloody camera

		std::shared_ptr<SceneGraph> _sceneGraph;
	};
}
