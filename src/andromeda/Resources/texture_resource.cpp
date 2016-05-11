#include <andromeda/Graphics/texture.h>
#include <andromeda/Resources/texture_resource.h>
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
	Template Specialisation for Loading a Mesh

	TODO:
	- The Mesh needs to be created and returned, irrespective of when/where the mesh gets loaded
	- Add threading support somewhere ...
*/
template<>
std::shared_ptr<Texture> ResourceLoader::build<Texture>(std::shared_ptr<File> file)
{
	log_warnp("Loading Texture");

	TextureLoader loader(file);

	return loader.getTexture();
}






/*

*/
TextureLoader::TextureLoader(const std::string & filename)
{
	log_debugp("Loading Texture: %1%", filename);

	Int32 width = 0;
	Int32 height = 0;
	Int32 channels = 0;


	// Load Image
	void * data = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);

	if (!data)
	{
		log_errp("Texture not Loaded: %1%", filename.c_str());
		return;
	}
	else
		log_verbosep("Texture Loaded: %1%x%2%", width, height);

	// Create Texture
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(width, height);

	// Set Data
	texture->data((UInt8*)data);
}



/*

*/
TextureLoader::TextureLoader(const std::shared_ptr<File> & file)
{
	log_debugp("Loading Texture");

	Int32 width = 0;
	Int32 height = 0;
	Int32 channels = 0;


	void * data = SOIL_load_image_from_memory((const unsigned char *)file->data(), file->length(), &width, &height, &channels, SOIL_LOAD_RGBA);

	if (!data)
	{
		log_errp("Texture not Loaded");
		return;
	}
	else
		log_verbosep("Texture Loaded: %1%x%2%", width, height);

	// Create Texture
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(width, height);

	// Set Data
	texture->data((UInt8*)data);
}



/*

*/
TextureLoader::~TextureLoader()
{

}