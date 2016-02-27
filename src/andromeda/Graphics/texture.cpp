#include <andromeda/Graphics/texture.h>

using namespace andromeda;

/*

*/
Texture::Texture()
{
	glGenTextures(1, &_handle);

	// Bind
	bind();


	// Send Empty Image Data
//	data(nullptr, 512, 512);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	


	// Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



	// Unbind
	unbind();
}


/*

*/
Texture::~Texture()
{
	if (_handle)
		glDeleteTextures(1, &_handle);
	_handle = 0;
}


/*

*/
void Texture::data(const UInt8 * ptr, Int32 width, Int32 height)
{
	_width = width;
	_height = height;

	bind();

	// Send Image Data to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

	unbind();
}

/*

*/
void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _handle);
}


/*

*/
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
