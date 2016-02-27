#ifndef _ANDROMEDA_GRAPHICS_TEXTURE_H_
#define _ANDROMEDA_GRAPHICS_TEXTURE_H_

#include <memory>
#include <string>

#include "../stddef.h"

#include "opengl.h"

namespace andromeda
{
	/*
		There are lots of different types of textures. They should probbaly all have a common base :)
	*/
	class ITexture
	{
	public:
		ITexture() {}
		virtual ~ITexture(){}

		virtual void bind() = 0;
		virtual void unbind() = 0;

	private:
	};



	/*
		Simple 2D Texture
	*/
	class Texture : public ITexture
	{
	public:
		Texture();
		virtual ~Texture();

		void bind();
		void unbind();
		void data(const UInt8 * ptr, Int32 width, Int32 height);



		const inline GLuint handle() const { return _handle; }

		const inline Int32 width() const { return _width; }
		const inline Int32 height() const { return _height; }

	private:
		Int32 _width = 0;
		Int32 _height = 0;

		GLuint _handle = 0;
	};


	std::shared_ptr<Texture> LoadTexture(const std::string & filename);
}

typedef andromeda::Texture aTexture;

#endif