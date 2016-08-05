#ifndef _ANDROMEDA_GRAPHICS_TEXTURE_H_
#define _ANDROMEDA_GRAPHICS_TEXTURE_H_

#include <memory>
#include <string>

#include "../stddef.h"

#include <andromeda/opengl.h>	// Remove Meh

namespace andromeda
{
	/*
		There are lots of different types of textures. They should probbaly all have a common base :)

		This allows them to all be used as a base


		Texture
		CubeTexture
		VolumeTexture

		+ others
	*/
	class ITexture
	{
	public:
		ITexture() {}
		virtual ~ITexture(){}

		inline void bind() { bind(0); }
		inline void unbind() { unbind(0); }

		//virtual void bind() = 0;
		virtual void bind(UInt32 activeIndex) const = 0;
		//virtual void unbind() = 0;
		virtual void unbind(UInt32 activeIndex) const = 0;

	private:
	};




	/*
		2D Texture

		TODO: Rename to Texture
	*/
	class ITexture2D : virtual public ITexture
	{
	public:
		virtual const Int32 width() const = 0;
		virtual const Int32 height() const = 0;
	};









	/*
		TODO:
		Move to the OpenGL library
	*/


	/*
		Simple 2D Texture
	*/
	class Texture : public ITexture2D
	{
	public:
		Texture(Int32 width, Int32 height);
		virtual ~Texture();

	//	void bind() override;
		void bind(UInt32 activeIndex) const override;
	//	void unbind() override;
		void unbind(UInt32 activeIndex) const override;

		void resize(const UInt8 * ptr, Int32 width, Int32 height);

		void data(const UInt8 * ptr);
		void data(const UInt8 * ptr, Int32 xOffset, Int32 yOffset, Int32 width, Int32 height);


		const inline UInt32 handle() const { return _handle; }

		const inline Int32 width() const { return _width; }
		const inline Int32 height() const { return _height; }

	private:
		Int32 _width = 0;
		Int32 _height = 0;

		UInt32 _handle = 0;
	};


	std::shared_ptr<Texture> LoadTexture(const std::string & filename);
}

typedef andromeda::Texture aTexture;

#endif