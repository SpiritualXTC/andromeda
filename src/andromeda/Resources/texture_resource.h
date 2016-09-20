#pragma once

#include <andromeda/graphics_types.h>

#include <andromeda/Resources/resource.h>
#include <andromeda/Resources/resource_builder.h>



namespace andromeda
{
	class Texture;

	/*
		Arguments for Loading a Texture
	*/
	struct TextureResourceArgs
	{
		std::string filename;

		StorageFormat format = StorageFormat::RGBA;

		TextureMinFilter minFilter = TextureMinFilter::Linear;
		TextureMagFilter magFilter = TextureMagFilter::Linear;
	};



	/*
		Create and Load a Texture Resource
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


	protected:
		const inline TextureResourceArgs & getArgs() const override { return _args; }

	private:
		TextureResourceArgs _args;
	};
}