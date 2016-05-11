#ifndef _ANDROMEDA_GRAPHICS_NV_EFFECT_BUFFER_H_
#define _ANDROMEDA_GRAPHICS_NV_EFFECT_BUFFER_H_

#include <cassert>

#include <nvfx/FxLib.h>

#include <andromeda/stddef.h>

namespace andromeda
{

	/*
		Wraps the "Constant Buffer" used by nvFX

		Relocate once the classes are fixed and working

		This is a base class for the effect buffer ... map() may not be needed here

		A Generic implementation for this class would be a good for custom data [using a hashmap with the uniform or something)
	*/
	template<typename T>
	class EffectBuffer
	{
	public:
		EffectBuffer(nvFX::ICstBuffer * buffer)
			: _buffer(buffer)
		{
			assert(_buffer);

			
		}


		/*
			Size of the Buffer
		*/
		inline const Size size() const { return sizeof(T); }

		/*
			Updates the Buffer
		*/
		Boolean update()
		{
			return _buffer->update();
		}


		/*
			Maps data to the Constant Buffer
		*/
		Boolean map(const T & data)
		{
			T * p;

			_buffer->mapBuffer(&p);
			memcpy(p, &data, sizeof(T));
			_buffer->unmapBuffer();
		}


	protected:
		inline nvFX::ICstBuffer * getBuffer()
		{
			return _buffer;
		}

		nvFX::IUniform * findUniform(const char * uniformName)
		{
			assert(_buffer);

			// Find the Uniform
			nvFX::IUniform * uniform = _buffer->findUniform(uniformName);

			// Currently The Uniform is required
			assert(uniform);

			return uniform;
		}


	private:
		nvFX::ICstBuffer * _buffer = nullptr;

		

	};



	/*
		MOVE THIS TO ANOTHER HEADER ... !
	*/
	class Material;

	class MaterialEffectBuffer : public EffectBuffer<Material>
	{
	public:
		MaterialEffectBuffer(nvFX::ICstBuffer * buffer);


	private:
		nvFX::IUniform * _ambient;
		nvFX::IUniform * _diffuse;
		nvFX::IUniform * _specular;
	};


}

#endif