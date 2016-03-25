#ifndef _ANDROMEDA_RENDERER_LAYER_H_
#define _ANDROMEDA_RENDERER_LAYER_H_

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>


#include <andromeda/glm.h>

#include <andromeda/stddef.h>

#include "renderable.h"


namespace andromeda
{
	class Effect;
	class IRenderable;
	class IRenderable;
	class IProjection;

	class ICamera;


	/*
		Class used to create views as they are dynamically added
	*/
	class LayerInfo
	{

	};



	/*
		A layer is a visual layer applied to a scene. 
		A layer consists of a single effect, with multiple techniques and multiple passes
	*/
	class Layer
	{
	private:
		struct _LayerSort
		{
			Boolean operator ()(IRenderable * lhs, IRenderable * rhs)
			{
				// WHY AM I USING THE ID??? LOLOLOLOLOLOLOLOLOLOL
				// Should be related to distance to camera, or some such thing :P
				return lhs->id() < rhs->id();
			}

		};

	public:
		Layer(const std::string & effectFile);
		virtual ~Layer();
		

//		Boolean addRenderable(std::shared_ptr<IRenderable> renderable);
//		Boolean removeRenderable(std::shared_ptr<IRenderable> renderable);

		Boolean addRenderable(IRenderable * renderable);
		Boolean removeRenderable(IRenderable * renderable);

		Boolean render(std::shared_ptr<IProjection> projection, const std::shared_ptr<ICamera> camera, const std::string & technique);

	private:
		std::shared_ptr<Effect> _effect;	// Should it be a weak pointer ?

	//	std::unordered_map<std::string, std::shared_ptr<IRenderable>> _renderables;
	//	std::set<std::shared_ptr<IRenderable>> _renderables;
		std::set<IRenderable*, _LayerSort> _renderables;
	};
}

#endif
