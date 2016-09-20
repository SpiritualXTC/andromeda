#include "lighting_environment.h"

#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Renderer/graphics_state.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::deferred;

/*

*/
DeferredLightingEnvironment::DeferredLightingEnvironment(const std::shared_ptr<IFrameBuffer> & fb, const std::shared_ptr<Camera> & worldCamera)
	: _gBuffer(fb)
	, _camera(worldCamera)
{

}


/*

*/
void DeferredLightingEnvironment::begin(GraphicsState & state)
{
	static std::string uniforms[] = {
		"u_gBufferDiffuse",
		"u_gBufferPosition",
		"u_gBufferNormal"
	};


	// Bind GBuffer as Textures
	for (UInt32 i = 0; i < _gBuffer->getBufferCount(); ++i)
	{
		std::shared_ptr<ITexture> t = _gBuffer->getTexture(i);

		t->bind(i);
		state.setUniform(uniforms[i], (Int32)i);
	}



	glm::vec4 cp = glm::vec4(0, 0, 0, 1);

	// Calc Inverse View Matrix
	glm::mat4 v = glm::inverse(_camera->getViewMatrix());

	// Calculate Camera Position
	cp = v * cp;

	// Set Camera Position
	state.setUniform("u_cameraPosition", glm::vec3(cp));
}


/*

*/
void DeferredLightingEnvironment::end(GraphicsState & state)
{
	// Unbind GBuffer as Texturess
	for (UInt32 i = 0; i < _gBuffer->getBufferCount(); ++i)
	{
		std::shared_ptr<ITexture> t = _gBuffer->getTexture(i);

		t->unbind(i);
	}
}