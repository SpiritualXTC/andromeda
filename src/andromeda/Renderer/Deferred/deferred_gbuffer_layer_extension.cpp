#include "deferred_gbuffer_layer_extension.h"

#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/frame_buffer.h>
#include <andromeda/Graphics/texture.h>


using namespace andromeda;
using namespace andromeda::deferred;

/*

*/
DeferredGBufferLayerExtension::DeferredGBufferLayerExtension(std::shared_ptr<IFrameBuffer> & fb)
	: _gBuffer(fb)
{

}

/*

*/
void DeferredGBufferLayerExtension::begin(const std::shared_ptr<IShader> & shader)
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
void DeferredGBufferLayerExtension::end(const std::shared_ptr<IShader> & shader)
{
	for (UInt32 i = 0; i < _gBuffer->getBufferCount(); ++i)
	{
		std::shared_ptr<ITexture> t = _gBuffer->getTexture(i);

		t->unbind(i);
	}
}