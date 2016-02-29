#include <andromeda/Game/render_component.h>

#include <glm/gtc/matrix_transform.hpp>


#include <andromeda/Game/transform_component.h>

#include <andromeda/Geometry/geometry.h>

#include <andromeda/Graphics/shader.h>
#include <andromeda/Graphics/texture.h>


using namespace andromeda;



/*

*/
#if 1
RenderComponent::RenderComponent(std::shared_ptr<andromeda::Geometry> geometry, std::weak_ptr<TransformComponent> transform)
	: _geometry(geometry)
	, _transform(transform)
{
	assert(geometry);
}
#else

RenderComponent::RenderComponent(std::weak_ptr<TransformComponent> transform)
	: _transform(transform)
{
	
}
#endif


/*

*/
RenderComponent::~RenderComponent()
{

}


/*
	
*/
void RenderComponent::render(const andromeda::Shader * const shader, const glm::mat4 & modelView)
{
	assert(shader);
	//assert(! _transform.expired());

	std::shared_ptr<TransformComponent> trans = _transform.lock();

	// Calculate Matrix/
	glm::mat4 mv = modelView;

	// Multiply World Matrix into ModelView Matrix
	trans->calculate();		// TEMPORARY
	mv *= trans->matrix();	

	// Animation Matices, could be push/popped here :)


	/*
		Configure Shader: Set Shader Uniforms
	*/
	// Matrices
	shader->setUniformMat4("u_modelview", mv);

	// Material :: This is most basic setup.
	// Single Pass draw call, with single Mesh.
	// Means a Mesh, made up of multiple "subsets" & materials wont work.
	shader->setUniformVec4("u_material.ambient", _material.ambient);
	shader->setUniformVec4("u_material.diffuse", _material.diffuse);
	shader->setUniformVec4("u_material.specular", _material.specular);

	// Textures : Basic (See Material)
	if (!_texture.expired())
	{
		_texture.lock()->bind();
	}

	// TEMP
	


	// Render ALL Geometry
	_geometry->render();



	// Undo Textures
	if (!_texture.expired())
	{
		_texture.lock()->unbind();
	}
}