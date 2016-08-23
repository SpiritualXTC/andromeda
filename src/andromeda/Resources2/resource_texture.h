#pragma once


#include <andromeda/Graphics/texture.h>
#include <andromeda/Resources2/resource.h>
#include <andromeda/Resources2/resource_builder.h>


#include <andromeda/Utilities/log.h>

/*
	TODO:
	Remove logging
*/

namespace andromeda
{

	struct TextureResourceArgs
	{
		std::string filename;

		StorageFormat format = StorageFormat::RGBA;

		TextureMinFilter minFilter = TextureMinFilter::Linear;
		TextureMagFilter magFilter = TextureMagFilter::Linear;
	};



	/*
		Builds a Texture Resource
	*/
	class TextureResourceBuilder : public ResourceBuilderEx<Texture, TextureResourceArgs>
	{
	public:
		std::shared_ptr<ResourceEx<Texture, TextureResourceArgs>> build(const boost::property_tree::ptree & propTree, const IFileLocation * location) override;
		std::shared_ptr<Texture> load(const TextureResourceArgs & args, const IFileLocation * location) override;
	};





	/*
		Texture Resource
	*/
	class TextureResource : public ResourceEx<Texture, TextureResourceArgs>
	{
	public:
		TextureResource(const std::string & name, const IFileLocation * location)
			: ResourceEx(name, location)
		{

		}

		// Set Filename
		inline TextureResource & setFilename(const std::string & filename)
		{
			_args.filename = filename;

			return *this;
		}

		// Set Storage Format
		inline TextureResource & setFormat(StorageFormat format)
		{
			_args.format = format;

			return *this;
		}

		// Sets Min Filter
		inline TextureResource & setMinFilter(TextureMinFilter filter)
		{
			_args.minFilter = filter;

			return *this;
		}

		// Sets Mag Filter 
		inline TextureResource & setMagFilter(TextureMagFilter filter)
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

			return - 1;
		}

		// Get Format
		const inline StorageFormat format() const override 
		{ 
			if (isAvailable())
				return getResource()->format(); 

			return StorageFormat::Unknown;
		}

		// Resize the Texture, Change StorageFormat and sets Data
		void resize(UInt32 width, UInt32 height, StorageFormat storageFormat, const UInt8 * ptr) override
		{
			if (isAvailable())
				getResource()->resize(width, height, storageFormat, ptr);
		}

		// Send Data to the Texture
		void data(const UInt8 * ptr) override
		{
			if (isAvailable())
				getResource()->data(ptr);
		}

		// Send only partial data to the Texture
		void data(const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height) override
		{
			if (isAvailable())
				getResource()->data(ptr, xOffset, yOffset, width, height);
		}

		// Set Filtering Options
		void filter(TextureMagFilter magFilter, TextureMinFilter minFilter) override
		{
			if (isAvailable())
				getResource()->filter(magFilter, minFilter);
		}

	protected:
		const inline TextureResourceArgs & getArgs() const override { return _args; }

	private:
		TextureResourceArgs _args;
	};
}