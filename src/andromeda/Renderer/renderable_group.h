#pragma once

/*
	This class does NOT need to be exposed to the application
*/


/*
	A RenderGroup is a group of renderables that all share the same rendering requirements

	An Example Could be
	1:
	- Group A: All "physical" meshes in the scene (projectiles, ships, static terrain, etc)
	- Group B: Particle System
	- Group C: Interface

	Group A and B, both share the same camera and SceneGraph
	Group C has a different SceneGraph

	2:
	- Group A: All "physical" meshes in the scene (projectiles, ships, etc)
	- Group B: Dynamic Terrain driven by a geometry shader
	- Group C: Particle System
	- Group D: Visible Light Cones
	- Group E: Interface
	- Group F: Debugging Information

	Group A, B, C, D 
		Share the camera 
		Share the SceneGraph
	Group E, Group F
		Have a different SceneGraph
		Have different (however likely to be equal) cameras

	Group A & B, both share an extremely similiar shader and follow similiar shader paths :: However they are different shaders, therefore they are different passes
			Settings these up as seperate techniques/layergroups would be ... silly
			They need to be setup so that a layer = pass, layergroup = technique
*/


#include <memory>
#include <string>
#include <set>

#include <andromeda/stddef.h>

namespace andromeda
{
	class IRenderable;

	class GraphicsState;
	
	/*
	
	*/
	class RenderableGroup
	{
	public:
		RenderableGroup(const std::string & groupName);
		virtual ~RenderableGroup();


		// Get Group Name
		const std::string & group() const { return _groupName; }

		// Get Number of Renderables
		const UInt32 size() const { return _renderables.size(); }

		// Adds a Renderable
		Boolean addRenderable(IRenderable * renderable);

		// Removes a Renderable
		Boolean removeRenderable(IRenderable * renderable);

		// Render all Objects
		void render(GraphicsState & rs);


	private:
		std::string _groupName;


		// This should really be sorted .... by something useful :P
		// However it may not matter :D
		std::set<IRenderable*> _renderables;
	};
}
