#include <opengl/graphics_gl.h>

// Include OpenGL Graphic Objects
#include "Graphics/frame_buffer_gl.h"
#include "Graphics/texture_gl.h"
#include "Graphics/cube_texture_gl.h"

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
std::shared_ptr<IFrameBuffer> GraphicsOpenGL::createFrameBuffer(UInt32 width, UInt32 height)
{
	return std::make_shared<opengl::FrameBufferGL>(width, height);
}


/*
	Create Texture
*/
std::shared_ptr<Texture> GraphicsOpenGL::createTexture(UInt32 width, UInt32 height)
{
	return std::make_shared<opengl::TextureGL>(width, height);
}


/*
	Create Cube Texture [No Implementation]
*/
std::shared_ptr<CubeTexture> GraphicsOpenGL::createCubeTexture(UInt32 width, UInt32 height)
{
	return std::make_shared<opengl::TextureCubeGL>(width, height);
}

/*
	Create Volume Texture [No Implementation]
*/
std::shared_ptr<VolumeTexture> GraphicsOpenGL::createVolumeTexture()
{
	return nullptr;
}

/*
	Creates a Shader
*/
std::shared_ptr<IShader> GraphicsOpenGL::createShader()
{
	return nullptr;
}