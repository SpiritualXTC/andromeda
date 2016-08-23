#include "resource_cube_texture.h"

#include <array>

#include <andromeda/andromeda.h>

#include <andromeda/graphics.h>
#include <andromeda/graphics_conversion.h>

#include <andromeda/IO/file_location.h>

#include <andromeda/Utilities/image.h>
#include <andromeda/Utilities/io.h>

#include <andromeda/Utilities/log.h>

#include <andromeda/Utilities/Util/ptree_helper.h>

using namespace andromeda;



/*

*/
std::shared_ptr<ResourceEx<CubeTexture, CubeTextureResourceArgs>> CubeTextureResourceBuilder::build(const boost::property_tree::ptree & propTree, const IFileLocation * location)
{
	boost::optional<std::string> name = util::getChildValueOptional(propTree, "name");

	boost::optional<std::string> filenameXPos = util::getChildValueOptional(propTree, "xpos");
	boost::optional<std::string> filenameYPos = util::getChildValueOptional(propTree, "ypos");
	boost::optional<std::string> filenameZPos = util::getChildValueOptional(propTree, "zpos");
	boost::optional<std::string> filenameXNeg = util::getChildValueOptional(propTree, "xneg");
	boost::optional<std::string> filenameYNeg = util::getChildValueOptional(propTree, "yneg");
	boost::optional<std::string> filenameZNeg = util::getChildValueOptional(propTree, "zneg");

	boost::optional<std::string> format = util::getChildValueOptional(propTree, "format");

	boost::optional<std::string> filter = util::getChildValueOptional(propTree, "filter");
	boost::optional<std::string> minFilter = util::getChildValueOptional(propTree, "minfilter");
	boost::optional<std::string> magFilter = util::getChildValueOptional(propTree, "magfilter");



	// Name must be set
	if (!name.is_initialized())
		return nullptr;

	// Filenames must be set. 
	if (!filenameXPos.is_initialized() || !filenameXNeg.is_initialized())
		return nullptr;

	if (!filenameYPos.is_initialized() || !filenameYNeg.is_initialized())
		return nullptr;

	if (!filenameZPos.is_initialized() || !filenameZNeg.is_initialized())
		return nullptr;

	
	log_debugp("CubeTextureResourceBuilder :: build() :: Loading Cube Texture");
	log_tree();

	// Filter Tweaks
	if (!minFilter.is_initialized())
		minFilter = filter;
	if (!magFilter.is_initialized())
		magFilter = filter;

	log_verbosep("Name = %1%", name);

	log_verbosep("X-Positive Filename = %1%", filenameXPos);
	log_verbosep("X-Negative Filename = %1%", filenameXNeg);
	log_verbosep("Y-Positive Filename = %1%", filenameYPos);
	log_verbosep("Y-Negative Filename = %1%", filenameYNeg);
	log_verbosep("Z-Positive Filename = %1%", filenameZPos);
	log_verbosep("Z-Negative Filename = %1%", filenameZNeg);

	log_verbosep("Format = %1%", format);
	log_verbosep("MagFilter = %1%", magFilter);
	log_verbosep("MinFilter = %1%", minFilter);

	// Create Resource
	auto resource = std::make_shared<CubeTextureResource>(name.get(), location);

	// Filenames have already been validated
	resource->setFilename(CubeTextureFace::X_Positive, filenameXPos.get());
	resource->setFilename(CubeTextureFace::X_Negative, filenameXNeg.get());

	resource->setFilename(CubeTextureFace::Y_Positive, filenameYPos.get());
	resource->setFilename(CubeTextureFace::Y_Negative, filenameYNeg.get());

	resource->setFilename(CubeTextureFace::Z_Positive, filenameZPos.get());
	resource->setFilename(CubeTextureFace::Z_Negative, filenameZNeg.get());

	// Set Format
	if (format.is_initialized())
	{
		StorageFormat fmt = util::convertToStorageFormat(format.get(), StorageFormat::RGBA);

		resource->setFormat(fmt);
	}

	// Set Min Filter
	if (minFilter.is_initialized())
	{
		TextureMinFilter min = util::convertToTextureMinFilter(minFilter.get(), TextureMinFilter::Linear);

		resource->setMinFilter(min);
	}

	// Set Mag Filter
	if (magFilter.is_initialized())
	{
		TextureMagFilter mag = util::convertToTextureMagFilter(magFilter.get(), TextureMagFilter::Linear);

		resource->setMagFilter(mag);
	}

	return resource;
}







/*

*/
std::shared_ptr<CubeTexture> CubeTextureResourceBuilder::load(const CubeTextureResourceArgs & args, const IFileLocation * location)
{
	log_debugp("Loading Cube Texture");


	Int32 width = -1;
	Int32 height = -1;

	struct _CubeFace
	{
		_CubeFace(CubeTextureFace f, const std::string & fn)
			: face(f), filename(fn) {}
		CubeTextureFace face;
		std::string filename;

		std::shared_ptr<Image> image;
	};

	std::array<_CubeFace, 6> faces =
	{
		_CubeFace(CubeTextureFace::X_Positive, args.filenameXPos),
		_CubeFace(CubeTextureFace::X_Negative, args.filenameXNeg),

		_CubeFace(CubeTextureFace::Y_Positive, args.filenameYPos),
		_CubeFace(CubeTextureFace::Y_Negative, args.filenameYNeg),

		_CubeFace(CubeTextureFace::Z_Positive, args.filenameZPos),
		_CubeFace(CubeTextureFace::Z_Negative, args.filenameZNeg)
	};


	// Load all the Textures
	for (auto & face : faces)
	{
		// Load File into memory
		std::shared_ptr<File> file = location->loadFile(face.filename, true);

		// Validate File :: early out
		// TODO: This should load something here - invalid texture or something
		if (!file)
		{
			log_errp("Unable to load cube texture file : %1%", face.filename);
			return nullptr;
		}

		// Load Image
		face.image = Image::LoadImageFromMemory(file.get());

		// Validate Image :: early out
		// TODO: This should setup an invalid texture or something
		if (!face.image)
		{
			log_errp("Unable to load cube texture image : %1%", face.filename);
			return nullptr;
		}

		// Set Dimensions
		if (width == -1)
			width = face.image->width();
		else if (width != face.image->width())
		{
			// Texture Size Mismatch
			log_warn("Cube Texture Size Mismatch");
		}

		if (height == -1)
			height = face.image->height();
		else if (height != face.image->height())
		{
			// Texture Size Mismatch
			log_warn("Cube Texture Size Mismatch");
		}
	}



	// Create Texture
	std::shared_ptr<CubeTexture> tex = graphics()->createCubeTexture(width, height);

	for (auto & face : faces)
	{
		tex->data(face.face, (UInt8*)face.image->data());
	}

	// Set Data
//	tex->data((UInt8*)image->data());

//	return tex;// std::move(tex);

	return tex;
}


