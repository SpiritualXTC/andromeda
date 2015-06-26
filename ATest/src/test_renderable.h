#ifndef _TEST_RENDERABLE_H_
#define _TEST_RENDERABLE_H_

#include <memory>

#include <andromeda/Graphics/renderable.h>

// Forward Declarations
namespace andromeda
{
	class Shader;
	class VertexBuffer;
	class Geometry;
}


class GeometryRenderable : public andromeda::IRenderable
{
public:
	GeometryRenderable(std::shared_ptr<andromeda::Geometry> geometry);
	virtual ~GeometryRenderable();

	void render(const aInt32 pass, const andromeda::Shader * const shader, const glm::mat4 & modelView) override;

private:
	std::shared_ptr<andromeda::Geometry> _geometry;

	
};



#endif