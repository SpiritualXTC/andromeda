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
	class Camera;
	class IRenderable;

	class IShader;	// Remove meh

	/*
	
	*/
	class RenderGroup
	{
	public:
		RenderGroup(const std::string & groupName);
		virtual ~RenderGroup();


		// Get Group Name
		const std::string & group() const { return _groupName; }


		Boolean addRenderable(IRenderable * renderable);
		Boolean removeRenderable(IRenderable * renderable);



		// Render all Objects
		void render(std::shared_ptr<Camera> & camera, std::shared_ptr<IShader> shader);


	private:
		std::string _groupName;

		std::set<IRenderable*> _renderables;
	};
}
