#include "mesh.h"

using namespace andromeda;

Mesh::Mesh()
{

}

Mesh::~Mesh()
{

}

Boolean Mesh::setVertexBufferData(const void* ptr, UInt32 length)
{
	return true;
}

Boolean Mesh::setIndexBufferData(const void* ptr, UInt32 length)
{

	return true;
}

Boolean Mesh::render()
{
	return true;
}

Boolean Mesh::render(Int32 subset)
{
	return true;
}



Boolean Mesh::addDeclaration(Int32 elements, DataType dataType, Int32 stride, VertexAttribute attribute)
{
	if (!_geometry)
	{
		// TODO: Build Geometry Object
		return false;
	}
	_geometry->addDeclaration(elements, dataType, stride, attribute);
	return true;
}

Boolean Mesh::addGeometry(Int32 vertices, Int32 indices)
{
	if (!_geometry)
	{
		// TODO: Build Geometry Object
		return false;
	}
	_geometry->addGeometry(vertices, indices);
	return true;
}