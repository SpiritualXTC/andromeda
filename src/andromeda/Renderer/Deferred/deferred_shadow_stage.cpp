#include "deferred_shadow_stage.h"

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Graphics/light.h>

#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/graphics_state.h>

using namespace andromeda;
using namespace andromeda::deferred;


/*

*/
DeferredShadowStage::DeferredShadowStage()
{
	/*
		TODO:
		Size of the Shadow Map should be based on application defined settings

		However these settings *COULD* be stored in andromeda::settings()
		when the config system is setup.
	*/
	// Setup Camera
	getCamera()->setOrthogonal(10.0f, -10.0f, 20.0f);
	getCamera()->setView(-1.0f);	// Why did this have to be negative?


	// Create Shadow Map
	_shadowMap = andromeda::graphics()->createFrameBuffer(512, 512);

	_shadowMap->attach(FrameBufferAttachment::Depth, StorageFormat::Depth24, DataType::UnsignedInt);

}



/*

*/
DeferredShadowStage::~DeferredShadowStage()
{

}



/*

*/
void DeferredShadowStage::begin(GraphicsState & gs)
{
	gs.setViewport(0, 0, _shadowMap->width(), _shadowMap->height());

	// Bind the Buffer
	_shadowMap->bind();

	// The Viewport needs to be altered for the shadowmap
	// This can't be done properly yet due to no way of restoring the viewport back to the previous....

	// Clear all Buffers
	graphics()->clear();



	// TODO: Fix Meh
	// This could be done by using a specialised ViewMatrix that adjusts itself based on the light direction
	// That is afterall WHY the Camera takes a IViewMatrix....
	
	// Cheap and Nasty minor hack :)
	if (_light)
		getCamera()->setView(-_light->getDirection(), glm::vec3(0.0f, 0.0f, 0.0f));
}

/*

*/
void DeferredShadowStage::end(GraphicsState & gs)
{
	// Bind the Buffer
	_shadowMap->unbind();
}