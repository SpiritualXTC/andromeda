#include "deferred_geometry_method.h"

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

#include <andromeda/Graphics/frame_buffer.h>

using namespace andromeda;
using namespace andromeda::deferred;


/*

*/
DeferredRendererGeometryMethod::DeferredRendererGeometryMethod(const std::shared_ptr<IFrameBuffer> & gBuffer, const std::shared_ptr<ILayerEnvironment> & enviro)
	: RendererMethod(enviro)
	, _gBuffer(gBuffer)
{

}


/*

*/
void DeferredRendererGeometryMethod::begin()
{
	// Bind the Buffer
	_gBuffer->bind();

	// Clear the Buffer
	graphics()->setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	graphics()->clear();
}


/*

*/
void DeferredRendererGeometryMethod::end()
{
	_gBuffer->unbind();
}