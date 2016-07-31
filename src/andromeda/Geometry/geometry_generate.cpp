#include <andromeda/Geometry/geometry_generate.h>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>
#include <andromeda/Geometry/geometry_desc.h>
#include <andromeda/Graphics/buffer.h>

using namespace andromeda;
using namespace andromeda::geometry;


/*

*/
GeometryGenerate::GeometryGenerate()
{

}


/*

*/
GeometryGenerate::~GeometryGenerate()
{

	if (_indices)
		delete[] _indices;
	_indices = nullptr;

	if (_texCoord0)
		delete[] _texCoord0;
	_texCoord0 = nullptr;

	if (_normals)
		delete[] _normals;
	_normals = nullptr;

	if (_position)
		delete[] _position;
	_position = nullptr;

}


/*
	TODO:
	This really needs a more dynamic implementation
*/
std::shared_ptr<Geometry> GeometryGenerate::build(UInt32 genFlags)
{
	// Prebuild Process
	Boolean b = prebuild();
	if (!b)
		return nullptr;

	// Allocate
	Int32 vertices = getVertexCount();
	Int32 faces = getFaceCount();

	if (faces == 0 || vertices == 0)
		return nullptr;


	// Allocate Position
	_position = new glm::vec3[vertices];

	// Allocate Normals
	if (genFlags & GeometryGenerate::Normals)
		_normals = new glm::vec3[vertices];

	// Allocate TexCoordinate 0
	if (genFlags & GeometryGenerate::Texture)
		_texCoord0 = new glm::vec2[vertices];

	// Allocate Indices
	_indices = new UInt32[faces * 3];


	// Call Creation Functions
	if (_position)
		buildPosition(_position, vertices);	

	if (_indices)
		buildIndices(_indices, faces * 3);

	if (_normals)
		buildNormals(_normals, vertices);

	if (_texCoord0)
		buildTexCoords(_texCoord0, vertices);



	// Post Process
	postProcess();


	// Build Geometry Object
	GeometryBuilder gb;

	// Add Position Data
	if (_position)
		gb.addVertexData("pos", _position, vertices, GeometryLocation::Position);

	// Add Normal Data
	if (_normals)
		gb.addVertexData("norm", _normals, vertices, GeometryLocation::Normal);

	// Add Texture Data
	if (_texCoord0)
		gb.addVertexData("tex", _texCoord0, vertices, GeometryLocation::Texture0);

	// Create Buffers
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>();
	std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>();
	std::shared_ptr<GeometryDescription> desc = std::make_shared<GeometryDescription>(GL_TRIANGLES, vertices, faces * 3, GL_UNSIGNED_INT);

	// Copy Index Data
	ib->data(_indices, faces * 3 * sizeof(UInt32));

	// Interleave Data amongst buffers
	gb.build(vb, desc);

	// Create Geometry Object
	return std::make_shared<Geometry>(vb, desc, ib);
}




void GeometryGenerate::postProcess()
{
	if (_postProcessFlags == 0)
		return;

	// Post Process Trasnformation
	if (_postProcessFlags & GeometryGenerate::Transform)
	{
		transformPosition();

		if (_normals)
			transformNormals();
	}
}





/*

*/
void GeometryGenerate::transformPosition()
{
	assert(_position);

	glm::vec3 * pvertices = _position;

	for (UInt32 i = 0; i < getVertexCount(); ++i)
	{
		glm::vec4 p = glm::vec4(*pvertices, 0) * _matrix;

		*pvertices++ = glm::vec3(p.x, p.y, p.z);
	}
}


/*

*/
void GeometryGenerate::transformNormals()
{
	assert(_normals);

	glm::vec3 * pvertices = _normals;

	glm::mat3 normMatrix(_matrix);

	normMatrix = glm::transpose(glm::inverse(normMatrix));

	for (UInt32 i = 0; i < getVertexCount(); ++i)
	{
		*pvertices++ = glm::normalize(*pvertices * normMatrix);
	}

}