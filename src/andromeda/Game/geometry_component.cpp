#include <andromeda/Game/geometry_component.h>

#include <andromeda/Game/transform.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Math/matrix_stack.h>


using namespace andromeda;

/*

*/
GeometryRenderComponent::GeometryRenderComponent(std::shared_ptr<Geometry> geometry, std::shared_ptr<ITransform> transform)
	: _geometry(geometry)
	, _transform(transform)
{

}


/*

*/
GeometryRenderComponent::~GeometryRenderComponent()
{

}




void GeometryRenderComponent::render(const std::shared_ptr<andromeda::IEffect> effect, andromeda::MatrixStack & ms)
{

	// Animation Matices, could be push/popped here :)


	/*
		Configure Shader: Set Shader Uniforms
	*/

	/* Animation -- Subset of Data only. Each Subset *MAY*  contain its own Materials, etc */

	/* Effect: Set Materials, Textures, Colors */
	/* Effect: Set Transformations */
	


	// Push Matrix
	ms.push();
	ms.multiply(_transform->matrix());

	// Update the Model View Matrix
	effect->updateUniformMat4("u_modelview", ms.top());

	// Render ALL Geometry
	_geometry->render();

	// Pop the matrix
	ms.pop();
}