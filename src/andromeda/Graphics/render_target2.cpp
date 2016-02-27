#include <andromeda/Graphics/render_target.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
RenderTarget2::RenderTarget2(Int32 width, Int32 height, Int32 buffers)
	: _width(width)
	, _height(height)
	, _bufferCount(buffers)
{

	// Create Arrays
	_textures = new GLuint[_bufferCount];
	_buffers = new GLuint[_bufferCount];

	// Generate Textures
	glGenTextures(_bufferCount,_textures);

	// Generate Frame Buffers
	glGenFramebuffers(_bufferCount, _buffers);


	GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };

	for (UInt32 i = 0; i < _bufferCount; ++i)
	{
		// Bind Texture
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Send Image Data to GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);

		// Bind Framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, _buffers[i]);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _textures[i], 0);
		glDrawBuffers(1, drawBuffers);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	_buffer = 0;
	_texture = 0;
	_index = 0;
}


/*

*/
RenderTarget2::~RenderTarget2()
{
	// Delete Buffers
	if (_buffers)
	{
		glDeleteFramebuffers(_bufferCount, &_buffer);
		delete[] _buffers;
		_buffers = nullptr;
	}
	_buffer = -1;

	// Delete Textures
	if (_textures)
	{
		glDeleteTextures(_bufferCount, _textures);
		delete[] _textures;
		_textures = nullptr;
	}
	_texture = -1;
}



/*

*/
void RenderTarget2::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}



/*

*/
void RenderTarget2::bind()
{
	assert(_texture != -1);

	glBindTexture(GL_TEXTURE_2D, _texture);
}


/*

*/
void RenderTarget2::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}







/*

*/
void RenderTarget2::bindFrame()
{
	assert(_buffer != -1);

	glBindFramebuffer(GL_FRAMEBUFFER, _buffer);



	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		log_err("Failure Settings Framebuffer");
}

/*

*/
void RenderTarget2::unbindFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Assign Current Texture
	_texture = _textures[_index];

	// Update Frame Index
	_index++;
	if (_index >= _bufferCount)
		_index = 0;

	// Assign Current Frame
	_buffer = _buffers[_index];
}