#include <andromeda/Game/mesh_component.h>


#include <andromeda/Graphics/mesh.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>
#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/transform.h>
#include <andromeda/Renderer/render_state.h>

using namespace andromeda;

/*

*/
MeshRenderComponent::MeshRenderComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<ITransform> transform)
	: _mesh(mesh)
	, _transform(transform)
{

}


/*

*/
MeshRenderComponent::~MeshRenderComponent()
{

}




void MeshRenderComponent::render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms)
{

	// Animation Matices, could be push/popped here :)


	/*
	Configure Shader: Set Shader Uniforms
	*/

	/* Animation -- Subset of Data only. Each Subset *MAY*  contain its own Materials, etc */

	/* Effect: Set Materials, Textures, Colors */
	/* Effect: Set Transformations */



	/*
		TODO:
		- Effect Annotations
		- Don't pass the shader in, go directly via the Graphics API
			It should contain a pointer/reference to the active shader
	*/



	// Push Matrix
	ms.push();
	ms.multiply(_transform->matrix());

	// Update the Model View Matrix
	shader->setUniform("u_model", ms.top());

	// Bind Material Uniforms
	for (Int32 i = 0; i < _mesh->getGeometryCount(); ++i)
	{
		const Material & material = _mesh->getGeometryMaterial(i);

		/*
			TODO:
			This process should be done via Graphics API & Annotations
		*/
		shader->setUniform("g_ambient", material.getAmbient());
		shader->setUniform("g_diffuse", material.getDiffuse());
		shader->setUniform("g_specular", material.getSpecular());

		const std::shared_ptr<ITexture> & diffuseTex = material.getDiffuseTexture();

		if (diffuseTex)
		{
			/*
				TODO:
				This process SHOULD be done directly via the Graphics API
			*/
			//graphics()->setTexture(diffuseTex, [annotation], [index]);
			diffuseTex->bind();
			shader->setUniformTexture("g_diffuseTexture", 0);
		}


		_mesh->drawGeometry(i);

		if (diffuseTex)
			diffuseTex->unbind();
	}

	// Pop the matrix
	ms.pop();
}


/*

*/
void MeshRenderComponent::render(RenderState & rs)
{
	// Set Matrix
	rs.setModelMatrix(_transform->matrix());

	// Loop through geometry
	for (Int32 i = 0; i < _mesh->getGeometryCount(); ++i)
	{
		const Material & material = _mesh->getGeometryMaterial(i);

		// Get Textures
		const std::shared_ptr<ITexture> & diffuseTex = material.getDiffuseTexture();

		// Bind Texture
		if (diffuseTex)
			diffuseTex->bind();

		// Set Material
		rs.setMaterial(material);

		// Draw Geometry
		_mesh->drawGeometry(i);

		// Unbind Texture
		if (diffuseTex)
			diffuseTex->unbind();
	}

}