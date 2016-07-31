#pragma once

#include "renderer.h"

namespace andromeda
{

	/*
		This Renderer can be used to switch between different renderers :)
		Use and Management of this renderer will need to be done by the application.

		TODO:
		Actually make this class :)

		Added the skeleton purely to remind me to set it up at some stage.
	*/
	class RendererActive : public IRenderer
	{
	public:

		Boolean addLayer(const std::string & method, const std::string & renderGroup,
			const std::shared_ptr<Effect> & effect, const std::string & technique = "") override
		{
			return false;
		}


		Boolean addRenderer(const std::string & rendererName, const std::shared_ptr<IRenderer> & renderer)
		{
			return false;
		}



		Boolean setActive(const std::string & renderer)
		{
			return false;
		}

		void resize(Float width, Float height) override
		{
			// resize all renderers
		}

		void render() override
		{
			if (!_active)
				return;

			_active->render();
		}

	private:

		std::unordered_map<std::string, std::shared_ptr<IRenderer>> _renderers;

		std::shared_ptr<IRenderer> _active;
	};
}