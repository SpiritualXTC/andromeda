#pragma once

#include <memory>
#include <string>
#include <vector>

#include <common/types.h>

#include "types.h"

namespace andromeda
{
	/*
		TODO: Some tweaks made to the constness
	*/

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

		// Binds to the First Texture Index
		inline void bind() const { bind(0); }

		// Unbinds from the First Texture Index
		inline void unbind() const { unbind(0); }

		// Binds to the active texture index 	
		virtual void bind(UInt32 activeIndex) const = 0;
	
		// Binds to the active texture index
		virtual void unbind(UInt32 activeIndex) const = 0;

	private:
	};






	/*
		TODO:

		Setup datatype options for the data being passed in... 
		
		for now it only uses UInt8

		however it may need to use other data at some stage.
	*/

	/*
		Abstract 2D Texture
	*/
	class Texture : virtual public ITexture
	{
	public:


		// Resize the Texture
		virtual void resize(UInt32 width, UInt32 height)
		{
			resize(width, height, format(), nullptr);
		}

		// Resize the Texture and Change StorageFormat
		inline void resize(UInt32 width, UInt32 height, StorageFormat storageFormat)
		{
			resize(width, height, storageFormat, nullptr);
		}

		// Resize the Texture and Set Data
		inline void resize(UInt32 width, UInt32 height, const UInt8 * ptr)
		{
			resize(width, height, format(), ptr);
		}




		// Get Width
		virtual const inline UInt32 width() const = 0;

		// Get Height
		virtual const inline UInt32 height() const = 0;

		// Get Format
		virtual const inline StorageFormat format() const = 0;

		// Resize the Texture, Change StorageFormat and sets Data
		virtual void resize(UInt32 width, UInt32 height, StorageFormat storageFormat, const UInt8 * ptr) = 0;

		// Send Data to the Texture
		virtual void data(const UInt8 * ptr) = 0;

		// Send only partial data to the Texture
		virtual void data(const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) = 0;

		// Set Filtering Options
		virtual void filter(TextureMagFilter magFilter, TextureMinFilter minFilter) = 0;

		// Set Wrapping / Clamping Options
		virtual void wrap(TextureWrapMode wrapMode) = 0;
	};









	/*
		Abstract Cube Texture
	*/
	class CubeTexture : virtual public ITexture
	{
	public:

		// Resize the Texture
		virtual void resize(UInt32 width, UInt32 height)
		{
			resize(width, height, format());
		}


		// Get Width
		virtual const inline UInt32 width() const = 0;

		// Get Height
		virtual const inline UInt32 height() const = 0;

		// Get Format
		virtual const inline StorageFormat format() const = 0;



		// Resize the Texture
		virtual void resize(UInt32 width, UInt32 height, StorageFormat storageFormat) = 0;

		// Send Data to the Textures' Face
		virtual void data(CubeTextureFace face, const UInt8 * ptr) = 0;

		// Send only Partial Data to the Textures' Face
		virtual void data(CubeTextureFace face, const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) = 0;

		// Set Filtering Options
		virtual void filter(TextureMagFilter magFilter, TextureMinFilter minFilter) = 0;
	};







	/*
		TODO: Abstract Volume Texture
	*/
	class VolumeTexture : virtual public ITexture
	{
	public:
		virtual const inline UInt32 width() const = 0;
		virtual const inline UInt32 height() const = 0;
		virtual const inline UInt32 depth() const = 0;

	private:
	};
}

typedef andromeda::Texture aTexture;

