#include <andromeda/Graphics/scene_graph.h>

using namespace andromeda;

/*

*/
SceneGraph::SceneGraph()
{

}



/*

*/
SceneGraph::~SceneGraph()
{

}



/*

*/
Boolean SceneGraph::addGroup(Int32 group)
{
	// Make sure it's not overriding an existing group...
	if (hasGroup(group))
		return false;
	
	// Add the Group
	_groups[group] = std::make_shared<SceneGroup>();

	return hasGroup(group);
}



/*

*/
Boolean SceneGraph::addRenderable(Int32 group, std::shared_ptr<IRenderable> renderable)
{
	// Does the Group Exist?
	if (! hasGroup(group))
	{
		// No? Create the Group
		if (!addGroup(group))
			return false;
	}

	// Add Renderable
	return _groups[group]->addRenderable(renderable);
}



/*

*/
Boolean SceneGraph::removeRenderable(Int32 group, std::shared_ptr<IRenderable> renderable)
{
	// Does the Group Exist?
	if (! hasGroup(group))
	{
		return false;
	}

	// Should a group with no renderables be removed automatically?


	// Remove Renderable
	return _groups[group]->removeRenderable(renderable);
}






/* 
	TEMPORARY!
	This crappy system just runs through everything rendering. It needs a rewrite!
*/
Boolean SceneGraph::render(Int32 group, Shader * shader, glm::mat4 & modelView)
{
	if (!hasGroup(group))
		return false;

	// Get SceneGroup
	std::shared_ptr<ISceneGroup> scenegroup = _groups[group];

	return scenegroup->render(shader, modelView);
}

