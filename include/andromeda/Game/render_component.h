#ifndef _ANDROMEDA_GAME_RENDER_COMPONENT_H_
#define _ANDROMEDA_GAME_RENDER_COMPONENT_H_

#include <andromeda/Renderer/renderable.h>

#include "component.h"

namespace andromeda
{
	/*
	
	*/
	class RenderComponent : public Component<RenderComponent>, virtual public IRenderable
	{
	public:
		RenderComponent();
		virtual ~RenderComponent();

		void onViewActivate(View * view) override;
		void onViewDeactivate(View * view) override;
		
		
	private:

	};
}


#endif
