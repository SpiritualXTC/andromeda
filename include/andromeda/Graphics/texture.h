#pragma once

#include <memory>
#include <string>

#include "../stddef.h"

#include <andromeda/opengl.h>	// Remove Meh


#include <andromeda/graphics_types.h>

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

	/*
		Common Interface shared by all texture types
	*/
	class ITexture
	{
	public:
		ITexture() {}
		virtual ~ITexture(){}

	
		inline void bind() { bind(0); }
		inline void unbind() { unbind(0); }

		// Binds to the active texture index 	
		virtual void bind(UInt32 activeIndex) const = 0;
	
		// Binds to the active texture index
		virtual void unbind(UInt32 activeIndex) const = 0;

	private:
	};






	/*
		Abstract 2D Texture
	*/
	class Texture : virtual public ITexture
	{
	public:
		// Resize the Texture [Currently Loses all information]
		virtual void resize(const UInt8 * ptr, UInt32 width, UInt32 height) = 0;

		virtual void data(const UInt8 * ptr) = 0;
		virtual void data(const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) = 0;

		virtual const inline UInt32 width() const = 0;
		virtual const inline UInt32 height() const = 0;
	};






	/*
		Abstract Cube Texture
	*/
	class CubeTexture : public ITexture
	{
	public:

		virtual const inline UInt32 width() const = 0;
		virtual const inline UInt32 height() const = 0;
	};







	/*
		Abstract Volume Texture
	*/
	class VolumeTexture : public ITexture
	{
	public:
		virtual const inline UInt32 width() const = 0;
		virtual const inline UInt32 height() const = 0;
		virtual const inline UInt32 depth() const = 0;

	private:
	};





	/*
		Look for this function in use... lololol
	*/
	//std::shared_ptr<Texture> LoadTexture(const std::string & filename);
}

typedef andromeda::Texture aTexture;

