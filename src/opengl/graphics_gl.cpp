#include <opengl/graphics_gl.h>

// Include OpenGL Graphic Objects
#include "Graphics/frame_buffer_gl.h"


// Include Log
#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
Int32 GraphicsOpenGL::getLastError()
{
	return glGetError();
}


/*

*/
void GraphicsOpenGL::errorCheck()
{
	Int32 err = 0;

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		// Send error message to log :)
		log_errp("GL Error: %1%", gluErrorString(err));
	}
}





/*

*/
std::shared_ptr<IFrameBuffer> GraphicsOpenGL::createFrameBuffer(Int32 width, Int32 height)
{
	return std::make_shared<opengl::FrameBufferGL>(width, height);
}