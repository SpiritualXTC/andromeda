#include "test_renderable.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/geometry.h>
#include <andromeda/Graphics/shader.h>
#include <andromeda/Graphics/texture.h>




/*

*/
GeometryRenderable::GeometryRenderable(std::shared_ptr<andromeda::Geometry> geometry, std::shared_ptr<andromeda::ITexture> texture)
	: _geometry(geometry)
	, _texture(texture)
{

}

/*

*/
GeometryRenderable::~GeometryRenderable()
{

}


/*

*/
void GeometryRenderable::render(const andromeda::Shader * const shader, const glm::mat4 & modelView)
{
	assert(shader);


	// Calculate Matrix
	glm::mat4 mv = modelView;
	mv = glm::translate(mv, _position);

	/*
		Configure Shader: Set Shader Uniforms
	*/
	// Matrices
	shader->setUniformMat4("u_modelview", mv);

	

	// Material


	// Textures
	if (_texture)
	{
		_texture->bind();
		shader->setUniformTexture("u_texture", 0);
	}
	


	// TEMP
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// Render ALL Geometry
	_geometry->render();


	if (_texture)
		_texture->unbind();
}





