#include <andromeda/Graphics/texture.h>

using namespace andromeda;
#if 0
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
#endif

/*

*/
Texture::Texture(Int32 width, Int32 height)
{
	// Generate Handle
	glGenTextures(1, &_handle);

	// Resize Texture
	resize(nullptr, width, height);
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
void Texture::resize(const UInt8 * ptr, Int32 width, Int32 height)
{
	// Set Dimensions
	_width = width;
	_height = height;

	// Bind
	bind(0);

	// Send Image Data to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

	// Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Unbind
	unbind(0);
}


/*

*/
void Texture::data(const UInt8 * ptr)
{
	bind(0);

	// Send Image Data to GPU
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

	unbind(0);
}

/*

*/
void Texture::data(const UInt8 * ptr, Int32 xOffset, Int32 yOffset, Int32 width, Int32 height)
{
	bind(0);

	// Send Image Data to GPU
	glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

	unbind(0);
}




#if 0
void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _handle);
}
#endif

/*

*/
void Texture::bind(UInt32 activeIndex) const
{
	glActiveTexture(GL_TEXTURE0 + activeIndex);
	glBindTexture(GL_TEXTURE_2D, _handle);
}



#if 0

void Texture::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
#endif


/*

*/
void Texture::unbind(UInt32 activeIndex) const
{
	glActiveTexture(GL_TEXTURE0 + activeIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
}
