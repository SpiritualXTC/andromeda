#include <andromeda/Game/geometry_component.h>


#include <andromeda/Geometry/geometry.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Renderer/transform.h>
#include <andromeda/Renderer/graphics_state.h>

using namespace andromeda;

/*

*/
GeometryRenderComponent::GeometryRenderComponent(std::shared_ptr<Geometry> geometry, std::shared_ptr<ITransform> transform)
	: _geometry(geometry)
	, _transform(transform)
{
	_material.setDiffuse(1, 1, 1);
}


/*

*/
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
void GeometryRenderComponent::render(GraphicsState & state)
{
	// Set Model Matrix
	state.setModelMatrix(_transform->matrix());

	
	// Get Textures
	const std::shared_ptr<ITexture> & diffuseTex = _material.getDiffuseTexture();

	// Bind Textures
	if (diffuseTex)
		diffuseTex->bind();

	// Set Material
	state.setMaterial(_material);

	// Render ALL Geometry
	_geometry->render();

	// Unbind Textures
	if (diffuseTex)
		diffuseTex->unbind();
}
