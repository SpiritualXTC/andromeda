#pragma once


#include <list>
#include <memory>
#include <unordered_map>
#include <vector>


#include <andromeda/stddef.h>
#include <andromeda/Renderer/scene_graph.h>

namespace andromeda
{
	class GameObject;






	/*
		This class is currently in an unoptimised form :)
	*/
	class SceneGraphNode
	{
	public:
		typedef std::shared_ptr<SceneGraphNode> NodePtr;
		typedef std::list<NodePtr> NodeList;

		typedef NodeList::iterator iterator;
		typedef NodeList::const_iterator const_iterator;

	public:
		SceneGraphNode(SceneGraphNode * parent, const std::shared_ptr<GameObject> & o);

		// Gets the Object
		inline const std::shared_ptr<GameObject> & getObject() const { return _object; }
		inline SceneGraphNode * getParent() { return _parent; }
		inline const SceneGraphNode * getParent() const { return _parent; }


		inline NodeList::iterator begin() { return _children.begin(); }
		inline NodeList::iterator end() { return _children.end(); }

		inline NodeList::const_iterator begin() const { return _children.cbegin(); }
		inline NodeList::const_iterator end() const { return _children.cend(); }



		// Adds a Node to the Child List
		SceneGraphNode * add(const std::shared_ptr<GameObject> & child);

		// Removes a Node from the Child List
		Boolean remove(const std::shared_ptr<GameObject> & child);


		void update(Float timeStep);
		

	protected:
		SceneGraphNode() {}


		// Destroys a Node
		//virtual Boolean destroy();

		// Updates a Node
		


	private:

		SceneGraphNode * _parent;										// Reference to the parent
		NodeList _children;			// List of Children ?? Could be a map as well? Determine later


									// AABB :: Includes Self & children :)
		void * _boundingBox;	// Obviously this shouldn't be void * :)

		std::shared_ptr<GameObject> _object;		// Reference to the Object Itself
	};



	/*
		A "Simple" SceneGraph is possible to be done by using the hierarchial sceneGraph, so the basic (and abstract) implementation should be removed :)

		TODO:
		Move this to the /Game area... maybe

		Rename to SceneGraph
	*/
	class SceneGraphHierarchy : public SceneGraphNode, virtual public SceneGraph
	{
	public:
		

		
	public:
		SceneGraphHierarchy();
		virtual ~SceneGraphHierarchy();

		// Gets the Number of Objects in the SceneGraph
		const inline UInt32 getObjectCount() const { return _nodes.size(); }

		// Gets a Game Object
		std::shared_ptr<GameObject> getGameObject(const std::string & name);

		// Has an Object by the Specified Name
		Boolean hasObject(const std::string & name) override;

		// Has the Specified Object
		Boolean hasObject(std::shared_ptr<GameObject> object) override;

		// Adds a GameObject to the SceneGraph, with the root as a parent
		Boolean addGameObject(const std::shared_ptr<GameObject> & object) override;

		// Adds a GameObject to the SceneGraph, with a specified parent
		Boolean addGameObject(const std::shared_ptr<GameObject> & object, const std::string & parent) override;
		
		// Removes a GameObject from the SceneGraph
		Boolean removeGameObject(const std::string & name) override;
		
		// Removes a GameObject from the SceneGraph
		Boolean removeGameObject(const std::shared_ptr<GameObject> & object) override;


		// OBJECT RETRIEVAL :: TESTING
		std::shared_ptr<GameObject> operator[](const char * const name) override
		{
			return getGameObject(name);
		}



		// REMOVE MEH. Remove from the INterface. REMOVE IT!
		Boolean process(std::shared_ptr<RenderCache> & sgCache) override { return false; }


		// Required because of hte interface [TEMP] :: Interface is being removed
		void update(Float timeStep) override { SceneGraphNode::update(timeStep); }

	protected:
		SceneGraphNode * getNode(const std::string & name);

		Boolean addGameObject(const std::shared_ptr<GameObject> & object, SceneGraphNode * parent);


	private:
		std::unordered_map<std::string, SceneGraphNode*> _nodes;
	};
}