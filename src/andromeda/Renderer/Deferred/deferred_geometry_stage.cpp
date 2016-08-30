#include "deferred_geometry_stage.h"

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

#include <andromeda/Math/camera_matrix.h>
#include <andromeda/Renderer/camera.h>
#include <andromeda/Graphics/frame_buffer.h>



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
void DeferredGeometryStage::begin()
{
	// Bind the Buffer
	_gBuffer->bind();

	

	// Clear the Buffer
	graphics()->setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	graphics()->clear();
}


/*

*/
void DeferredGeometryStage::end()
{
	_gBuffer->unbind();
}