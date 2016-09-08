#include "frame_buffer_gl.h"

#include <opengl/graphics_gl.h>

using namespace andromeda;
using namespace andromeda::opengl;

/*

*/
RenderBufferGL::RenderBufferGL(Int32 width, Int32 height, UInt32 attachment, StorageFormat format, DataType dataType)
	: _width(width)
	, _height(height)
	, _format(format)
	, _dataType(dataType)
	, _attachment(attachment)
{





	// Generate RenderBuffer Handle
	glGenRenderbuffers(1, &_buffer);


	// Generate Texture Handle
	glGenTextures(1, &_texture);


	// Sets the Size
	setSize(width, height);
}


/*

*/
RenderBufferGL::~RenderBufferGL()
{

	if (_texture)
		glDeleteTextures(1, &_texture);
	_texture = 0;

	if (_buffer)
		glDeleteRenderbuffers(1, &_buffer);
	_buffer = 0;
}



void RenderBufferGL::setSize(Int32 width, Int32 height)
{
	// Set Dimensions
	_width = width;
	_height = height;


	// Convert DataType
	GLenum dt = opengl::convDataType(_dataType);

	GLenum internalFormat = opengl::convStorageFormatInternal(_format);
	GLenum glFormat = opengl::convStorageFormat(_format);


	// Bind RenderBuffer Handle
	glBindRenderbuffer(GL_RENDERBUFFER, _buffer);

	// Setup RenderBuffer
	glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, _attachment, GL_RENDERBUFFER, _buffer);



	// Bind Texture Handle
	bind(0);

	// Allocate Memory
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, glFormat, dt, NULL);

	// Set Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, _attachment, GL_TEXTURE_2D, _texture, 0);


	// Unbind Buffers
	unbind(0);
	unbindBuffer();
}



void RenderBufferGL::wrap(TextureWrapMode wrapMode)
{
	// Assign
//	_wrap = wrapMode;

	// Convert
	GLenum wrap = opengl::convTextureWrapMode(wrapMode);

	// BInd
	bind(0);

	// Set Texture Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap);

	// Unbind
	unbind(0);
}


/*
	Binds the RenderBuffer
*/
void RenderBufferGL::bindBuffer()
{
	glBindRenderbuffer(GL_RENDERBUFFER, _buffer);
}

/*
	Unbinds the RenderBuffer
*/
void RenderBufferGL::unbindBuffer()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


/*

*/
#if 0
void RenderBufferGL::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);
}
#endif

void RenderBufferGL::bind(UInt32 activeIndex) const
{
	glActiveTexture(GL_TEXTURE0 + activeIndex);
	glBindTexture(GL_TEXTURE_2D, _texture);
}



/*

*/
#if 0
void RenderBufferGL::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
#endif

void RenderBufferGL::unbind(UInt32 activeIndex) const
{
	glActiveTexture(GL_TEXTURE0 + activeIndex);
	glBindTexture(GL_TEXTURE_2D, _texture);
}
