#ifndef _ANDROMEDA_GRAPHICS_SCENE_GRAPH_H_
#define _ANDROMEDA_GRAPHICS_SCENE_GRAPH_H_

#include <memory>
#include <unordered_map>
#include <vector>


#include <glm/glm.hpp>

#include "../stddef.h"

#include "renderable.h"

namespace andromeda
{
	// Forward Declarations
	//class IRenderable;
	class Shader;


	/*
	
	*/
	class SceneNode
	{
	public:
		SceneNode();
		SceneNode(std::shared_ptr<IRenderable> renderable);
		virtual ~SceneNode();

		Boolean addNode(std::shared_ptr<IRenderable> renderable);
		Boolean removeNode(std::shared_ptr<IRenderable> renderable);


		// Shortcut to renderable ID
		const inline Int32 id() const { return _renderable == nullptr ? -1 : _renderable->id(); }

		// TEMPORARY
		Boolean render(Shader * shader, glm::mat4 & modelView);

	private:
		std::shared_ptr<IRenderable> _renderable;
		std::vector<SceneNode> _nodes;
	};

	/*
		Render Group Interface
	*/
	class ISceneGroup
	{
	public:
		ISceneGroup(){}
		virtual ~ISceneGroup(){}

		virtual Boolean addRenderable(std::shared_ptr<IRenderable> renderable) = 0;
		virtual Boolean removeRenderable(std::shared_ptr<IRenderable> renderable) = 0;

		// TEMPORARY
		virtual Boolean render(Shader * shader, glm::mat4 & modelView) = 0;

	};

	/*
		Test SceneGroup
	*/
	class SceneGroup : public ISceneGroup
	{
	public:
		SceneGroup(){}
		virtual ~SceneGroup(){}

		inline Boolean addRenderable(std::shared_ptr<IRenderable> renderable)
		{
			return _root.addNode(renderable);
		}
		Boolean removeRenderable(std::shared_ptr<IRenderable> renderable)
		{
			return _root.removeNode(renderable);
		}


		// TEMPORARY
		Boolean render(Shader * shader, glm::mat4 & modelView)
		{
			return _root.render(shader, modelView);
		}

	private:
		SceneNode _root;
	};







	/*
	
	*/
	class SceneGraph
	{
	public:
		SceneGraph();
		virtual ~SceneGraph();

		Boolean addRenderable(Int32 group, std::shared_ptr<IRenderable> renderable);
		Boolean removeRenderable(Int32 group, std::shared_ptr<IRenderable> renderable);
	


		// TEMPORARY
		Boolean render(Int32 group, Shader * shader, glm::mat4 & modelView);

	private:
		Boolean addGroup(Int32 group);

		const inline Boolean hasGroup(Int32 group) { return !! _groups[group]; }
		const inline std::shared_ptr<ISceneGroup> getGroup(Int32 group) { return _groups[group]; }

		std::unordered_map<Int32, std::shared_ptr<ISceneGroup>> _groups;		// Make 'SceneNode' abstract :)
	};
}


#endif