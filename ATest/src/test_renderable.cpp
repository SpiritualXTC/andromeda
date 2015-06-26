#include "test_renderable.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/shader.h>
#include <andromeda/Graphics/geometry.h>
#include <andromeda/Graphics/geometry_builder.h>



/*

*/
GeometryRenderable::GeometryRenderable(std::shared_ptr<andromeda::Geometry> geometry) 
	: _geometry(geometry)
{

}

/*

*/
GeometryRenderable::~GeometryRenderable()
{

}


void GeometryRenderable::render(const aInt32 pass, const andromeda::Shader * const shader, const glm::mat4 & modelView)
{
	assert(shader);


	// Calculate Matrix
	glm::mat4 mv(1.0f);
	mv *= modelView;

	/*
		Configure Shader: Set Shader Uniforms
	*/
	// Matrices
	shader->setUniformMat4("u_modelview", mv);

	// Material


	// Textures


	// TEMP
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// Render ALL Geometry
	_geometry->render();
}





