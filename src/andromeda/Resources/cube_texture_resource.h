#pragma once

#include <andromeda/graphics_types.h>

#include <andromeda/Resources/resource.h>
#include <andromeda/Resources/resource_builder.h>



namespace andromeda
{
	class CubeTexture;

	/*
		Arguments for Loading a Cube Texture
	*/
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



	/*
		Create and Load a Cube Texture Resource
	*/
	class CubeTextureResourceBuilder : public ResourceBuilderEx<CubeTexture, CubeTextureResourceArgs>
	{
	public:
		virtual std::shared_ptr<ResourceEx<CubeTexture, CubeTextureResourceArgs>> build(const boost::property_tree::ptree & propTree, const IFileLocation * location) override;
		std::shared_ptr<CubeTexture> load(const CubeTextureResourceArgs & args, const IFileLocation * location) override;
	};







	/*
		Cube Texture Resource
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


	protected:
		const inline CubeTextureResourceArgs & getArgs() const override { return _args; }

	private:
		CubeTextureResourceArgs _args;
	};
}