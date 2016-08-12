#include <andromeda/Utilities/image.h>

#include <andromeda/Platform/file.h>
#include <andromeda/Utilities/log.h>

/*
	TODO:
	Replace SOIL with a better library that doesn't suck :)
*/

#include <SOIL/SOIL.h>

using namespace andromeda;


/*

*/
std::shared_ptr<Image> Image::LoadImageFromFile(const std::string & filename)
{
	Int32 width = 0;
	Int32 height = 0;
	Int32 channels = 0;

	log_debugp("Image :: LoadImage() :: Loading Image from File");

	// Load Image
	unsigned char * data = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);

	// Create Image
	std::shared_ptr<Image> image = std::make_shared<Image>(width, height, (UInt32*)data, width * height);

	// Free Image
	SOIL_free_image_data(data);

	return image;
}



/*

*/
std::shared_ptr<Image> Image::LoadImageFromMemory(const File * file)
{
	Int32 width = 0;
	Int32 height = 0;
	Int32 channels = 0;

	log_debugp("Image :: LoadImage() :: Loading Image from Memory");

	// Load Image
	unsigned char * data = SOIL_load_image_from_memory((const unsigned char *)file->data(), file->length(), &width, &height, &channels, SOIL_LOAD_RGBA);

	// Create Image
	std::shared_ptr<Image> image = std::make_shared<Image>(width, height, (UInt32*)data, width * height);

	// Free Image
	SOIL_free_image_data(data);

	return image;
}