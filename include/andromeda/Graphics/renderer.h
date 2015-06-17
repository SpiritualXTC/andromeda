#ifndef _ANDROMEDA_GRAPHICS_RENDERER_H_
#define _ANDROMEDA_GRAPHICS_RENDERER_H_

#include <memory>
#include <set>

#include "../stddef.h"

#include "../Engine/module.h"
#include "../Engine/system.h"

#include "view.h"



namespace andromeda
{
	/*

	*/
	class Renderer : public Module < Renderer >
	{
	public:
		Renderer();
		virtual ~Renderer();


		Boolean addView();
		Boolean removeView();




		// IModule
		void onPause(){}
		void onResume(){}

		void update();
	private:
		Boolean resize(ResizeEventArgs & e);

		void errorCheck();



		std::set<std::shared_ptr<View>> _views;
	};



}


#endif