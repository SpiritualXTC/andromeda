#include "texture_resource.h"

#include <andromeda/Graphics/texture.h>
#include <andromeda/Resources/resource_manager.h>

#include <andromeda/Platform/file.h>

#include <andromeda/Utilities/log.h>

#include <SOIL/SOIL.h>

using namespace andromeda;

/*
	Loads a Texture :: This hasn't been tested since a change was made
*/
std::shared_ptr<Texture> andromeda::LoadTexture(const std::string & filename)
{
	TextureLoader loader(filename);

	return loader.getTexture();
}






/*
	Template Specialisation for Loading a Texture

	TODO:
	- The Texture needs to be created and returned, irrespective of when/where the mesh gets loaded
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

	Int32 width = 0;
	Int32 height = 0;
	Int32 channels = 0;


	// Load Image
	unsigned char * data = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);

	if (!data)
	{
		log_errp("TextureLoader :: <init>() :: Texture not Loaded: %1%", filename.c_str());
		return;
	}
	else
		log_verbosep("TextureLoader :: <init>() :: Texture Loaded: %1%x%2%", width, height);

	// Create Texture
	_texture = std::make_shared<Texture>(width, height);

	// Set Data
	_texture->data((UInt8*)data);

	if (_texture)
		log_infop("TextureLoader :: <init>() :: Valid Texture");

	SOIL_free_image_data(data);
}



/*

*/
TextureLoader::TextureLoader(const std::shared_ptr<File> & file)
{
	log_debugp("TextureLoader :: <init>() :: Loading Texture from Memory");

	Int32 width = 0;
	Int32 height = 0;
	Int32 channels = 0;


	unsigned char * data = SOIL_load_image_from_memory((const unsigned char *)file->data(), file->length(), &width, &height, &channels, SOIL_LOAD_RGBA);

	if (!data)
	{
		log_errp("TextureLoader :: <init>() :: Texture not Loaded");
		return;
	}
	else
		log_verbosep("TextureLoader :: <init>() :: Texture Loaded: %1%x%2%x%3%", width, height, channels);

	// Create Texture
	_texture = std::make_shared<Texture>(width, height);

	// Set Data
	_texture->data((UInt8*)data);

	if (_texture)
		log_infop("TextureLoader :: <init>() :: Valid Texture");


	std::string fn = "../test/" + file->filename() + ".png";
	SOIL_save_image(fn.c_str(), SOIL_SAVE_TYPE_BMP, width, height, channels, data);


	SOIL_free_image_data(data);
}



/*

*/
TextureLoader::~TextureLoader()
{

}