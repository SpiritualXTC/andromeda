#include <andromeda/Graphics/mesh.h>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>

#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
Mesh::Mesh()
{

}


/*

*/
Mesh::~Mesh()
{

}



/*
	Adds Geometry to the List of Geometry
*/
Boolean Mesh::addGeometry(std::shared_ptr<Geometry> & geometry, Int32 matIndex)
{
	_MeshData data(geometry, matIndex);
	_geometry.push_back(data);
	return true;
}

/*

*/
Boolean Mesh::addGeometry(GeometryBuilder & geometryBuilder, Int32 matIndex)
{
	std::shared_ptr<Geometry> g = geometryBuilder.build();
	return addGeometry(g, matIndex);
}



/*

*/
Boolean Mesh::addMaterial(Material & material)
{
	_materials.push_back(material);
	return true;
}

/*

*/
void Mesh::render(const std::shared_ptr<IShader> & shader)
{
	for (Size i = 0; i < _geometry.size(); ++i)
	{
		render(shader, i);
	}
}

/*

*/
void Mesh::render(const std::shared_ptr<IShader> & shader, UInt32 geomIndex)
{
	assert(geomIndex < _geometry.size());
	assert(_geometry[geomIndex].geometry);

	std::shared_ptr<Texture> difTex;

	// Set Materials... etc
	if (_geometry[geomIndex].materialIndex >= 0)
	{
		Material & material = _materials[_geometry[geomIndex].materialIndex];

		/*
			TODO:
			A mesh should have no care in the world as to what the effect is
			OR how it is rendered

			This should be part of the GraphicsAPI
		*/

		// Bind Material Uniforms
		shader->setUniform("g_ambient", material.getAmbient());
		shader->setUniform("g_diffuse", material.getDiffuse());
		shader->setUniform("g_specular", material.getSpecular());

		// Bind Textures
		difTex = material.getDiffuseTexture();
		if (difTex)
		{
			difTex->bind();
			shader->setUniformTexture("g_diffuseTexture", 0);
			
		}
	}

	// Render Geometry
	_geometry[geomIndex].geometry->render();


	if (difTex)
		difTex->unbind();
}