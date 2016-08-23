#include "resource_texture.h"

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
std::shared_ptr<ResourceEx<Texture, TextureResourceArgs>> TextureResourceBuilder::build(const boost::property_tree::ptree & propTree, const IFileLocation * location)
{
	boost::optional<std::string> name = util::getChildValueOptional(propTree, "name");
	boost::optional<std::string> filename = util::getChildValueOptional(propTree, "filename");

	boost::optional<std::string> format = util::getChildValueOptional(propTree, "format");

	boost::optional<std::string> filter = util::getChildValueOptional(propTree, "filter");
	boost::optional<std::string> minFilter = util::getChildValueOptional(propTree, "minfilter");
	boost::optional<std::string> magFilter = util::getChildValueOptional(propTree, "magfilter");

	// Filename must be set
	if (!filename.is_initialized())
		return nullptr;

	log_debugp("TextureResourceBuilder :: build() :: Loading Texture");
	log_tree();


	// Set the Name :: Strip the Filename for the name (Remove Slashes)
	if (!name.is_initialized())
		name = GetFilename(filename.get());

	// Filter Tweaks
	if (!minFilter.is_initialized())
		minFilter = filter;
	if (!magFilter.is_initialized())
		magFilter = filter;


	log_verbosep("name = %1%", name);
	log_verbosep("Filename = %1%", filename);
	log_verbosep("Format = %1%", format);
	log_verbosep("MagFilter = %1%", magFilter);
	log_verbosep("MinFilter = %1%", minFilter);

	// Create Resource
	auto resource = std::make_shared<TextureResource>(name.get(), location);

	// Set Filename :: Already Validated
	resource->setFilename(filename.get());
	
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
std::shared_ptr<Texture> TextureResourceBuilder::load(const TextureResourceArgs & args, const IFileLocation * location)
{
	assert(location);

	log_debugp("Loading a Texture : %1%", args.filename);


	// Use the Loader to load the File
	std::shared_ptr<File> file = location->loadFile(args.filename, true);


	// Loads the Image
	//std::shared_ptr<Image> image = Image::LoadImageFromFile(args.filename);
	std::shared_ptr<Image> image = Image::LoadImageFromMemory(file.get());


	// Sends the Image Data to the Texture
	

	// Create Texture
	std::shared_ptr<Texture> tex = graphics()->createTexture(image->width(), image->height(), args.format);

	// Set Data
	tex->data((UInt8*)image->data());

	return tex;// std::move(tex);
}