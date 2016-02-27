#include <andromeda/Graphics/texture.h>

#include <andromeda/Utilities/log.h>

#include <SOIL/SOIL.h>

using namespace andromeda;

std::shared_ptr<Texture> andromeda::LoadTexture(const std::string & filename)
{
	Int32 width = 0;
	Int32 height = 0;
	Int32 channels = 0;


	// Load Image
	void * data = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);

	if (!data)
	{
		log_err("Texture not Loaded: ", filename.c_str());
		return false;
	}
	else
		log_verbose("Texture Loaded: ", filename, width, height);

	// Create Texture
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	// Set Data
	texture->data((UInt8*)data, width, height);

	return texture;
}