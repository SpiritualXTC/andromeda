#include <andromeda/Renderer/renderer_deferred.h>


#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Renderer/camera.h>
#include <andromeda/Renderer/layer.h>

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>



#include <andromeda/Utilities/log.h>

#include "renderable_group.h"

#include "Deferred/deferred_directional_light.h"
#include "Deferred/deferred_environment.h"
#include "Deferred/deferred_geometry_method.h"
#include "Deferred/deferred_lighting_method.h"

using namespace andromeda;



/*
	TODO:
	Move the additional classes to the deferred renderer
*/




/*

*/





/*

*/
DeferredRenderer::DeferredRenderer(const std::shared_ptr<SceneGraph> & sg, const std::shared_ptr<Effect> & effect, const std::string & directionalTechnique)
	: Renderer(sg)
{
	// Create GBuffer
	_gBuffer = andromeda::graphics()->createFrameBuffer(512, 512);


	log_verbose("Attaching RenderBuffers to FrameBuffer");
	_gBuffer->attach(FrameBufferAttachment::Color, StorageFormat::RGBA, DataType::UnsignedByte);
	_gBuffer->attach(FrameBufferAttachment::Color, StorageFormat::RGBA32F, DataType::Float);
	_gBuffer->attach(FrameBufferAttachment::Color, StorageFormat::RGBA16F, DataType::Float);

	// Depth Buffer
	log_verbose("Attaching DepthBuffer to FrameBuffer");
	_gBuffer->attach(FrameBufferAttachment::Depth, StorageFormat::Depth24, DataType::UnsignedInt);


	// Create Environment Options for Deferred Renderer
	_environment = std::make_shared<deferred::DeferredEnvironment>();

	

	// Create Methods
	addMethod("background", std::make_shared<RendererMethod>());

	addMethod("geometry", std::make_shared<deferred::DeferredRendererGeometryMethod>(_gBuffer, _environment));

	_lightingMethod = std::make_shared<deferred::DeferredRendererLightingMethod>(_gBuffer, effect, directionalTechnique);

	addMethod("lighting", _lightingMethod);
}


/*

*/
void DeferredRenderer::onResize(Float width, Float height)
{
	_gBuffer->resize((Int32)width, (Int32)height);
}



#if 0
/*

*/
void DeferredRenderer::onBegin()
{

}

/*

*/
void DeferredRenderer::onEnd()
{

}
#endif



/*

*/
void DeferredRenderer::addDirectionalLight()
{
	// TODO: Pass through parameters. Not sure how this will be achieved.
	// It may need to be an object, that is dependancy-injected into the Renderable...

	// Add the Light.
	_lightingMethod->addDirectionalLight();
}


/*

*/
void DeferredRenderer::setEnvironmentReflectionmap(const std::shared_ptr<CubeTexture> & cubeTex)
{
	if (_environment)
	{
		_environment->setEnvironmentReflectionmap(cubeTex);
	}
}




#if 0
/*

*/
void DeferredRenderer::render()
{
	// Bind the Geometry Buffer

	_gBuffer->bind();







	// Unbind the Geometry Buffer
	_gBuffer->unbind();


	/*
		G-Buffer (Aka Geometry Buffer)
		- Multiple FrameBuffers that Geometry is "rendered" too.
		- Different textures will store different sets of data
		- Position (xyz)	:: This is the position when modified by the modelview matrix but NOT the projection matrix
		- Depth (x)			:: Could use "alpha" channel in the position buffer
		- Color (rgb)		:: Needs to include sampled textures material (diffuse) [Stage 1]
		- Normal (xyz)		:: Either Vertex Normals or Normal Mapped Normals
	*/



	// Render Geometry to G-Buffer using whatever
	// The shader to do this should be relatively simple... however it may NOT always be exactly the same
	// The Fragment Shader would probably be constant... ish
	// The Vertex Shader would also be very similiar... however for something like terrain, it could be quite concievable that is uses a completely different vertex shader with a geometry shader
	// Transparency Doesn't really work well with Deferred Rendering

	// It is also recommended that geometry is tested against an "alpha" mask, and discard pixels that are not present in the mask [VERY VERY VERY FIRST STEP]


	// "unbind" G-Buffer
	// Revert back to using the VIEWS render target :: This could be a FrameBuffer, but it could also be something else.
	// Essentially the Renderer, needs to know what the View is using to render too. [IViewTarget, ViewScreen, ViewTexture]


	// "bind" G-Buffer as textures to the shader


	// Draw Light Bounding Objects (Does the Depth Test matter ? ? ? )
	/*
		Directional Lights	= Quad across the entire VIEWAREA :: Different Camera (??) :: Not sure how the shader works for this.... :: This is the viewing plane from the projection-view matrix
		Point Lights		= Spheres
		Spot Lights			= Cones
		Neon Tubing			= Cylinders
		Particles			= Lots of little low-density spheres.... lol

		Vertex Shader is fairly typical. Needs both the ScreenSpace and cameraSpace position
			screen_pos = projection * modelview * vertex_position
			camera_pos = modelview * vertex_position

		Fragment Shader:
			Sample all the G-Buffer textures for position, color, etc.
			Use the geometry information from the buffer to calculate the pixel color

	*/


	//






	// Setup Deferred Shadows :: This requires rendering the scene to an offscreen depth/texture... from the perspective of the Light!

	// More Research :)
	



}
#endif