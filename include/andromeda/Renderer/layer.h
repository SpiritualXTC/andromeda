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
	/*
		TODO:
		Remove This
		Rename ITechnique to Technique
	*/
	//class ITechnique;
	//typedef ITechnique Technique;



	class Camera;

	class Effect;
	class ITechnique;
	class IPass;


	class IRenderable;
	class IProjection;

	

	class RenderGroup;





	/*
		A layer is a visual layer applied to a scene. 
		A layer consists of a single effect, with multiple techniques and multiple passes
	*/
	class Layer
	{
	private:
#if 0
		struct _LayerSort
		{
			Boolean operator ()(IRenderable * lhs, IRenderable * rhs)
			{
				// WHY AM I USING THE ID??? LOLOLOLOLOLOLOLOLOLOL
				// Should be related to distance to camera, or some such thing :P
				return lhs->id() < rhs->id();
			}

		};
#endif
	public:
		Layer(std::shared_ptr<Camera> & camera, std::shared_ptr<Effect> & effect, std::shared_ptr<RenderGroup> rg);
		//Layer(std::shared_ptr<Effect> & effect, const std::string & technique);
		virtual ~Layer();
		

		Boolean setActiveTechnique(const std::string & techniqueName);

//		Boolean addRenderable(std::shared_ptr<IRenderable> renderable);
//		Boolean removeRenderable(std::shared_ptr<IRenderable> renderable);

//		Boolean addRenderable(IRenderable * renderable);
//		Boolean removeRenderable(IRenderable * renderable);

	//	Boolean addLight(Light * light);
	//	Boolean removeLight(Light * light);

		Boolean render(/*std::shared_ptr<Camera> & camera*/);													// New Camera

		

	private:
		std::shared_ptr<Camera> _camera;

		std::shared_ptr<Effect> _effect;		// Should it be a weak pointer ?
		std::weak_ptr<ITechnique> _technique;


		std::shared_ptr<RenderGroup> _renderGroup;
	};







}

