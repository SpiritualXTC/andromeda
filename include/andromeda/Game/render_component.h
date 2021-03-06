#pragma once

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
		RenderComponent(const std::string & renderGroup);
		virtual ~RenderComponent();

		void onRenderActivate(IRenderableManager * manager) override;
		void onRenderDeactivate(IRenderableManager * manager) override;
		

		void setRenderGroup(const std::string & renderGroup) { _renderGroup = renderGroup; }
		
	private:
		std::string _renderGroup;
	};
}


