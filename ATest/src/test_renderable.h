#ifndef _TEST_RENDERABLE_H_
#define _TEST_RENDERABLE_H_

#include <memory>

#include <andromeda/Graphics/renderable.h>

// Forward Declarations
namespace andromeda
{
	class ITexture;

	class Geometry;
	class Shader;
	class VertexBuffer;
}


class GeometryRenderable : public andromeda::IRenderable
{
public:
	GeometryRenderable(std::shared_ptr<andromeda::Geometry> geometry, std::shared_ptr<andromeda::ITexture> texture = nullptr);
	virtual ~GeometryRenderable();

	void render(const andromeda::Shader * const shader, const glm::mat4 & modelView) override;


	/* Getters */
	const inline glm::vec3 & position() const { return _position; }
	
	/* Setters */
	inline void posiiton(const glm::vec3 & position) { _position = position; }
	inline void position(aFloat x, aFloat y, aFloat z) { _position = glm::vec3(x, y, z); }

private:
	std::shared_ptr<andromeda::Geometry> _geometry;
	std::shared_ptr<andromeda::ITexture> _texture;


	glm::vec3 _position = glm::vec3(0, 0, 0);
};



#endif