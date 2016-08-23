#pragma once

#include <andromeda/Graphics/texture.h>
#include <andromeda/Resources2/resource.h>
#include <andromeda/Resources2/resource_builder.h>


namespace andromeda
{

	struct CubeTextureResourceArgs
	{
		std::string filenameXPos;
		std::string filenameXNeg;
		std::string filenameYPos;
		std::string filenameYNeg;
		std::string filenameZPos;
		std::string filenameZNeg;


		StorageFormat format = StorageFormat::RGBA;

		TextureMinFilter minFilter = TextureMinFilter::Linear;
		TextureMagFilter magFilter = TextureMagFilter::Linear;
	};



	// Loads a CubeTexture
	class CubeTextureResourceBuilder : public ResourceBuilderEx<CubeTexture, CubeTextureResourceArgs>
	{
	public:
		virtual std::shared_ptr<ResourceEx<CubeTexture, CubeTextureResourceArgs>> build(const boost::property_tree::ptree & propTree, const IFileLocation * location) override;
		std::shared_ptr<CubeTexture> load(const CubeTextureResourceArgs & args, const IFileLocation * location) override;
	};







	/*

	*/
	class CubeTextureResource : public ResourceEx<CubeTexture, CubeTextureResourceArgs>
	{
	public:
		CubeTextureResource(const std::string & name, const IFileLocation * location)
			: ResourceEx(name, location)
		{

		}

		// Set Filename
		inline CubeTextureResource & setFilename(CubeTextureFace face, const std::string & filename)
		{
			switch (face)
			{
			case CubeTextureFace::X_Positive: _args.filenameXPos = filename; break;
			case CubeTextureFace::X_Negative: _args.filenameXNeg = filename; break;

			case CubeTextureFace::Y_Positive: _args.filenameYPos = filename; break;
			case CubeTextureFace::Y_Negative: _args.filenameYNeg = filename; break;

			case CubeTextureFace::Z_Positive: _args.filenameZPos = filename; break;
			case CubeTextureFace::Z_Negative: _args.filenameZNeg = filename; break;
			}

			return *this;
		}

		// Set Storage Format
		inline CubeTextureResource & setFormat(StorageFormat format)
		{
			_args.format = format;

			return *this;
		}

		// Sets Min Filter
		inline CubeTextureResource & setMinFilter(TextureMinFilter filter)
		{
			_args.minFilter = filter;

			return *this;
		}

		// Sets Mag Filter 
		inline CubeTextureResource & setMagFilter(TextureMagFilter filter)
		{
			_args.magFilter = filter;

			return *this;
		}










		// Binds to the active texture index 	
		inline void bind(UInt32 activeIndex) const override
		{
			if (isAvailable())
				getResource()->bind(activeIndex);
		}

		// Binds to the active texture index
		inline void unbind(UInt32 activeIndex) const override
		{
			if (isAvailable())
				getResource()->unbind(activeIndex);
		}

		// Get Width
		const inline UInt32 width() const override
		{
			if (isAvailable())
				return getResource()->width();
			return -1;
		}

		// Get Height
		const inline UInt32 height() const override
		{
			if (isAvailable())
				return getResource()->height();

			return -1;
		}

		// Get Format
		const inline StorageFormat format() const override
		{
			if (isAvailable())
				return getResource()->format();

			return StorageFormat::Unknown;
		}

		// Resize the Texture, Change StorageFormat and sets Data
		void resize(UInt32 width, UInt32 height, StorageFormat storageFormat) override
		{
			if (isAvailable())
				getResource()->resize(width, height, storageFormat);
		}

		// Send Data to the Texture
		void data(CubeTextureFace face, const UInt8 * ptr) override
		{
			if (isAvailable())
				getResource()->data(face, ptr);
		}

		// Send only partial data to the Texture
		void data(CubeTextureFace face, const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) override
		{
			if (isAvailable())
				getResource()->data(face, ptr, xOffset, yOffset, width, height);
		}

		// Set Filtering Options
		void filter(TextureMagFilter magFilter, TextureMinFilter minFilter) override
		{
			if (isAvailable())
				getResource()->filter(magFilter, minFilter);
		}







	protected:
		const inline CubeTextureResourceArgs & getArgs() const override { return _args; }

	private:
		CubeTextureResourceArgs _args;
	};
}