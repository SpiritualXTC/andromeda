#pragma once

#include <vector>
#include <unordered_map>

#include "scene_graph.h"

namespace andromeda
{
	/*
		A "Simple" SceneGraph is possible to be done by using the hierarchial sceneGraph, so the basic implementation could be removed :)
	*/
	class SceneGraphHierarchy : public SceneGraph
	{
	private:
		struct _Node
		{
			
			_Node * parent;							// Reference to the parent
			std::vector<_Node> children;			// List of Children

													
			// AABB :: Includes Self & children :)
			void * aabb;	// Obviously this shouldn't be an aabb :)

			std::shared_ptr<GameObject> entity;		// Reference to the Object Itself
		};

	public:

	private:


		_Node root;


		std::unordered_map<std::string, _Node> _nodes;
	};
}