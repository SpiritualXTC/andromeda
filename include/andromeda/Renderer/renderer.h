#ifndef _ANDROMEDA_GRAPHICS_RENDERER_H_
#define _ANDROMEDA_GRAPHICS_RENDERER_H_

#include <memory>
#include <set>
#include <unordered_map>

#include <andromeda/stddef.h>

#include <andromeda/Engine/module.h>
#include <andromeda/Engine/system.h>

#include <andromeda/Events/resize.h>

#include "view.h"



namespace andromeda
{
	// Forward-Declarations
//	class RenderList;
	class SceneGraph;


	/*

	*/
	class Renderer : public Module < Renderer >, virtual ResizeListener
	{
	public:
		Renderer();
		virtual ~Renderer();


		Boolean addView(std::shared_ptr<View> view);
		Boolean removeView(std::shared_ptr<View> view);
		Boolean clearViews();

		Boolean addRenderable(Int32 group, std::shared_ptr<IRenderable> renderable);
		Boolean removeRenderable(Int32 group, std::shared_ptr<IRenderable> renderable);
		Boolean clearRenderables();

		

		// IModule
		void onPause(){}
		void onResume(){}

		void update();
	private:
		// ResizeListener
		Boolean onResize(ResizeEventArgs & e) override;



		void errorCheck();



		std::multiset<std::shared_ptr<View>> _views;
		//std::unordered_map<Int32, std::shared_ptr<RenderList>> _renderLists;


		std::shared_ptr<SceneGraph> _sceneGraph;
	};



}

typedef andromeda::Renderer aRenderer;

#endif