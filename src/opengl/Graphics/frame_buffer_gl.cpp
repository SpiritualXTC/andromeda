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

#if 0
	// Check Status :: This doesn't do anything useful here anymore.
	if (!status())
		log_errp("Frame Buffer invalid");
	else
		log_info("Success... probably");
#endif
}


/*

*/
FrameBufferGL::~FrameBufferGL()
{
	if (_frameBuffer)
		glDeleteFramebuffers(1, &_frameBuffer);
	_frameBuffer = 0;
}



/*

*/
Boolean FrameBufferGL::attach(FrameBufferAttachment attachment, StorageFormat format, DataType dataType)
{
	//
	if (attachment == FrameBufferAttachment::Depth)
	{
		// Depth. No Stencil
		attachDepth(GL_DEPTH_ATTACHMENT, format, dataType);
	}
	else if (attachment == FrameBufferAttachment::DepthStencil)
	{
		// Depth with Stencil
		attachDepth(GL_DEPTH_STENCIL_ATTACHMENT, format, dataType);
	}
	else
	{
		// Color Attachment
		UInt32 attachment = GL_COLOR_ATTACHMENT0;

		attachment += _attachments.size();

		attachColor(attachment, format, dataType);
	}

	return true;
}


/*
	Attach Color Buffer
*/
void FrameBufferGL::attachColor(UInt32 attachment, StorageFormat format, DataType dataType)
{
	/*
		TODO: Validate Format
	*/

	// Bind FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

	std::shared_ptr<RenderBufferGL> rbgl = std::make_shared<RenderBufferGL>(_width, _height, attachment, format, dataType);

	// Push the Attachment Back
	_attachments.push_back(attachment);

	// Push the Buffer Back
	_buffers.push_back(rbgl);

	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*

*/
void FrameBufferGL::attachDepth(UInt32 attachment, StorageFormat format, DataType dataType)
{
	/*
		TODO: Validate Format
	*/

	// Bind FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

	_depth = std::make_shared<RenderBufferGL>(_width, _height, attachment, format, dataType);

	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



/*

*/
Boolean FrameBufferGL::status()
{
	// Bind FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

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

	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


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

	// Resize all Color Attachments
	for (const auto & it : _buffers)
		it->setSize(width, height);

	// Resize Depth Attachments
	if (_depth)
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