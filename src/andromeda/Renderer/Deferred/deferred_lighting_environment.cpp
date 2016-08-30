#include "deferred_lighting_environment.h"

#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::deferred;

#if 0
/*

*/
DeferredLightingLayerExtension::DeferredLightingLayerExtension(std::shared_ptr<IFrameBuffer> & fb)
	: _gBuffer(fb)
{

}

/*

*/
void DeferredLightingLayerExtension::begin(const std::shared_ptr<IShader> & shader)
{
	static std::string uniforms[] = {
		"u_gBufferDiffuse",
		"u_gBufferPosition",
		"u_gBufferNormal"
	};

	assert(shader);

	for (UInt32 i = 0; i < _gBuffer->getBufferCount(); ++i)
	{
		std::shared_ptr<ITexture> t = _gBuffer->getTexture(i);

		t->bind(i);
		shader->setUniformTexture(uniforms[i], i);
	}
}


/*

*/
void DeferredLightingLayerExtension::end(const std::shared_ptr<IShader> & shader)
{
	for (UInt32 i = 0; i < _gBuffer->getBufferCount(); ++i)
	{
		std::shared_ptr<ITexture> t = _gBuffer->getTexture(i);

		t->unbind(i);
	}
}
#endif












/*

*/
DeferredLightingEnvironment::DeferredLightingEnvironment(const std::shared_ptr<IFrameBuffer> & fb, const std::shared_ptr<Camera> & worldCamera)
	: _gBuffer(fb)
	, _camera(worldCamera)
{

}

/*

*/
void DeferredLightingEnvironment::begin(const IShader * shader)
{
	static std::string uniforms[] = {
		"u_gBufferDiffuse",
		"u_gBufferPosition",
		"u_gBufferNormal"
	};

	assert(shader);

	for (UInt32 i = 0; i < _gBuffer->getBufferCount(); ++i)
	{
		std::shared_ptr<ITexture> t = _gBuffer->getTexture(i);

		t->bind(i);
		shader->setUniformTexture(uniforms[i], i);
	}

	glm::vec4 cp = glm::vec4(0, 0, 0, 1);

	glm::mat4 v = glm::inverse(_camera->getViewMatrix());

	cp = v * cp;

//	log_debugp("%1%, %2%, %3%", cp.x, cp.y, cp.z);

	shader->setUniform("u_cameraPosition", glm::vec3(cp));
}


/*

*/
void DeferredLightingEnvironment::end(const IShader * shader)
{
	for (UInt32 i = 0; i < _gBuffer->getBufferCount(); ++i)
	{
		std::shared_ptr<ITexture> t = _gBuffer->getTexture(i);

		t->unbind(i);
	}
}