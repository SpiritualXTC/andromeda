#pragma once

#include <memory>
#include <string>
#include <vector>

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
		Options for Loading a 2D Texture
	*/
	struct TextureLoadArgs
	{
		// Filtering Options
		// Format
	};

	/*
		Options for Loading a Cube Texture
	*/
	struct CubeTextureLoadArgs
	{
		// Filtering Options
		// Format

		std::string filename_posX;
		std::string filename_negX;
		
		std::string filename_posY;
		std::string filename_negY;

		std::string filename_posZ;
		std::string filename_negZ;
	};

	/*
		Options for Loading a Volume Texture
	*/
	struct VolumeTextureLoadArgs
	{
		// Filtering Options
		// Format

		std::vector<std::string> filenames;
	};





	/*
		Face Direction for CubeTextures

		TODO: This may be better in graphics_types.h
	*/
	enum class CubeTextureFace
	{
		X_Positive,
		X_Negative,
		Y_Positive,
		Y_Negative,
		Z_Positive,
		Z_Negative,
	};













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
		// Resize the Texture
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

		// Resize the Texture
		virtual void resize(UInt32 width, UInt32 height) = 0;

		virtual const inline UInt32 width() const = 0;
		virtual const inline UInt32 height() const = 0;

		virtual void data(CubeTextureFace face, const UInt8 * ptr) = 0;
		virtual void data(CubeTextureFace face, const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) = 0;
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
}

typedef andromeda::Texture aTexture;

