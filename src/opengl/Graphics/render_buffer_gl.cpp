#include "frame_buffer_gl.h"

#include <opengl/graphics_gl.h>

using namespace andromeda;
using namespace andromeda::opengl;

/*

*/
RenderBufferGL::RenderBufferGL(Int32 width, Int32 height, UInt32 attachment, StorageFormat format, DataType dataType)
	: _width(width)
	, _height(height)
	, _dataType(dataType)
{

	// Convert DataType
	GLenum dt = GraphicsOpenGL::convDataType(_dataType);

	GLenum internalFormat = GraphicsOpenGL::convStorageFormatInternal(format);
	GLenum glFormat = GraphicsOpenGL::convStorageFormat(format);



	// Generate RenderBuffer Handle
	glGenRenderbuffers(1, &_buffer);


	// Generate Texture Handle
	glGenTextures(1, &_texture);


	// Bind RenderBuffer Handle
	glBindRenderbuffer(GL_RENDERBUFFER, _buffer);

	// Setup RenderBuffer
	glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, _buffer);



	// Bind Texture Handle
	bind();

	// Allocate Memory
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, glFormat, dt, NULL);

	/*
		TODO:
		Setup Texture Filtering in graphics_types.h and the conversions.
	*/
	// Set Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, _texture, 0);







	// Unbind Buffers
	unbind();
	unbindBuffer();
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
void RenderBufferGL::bind()
{
	glBindTexture(GL_TEXTURE_2D, _texture);
}



/*

*/
void RenderBufferGL::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}