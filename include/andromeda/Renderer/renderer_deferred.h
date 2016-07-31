#pragma once

#include "renderer.h"

namespace andromeda
{
	class Camera;

	class IFrameBuffer;



	/*
	
	*/
	class DeferredRenderer : public Renderer
	{
	public:
		DeferredRenderer(const std::shared_ptr<SceneGraph> & sg);


		
		void render() override;

	protected:
		void onResize(Float width, Float height) override;

	private:
		std::shared_ptr<IFrameBuffer> _gBuffer;
	};
}