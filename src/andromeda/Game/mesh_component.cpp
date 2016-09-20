#include <andromeda/Game/mesh_component.h>


#include <andromeda/Graphics/mesh.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>
#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/transform.h>
#include <andromeda/Renderer/graphics_state.h>

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


/*

*/
void MeshRenderComponent::render(GraphicsState & state)
{
	// Set Matrix
	state.setModelMatrix(_transform->matrix());

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
		state.setMaterial(material);

		// Draw Geometry
		_mesh->drawGeometry(i);

		// Unbind Texture
		if (diffuseTex)
			diffuseTex->unbind();
	}

}