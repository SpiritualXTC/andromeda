#include <andromeda/Game/geometry_component.h>


#include <andromeda/Geometry/geometry.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>
#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/transform.h>

using namespace andromeda;

/*

*/
GeometryRenderComponent::GeometryRenderComponent(std::shared_ptr<Geometry> geometry, std::shared_ptr<ITransform> transform)
	: _geometry(geometry)
	, _transform(transform)
{
	_material.setDiffuse(1, 1, 1);
}

GeometryRenderComponent::GeometryRenderComponent(std::shared_ptr<Geometry> geometry, const Material & material, std::shared_ptr<ITransform> transform)
	: _geometry(geometry)
	, _transform(transform)
	, _material(material)
{

}



/*

*/
GeometryRenderComponent::~GeometryRenderComponent()
{

}



/*

*/
void GeometryRenderComponent::render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms)
{

	// Animation Matices, could be push/popped here :)


	/*
		Configure Shader: Set Shader Uniforms
	*/

	/* Animation -- Subset of Data only. Each Subset *MAY*  contain its own Materials, etc */

	/* Shader: Set Materials, Textures, Colors */
	/* Shader: Set Transformations */

	// Push Matrix
	ms.push();
	ms.multiply(_transform->matrix());

	// Update the Model View Matrix
	shader->setUniform("u_modelview", ms.top());

	// Get Material
	shader->setUniform("g_ambient", _material.getAmbient());
	shader->setUniform("g_diffuse", _material.getDiffuse());
	shader->setUniform("g_specular", _material.getSpecular());

	// Get Texture
	const std::shared_ptr<Texture> & diffuseTex = _material.getDiffuseTexture();

	if (diffuseTex)
	{
		// TODO: See Mesh Class
		diffuseTex->bind();
		shader->setUniformTexture("g_diffuseTexture", 0);
	}

	// Render ALL Geometry
	_geometry->render();


	if (diffuseTex)
	{
		diffuseTex->unbind();
	}

	// Pop the matrix
	ms.pop();
}