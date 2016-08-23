#include "texture_gl.h"

#include <opengl/graphics_gl.h>
#include <opengl/graphics_gl_conversions.h>

using namespace andromeda;
using namespace andromeda::opengl;


/*

*/
TextureGL::TextureGL(UInt32 width, UInt32 height, StorageFormat storageFormat)
{
	// Generate Handle
	glGenTextures(1, &_handle);

	// Resize Texture
	resize(width, height, storageFormat, nullptr);
}


/*

*/
TextureGL::~TextureGL()
{
	if (_handle)
		glDeleteTextures(1, &_handle);
	_handle = 0;
}



/*

*/
//void TextureGL::resize(const UInt8 * ptr, UInt32 width, UInt32 height)
void TextureGL::resize(UInt32 width, UInt32 height, StorageFormat storageFormat, const UInt8 * ptr)
{
	// Set Dimensions
	_width = width;
	_height = height;
	_format = storageFormat;

	// Convert Format to GLenum
	GLenum internalFormat = opengl::convStorageFormatInternal(_format);
	GLenum glFormat = opengl::convStorageFormat(_format);


	// Bind
	bind(0);

	// Send Image Data to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, ptr);

	// Unbind
	unbind(0);

	// Reset the Filter
	filter(_magFilter, _minFilter);
}

/*

*/
void TextureGL::data(const UInt8 * ptr)
{
	GLenum glFormat = opengl::convStorageFormat(_format);

	bind(0);

	// Send Image Data to GPU
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, glFormat, GL_UNSIGNED_BYTE, ptr);

	unbind(0);
}

/*

*/
void TextureGL::data(const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height)
{
	GLenum glFormat = opengl::convStorageFormat(_format);

	bind(0);

	// Send Image Data to GPU
	glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, glFormat, GL_UNSIGNED_BYTE, ptr);

	unbind(0);
}

/*

*/
void TextureGL::filter(TextureMagFilter magFilter, TextureMinFilter minFilter)
{
	// Assign
	_magFilter = magFilter;
	_minFilter = minFilter;

	// Convert Filtering Options
	GLint min = opengl::convTextureMinFilter(_minFilter);
	GLint mag = opengl::convTextureMagFilter(_magFilter);

	// Bind
	bind(0);

	// Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);

	// Unbind
	unbind(0);
}

/*

*/
void TextureGL::bind(UInt32 activeIndex) const
{
	glActiveTexture(GL_TEXTURE0 + activeIndex);
	glBindTexture(GL_TEXTURE_2D, _handle);
}

/*

*/
void TextureGL::unbind(UInt32 activeIndex) const
{
	glActiveTexture(GL_TEXTURE0 + activeIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
}