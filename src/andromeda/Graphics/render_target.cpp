#include <andromeda/Graphics/render_target.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
RenderTarget::RenderTarget(Int32 width, Int32 height)
{
	// Generate Framebuffer
	glGenFramebuffers(1, &_frameBuffer);
	bindFrame();

	// Set Texture as Framebuffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, handle(), 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	unbindFrame();

	// Default the Render Target
	data(nullptr, width, height);
}

/*

*/
RenderTarget::~RenderTarget()
{
	if (_frameBuffer)
		glDeleteFramebuffers(1, &_frameBuffer);
	_frameBuffer = 0;
}



/*

*/
void RenderTarget::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

/*

*/
void RenderTarget::bindFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

	

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		log_err("Failure Settings Framebuffer");
}

/*

*/
void RenderTarget::unbindFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
