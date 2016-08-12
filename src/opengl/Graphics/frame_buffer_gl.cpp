#include "frame_buffer_gl.h"

#include <andromeda/graphics.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::opengl;


/*

*/
FrameBufferGL::FrameBufferGL(Int32 width, Int32 height)
	: _width(width)
	, _height(height)
{
	log_debug("FrameBufferGL :: <init>()");
	log_tree();

	// Create FBO
	glGenFramebuffersEXT(1, &_frameBuffer);

	// Bind FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

	log_verbose("Attaching RenderBuffers to FrameBuffer");
	

	/*
		TODO: 
		Do this process where hte frame buffer itself is created/needed
	*/
	// Attach Color Buffers
	attach(GL_COLOR_ATTACHMENT0, StorageFormat::RGBA, DataType::UnsignedByte);
	attach(GL_COLOR_ATTACHMENT1, StorageFormat::RGBA32F, DataType::Float);
	attach(GL_COLOR_ATTACHMENT2, StorageFormat::RGBA16F, DataType::Float);

	// Depth Buffer
	log_verbose("Attaching DepthBuffer to FrameBuffer");
	_depth = std::make_shared<RenderBufferGL>(_width, _height, GL_DEPTH_ATTACHMENT, StorageFormat::Depth24, DataType::UnsignedInt);


	// Check Status
	if (!status())
		log_errp("Frame Buffer invalid");
	else
		log_info("Success... probably");


	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


/*

*/
FrameBufferGL::~FrameBufferGL()
{
	if (_frameBuffer)
		glDeleteFramebuffers(1, &_frameBuffer);
	_frameBuffer = 0;
}



void FrameBufferGL::attach(UInt32 attachment, StorageFormat format, DataType dataType)
{
	std::shared_ptr<RenderBufferGL> rbgl = std::make_shared<RenderBufferGL>(_width, _height, attachment, format, dataType);

	// Push the Attachment Back
	_attachments.push_back(attachment);

	// Push the Buffer Back
	_buffers.push_back(rbgl);
}


/*

*/
Boolean FrameBufferGL::status()
{
	// Check if all worked fine and unbind the FBO
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status == GL_FRAMEBUFFER_COMPLETE)
		return true;
	else
	{
		std::string err;

		switch (status)
		{
		case GL_FRAMEBUFFER_UNDEFINED:
			err = "FrameBuffer Undefined";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			err = "FrameBuffer incomplete Attachment";
			break;


		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			err = "FrameBuffer Missing Attachment";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			err = "FrameBuffer Incomplete DrawBuffer";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			err = "FrameBuffer Incomplete ReadBuffer";
			break;

		case GL_FRAMEBUFFER_UNSUPPORTED:
			err = "FrameBuffer Unsupported";
			break;


		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			err = "FrameBuffer incomplete Multisampling";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			err = "FrameBuffer incomplete Layer Targets";
			break;


		default:
			err = "unknown error";
		}


		log_errp("FrameBuffer Status = %1%", err);

	}





	return status == GL_FRAMEBUFFER_COMPLETE;
}


/*

*/
void FrameBufferGL::resize(Int32 width, Int32 height)
{
	_width = width;
	_height = height;

	// Bind FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

	for (const auto & it : _buffers)
		it->setSize(width, height);

	_depth->setSize(width, height);


	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}




/*

*/
void FrameBufferGL::bind()
{


	// Bind the FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

	glDrawBuffers(_attachments.size(), _attachments.data());
}


/*

*/
void FrameBufferGL::unbind()
{
	// Bind the FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}