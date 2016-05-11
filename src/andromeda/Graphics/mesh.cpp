#include <andromeda/Graphics/mesh.h>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>

#include <andromeda/Graphics/effect.h>

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
void Mesh::render(const std::shared_ptr<IEffect> & effect)
{
	for (Size i = 0; i < _geometry.size(); ++i)
	{
		render(effect, i);
	}
}

/*

*/
void Mesh::render(const std::shared_ptr<IEffect> & effect, UInt32 geomIndex)
{
	assert(geomIndex < _geometry.size());
	assert(_geometry[geomIndex].geometry);

	// Set Materials... etc
	if (_geometry[geomIndex].materialIndex >= 0)
	{
		Material & material = _materials[_geometry[geomIndex].materialIndex];

		// Bind Material Uniforms
		effect->updateUniformVec3("g_ambient", material.getAmbient());
		effect->updateUniformVec3("g_diffuse", material.getDiffuse());
		effect->updateUniformVec3("g_specular", material.getSpecular());
	}

	// Render Geometry
	_geometry[geomIndex].geometry->render();
}