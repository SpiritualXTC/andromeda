#include "texture_resource.h"

#include <andromeda/Graphics/texture.h>
#include <andromeda/Resources/resource_manager.h>

#include <andromeda/IO/file.h>


#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

#include <andromeda/Utilities/image.h>
#include <andromeda/Utilities/log.h>

using namespace andromeda;



/*
	Template Specialisation for Loading a Texture

	TODO:
	- The Texture needs to be created and returned, irrespective of when/where/how the texture gets loaded
	- Add threading support somewhere ...
*/
template<>
std::shared_ptr<Texture> ResourceLoader::build<Texture>(std::shared_ptr<File> file)
{
	log_warnp("ResourceLoader :: build<Texture>() :: Loading Texture");

	TextureLoader loader(file);

	return loader.getTexture();
}

/*

*/
TextureLoader::TextureLoader(const std::string & filename)
{
	log_debugp("TextureLoader :: <init>() :: Loading Texture: %1%", filename);

	// Load Image
	std::shared_ptr<Image> image = Image::LoadImageFromFile(filename);

	// Create Texture
	_texture = graphics()->createTexture(image->width(), image->height());

	// Set Data
	_texture->data((UInt8*)image->data());

	if (_texture)
		log_infop("TextureLoader :: <init>() :: Valid Texture");
}

/*

*/
TextureLoader::TextureLoader(const std::shared_ptr<File> & file)
{
	log_debugp("TextureLoader :: <init>() :: Loading Texture from Memory");

	// Load Image
	std::shared_ptr<Image> image = Image::LoadImageFromMemory(file.get());

	// Create Texture
	_texture = graphics()->createTexture(image->width(), image->height());

	// Set Data
	_texture->data((UInt8*)image->data());

	if (_texture)
		log_infop("TextureLoader :: <init>() :: Valid Texture");
}

/*

*/
TextureLoader::~TextureLoader()
{

}