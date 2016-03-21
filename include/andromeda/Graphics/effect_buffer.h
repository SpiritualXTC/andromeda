#ifndef _ANDROMEDA_GRAPHICS_NV_EFFECT_BUFFER_H_
#define _ANDROMEDA_GRAPHICS_NV_EFFECT_BUFFER_H_


#include <nvfx/FxLib.h>

#include <andromeda/stddef.h>

namespace andromeda
{

	/*
		Wraps the "Constant Buffer" used by nvFX

		Relocate once the classes are fixed
	*/
	template<typename T>
	class EffectBuffer
	{
	public:
		public EffectBuffer(nvFX::ICstBuffer * buffer)
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


	private:
		nvFX::ICstBuffer * _buffer = nullptr;

		

	};


}

#endif