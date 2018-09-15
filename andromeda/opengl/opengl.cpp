#include "opengl.h"

#include <GL/glew.h>

#include <common/log.h>

#include "geometry.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

using namespace andromeda;
using namespace andromeda::opengl;


class OpenGLFactory : public IGraphicsFactory
{
public:
	// Factory
	std::shared_ptr<ITexture> createTexture() override { return nullptr; }
	std::shared_ptr<ICubeTexture> createCubeTexture() override { return nullptr; }

	std::shared_ptr<IGeometry> createGeometry(PrimitiveMode mode, IndexType indexType) override;
	std::shared_ptr<IVertexBuffer> createVertexBuffer() override;
	std::shared_ptr<IIndexBuffer> createIndexBuffer() override;
};

std::shared_ptr<IGeometry> OpenGLFactory::createGeometry(PrimitiveMode mode, IndexType indexType)
{
	return std::make_shared<GeometryGL>(mode, indexType);
}

std::shared_ptr<IVertexBuffer> OpenGLFactory::createVertexBuffer()
{
	return std::make_shared<VertexBufferGL>();
}

std::shared_ptr<IIndexBuffer> OpenGLFactory::createIndexBuffer()
{
	return std::make_shared<IndexBufferGL>();
}



OpenGL::OpenGL()
{
	_factory = std::make_shared<OpenGLFactory>();
}

OpenGL::~OpenGL()
{

}

std::shared_ptr<IGraphicsFactory> OpenGL::getFactory()
{
	return _factory;
}






Boolean OpenGL::setClearColor(Float r, Float g, Float b)
{
	//log_debugp("OpenGL :: Set Clear Color (%.2f, %.2f, %.2f)", r, g, b);
	glClearColor(r, g, b, 1.0f);
	return true;
}


Boolean OpenGL::clear(ClearMaskBits mask)
{
	GLbitfield bits = 0;

	if (mask & ClearMask::Color)
		bits |= GL_COLOR_BUFFER_BIT;
	if (mask & ClearMask::Depth)
		bits |= GL_DEPTH_BUFFER_BIT;
	if (mask & ClearMask::Stencil)
		bits |= GL_STENCIL_BUFFER_BIT;

	glClear(bits);

	return true;
}