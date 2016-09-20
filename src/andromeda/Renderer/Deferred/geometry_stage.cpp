#include "geometry_stage.h"

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

#include <andromeda/Math/camera_matrix.h>

#include <andromeda/Graphics/frame_buffer.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/render_state.h>

using namespace andromeda;
using namespace andromeda::deferred;


/*

*/
DeferredGeometryStage::DeferredGeometryStage(const std::shared_ptr<IFrameBuffer> & gBuffer, const std::shared_ptr<Camera> & camera, const std::shared_ptr<ILayerEnvironment> & enviro)
	: RenderStage(camera, enviro)
	, _gBuffer(gBuffer)
{

}


/*

*/
void DeferredGeometryStage::begin(RenderState & state)
{
	state.setViewport(0, 0, _gBuffer->width(), _gBuffer->height());

	// Bind the Buffer
	_gBuffer->bind();

	

	// Clear the Buffer
	graphics()->setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	graphics()->clear();
}


/*

*/
void DeferredGeometryStage::end(RenderState & state)
{
	_gBuffer->unbind();
}