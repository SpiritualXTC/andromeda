#include "cube_texture_gl.h"

#include <array>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::opengl;



/*

*/
TextureCubeGL::TextureCubeGL(UInt32 width, UInt32 height)
{
	// Generate Handle
	glGenTextures(1, &_handle);

	// Resize Texture
	resize(width, height);
}


/*

*/
TextureCubeGL::~TextureCubeGL()
{
	if (_handle)
		glDeleteTextures(1, &_handle);

	_handle = 0;
}





/*

*/
void TextureCubeGL::resize(UInt32 width, UInt32 height)
{
	static std::array<GLenum, 6> faces = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,

		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,

		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	// Set Dimensions
	_width = width;
	_height = height;

	// Bind
	bind(0);

	// Send Image Data to GPU
	for (const auto & face : faces)
	{
		log_debugp("Generate Cube Face : %1%", face);

		// Create the Face
		glTexImage2D(face, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// TODO: Move this to a filter section
		// Set Texture Parameters

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Unbind
	unbind(0);
}


/*

*/
void TextureCubeGL::data(CubeTextureFace face, const UInt8 * ptr)
{
	static std::array<GLenum, 6> faces = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,

		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,

		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	GLenum faceIndex = faces.at((UInt32)face);

	bind(0);

	// Send Image Data to GPU
	glTexSubImage2D(faceIndex, 0, 0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, ptr);

	unbind(0);
}

/*

*/
void TextureCubeGL::data(CubeTextureFace face, const UInt8 * ptr, Int32 xOffset, Int32 yOffset, UInt32 width, UInt32 height)
{


}





/*

*/
void TextureCubeGL::bind(UInt32 activeIndex) const
{
	glActiveTexture(GL_TEXTURE0 + activeIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
}

/*

*/
void TextureCubeGL::unbind(UInt32 activeIndex) const
{
	glActiveTexture(GL_TEXTURE0 + activeIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}