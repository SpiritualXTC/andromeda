#pragma once

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>


#include <andromeda/glm.h>

#include <andromeda/stddef.h>

#include "camera.h"

#include "renderable.h"


namespace andromeda
{
	class Camera;

	class Effect;
	class ITechnique;
	class IPass;


	class IRenderable;
	class IProjection;

	

	class RenderableGroup;





	/*
		A layer is a visual layer applied to a scene. 
		A layer consists of a single effect, with multiple techniques and multiple passes
	*/
	class Layer
	{
	public:
		Layer(const std::shared_ptr<Camera> & camera, const std::shared_ptr<Effect> & effect, const std::shared_ptr<RenderableGroup> rg);
		virtual ~Layer();
		

		Boolean setActiveTechnique(const std::string & techniqueName);

		Boolean render();													

		

	private:
		std::shared_ptr<Camera> _camera;

		std::shared_ptr<Effect> _effect;		// Should it be a weak pointer ?
		std::weak_ptr<ITechnique> _technique;


		std::shared_ptr<RenderableGroup> _renderGroup;
	};







}

