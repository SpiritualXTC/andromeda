#ifndef _ANDROMEDA_GRAPHICS_VIEW_H_
#define _ANDROMEDA_GRAPHICS_VIEW_H_

#include <list>
#include <memory>

#include <andromeda/stddef.h>

#include <andromeda/Math/region.h>




namespace andromeda
{
	// Forward Declarations
	class SceneGraph;
	class Camera;
	class RenderTarget;
	class IRenderTarget;

	class Effect;
	class IRenderable;




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
		View(std::shared_ptr<IRenderTarget> target);

		virtual ~View();

		const inline Int32 layer() const { return _layer; }
		const inline Int32 group() const { return _group; }

		const inline std::shared_ptr<Camera> camera() const { return _camera; }

		/*
		
		*/
		void render(std::shared_ptr<SceneGraph> scene);

		/*
		
		*/
		void resize(const Int32 width, const Int32 height);





	private:
		Int32 _layer = 0;
		Int32 _group = 0;

		Region2f _view;		// Viewspace Region
		Region2i _screen;	// Screenspace Region


		glm::mat4 _projection;

		std::shared_ptr<Effect> _effect;
		std::shared_ptr<Camera> _camera;

		std::shared_ptr<IRenderTarget> _target;
	};
}

#endif