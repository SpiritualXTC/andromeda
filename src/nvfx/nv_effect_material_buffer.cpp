#include <nvfx/nv_effect_buffer.h>

using namespace andromeda;

MaterialEffectBuffer::MaterialEffectBuffer(nvFX::ICstBuffer * buffer)
	: EffectBuffer(buffer)
{
	// Get Uniforms from Const Buffer
	
	_ambient = findUniform("ambient");
	_diffuse = findUniform("diffuse");
	_specular = findUniform("specular");
}