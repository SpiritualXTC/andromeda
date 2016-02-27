#include <andromeda/Game/render_component.h>

#include <andromeda/Game/transform_component.h>

#include <andromeda/Graphics/geometry.h>
#include <andromeda/Graphics/shader.h>

using namespace andromeda;



/*

*/
RenderComponent::RenderComponent(std::shared_ptr<andromeda::Geometry> geometry, std::weak_ptr<TransformComponent> transform)
	: _geometry(geometry)
	, _transform(transform)
{
	assert(geometry);
}



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
	assert(! _transform.expired());

	std::shared_ptr<TransformComponent> trans = _transform.lock();

	// Calculate Matrix/
	glm::mat4 mv = modelView;
	mv *= trans->matrix();



	/*
		Configure Shader: Set Shader Uniforms
	*/
	// Matrices
	shader->setUniformMat4("u_modelview", mv);

	// Material


	// Textures


	// TEMP
	


	// Render ALL Geometry
	_geometry->render();
}