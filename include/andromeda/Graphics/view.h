#ifndef _ANDROMEDA_GRAPHICS_VIEW_H_
#define _ANDROMEDA_GRAPHICS_VIEW_H_

#include <list>
#include <memory>

#include "../stddef.h"
#include "../Utilities/log.h"

#include "../Math/region.h"

namespace andromeda
{
	// Forward Declarations
	class SceneGraph;
	class Camera;

	class Pass;
	class IRenderable;
	class RenderList;



	/*
	
	*/
	class View
	{
	public:
		enum _Layer
		{
			Target,		// Render Target
			Default,	// Typical Game Layer
			HUD,		// Interface Layer
			Overlay,	// Overlay Layer
		};


		// Layer Sorting!
		friend Boolean operator <(const std::shared_ptr<View> & lhs, const std::shared_ptr<View> & rhs)
		{
			return lhs->layer() < rhs->layer();
		}





	public:
		View(Int32 layer = View::Default);
		View(Float x, Float y, Float width, Float height, Int32 layer = View::Default);
		

		virtual ~View();

		const inline Int32 layer() const { return _layer; }
		const inline Int32 group() const { return _group; }

		const inline std::shared_ptr<Camera> camera() const { return _camera; }

		/*
		
		*/
		void render(std::shared_ptr<RenderList> renderables);

		/*
		
		*/
		void resize(const Int32 width, const Int32 height);




		Boolean addRenderPass(Int32 passId);
		Boolean removeRenderPass(Int32 passId);

	private:
		Int32 _layer = 0;
		Int32 _group = 0;

		Region2f _view;		// Viewspace Region
		Region2i _screen;	// Screenspace Region


		glm::mat4 _projection;

		std::list<std::shared_ptr<Pass>> _passes;
		std::shared_ptr<Camera> _camera;
	};
}

#endif