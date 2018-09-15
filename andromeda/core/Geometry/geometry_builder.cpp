#include "geometry_builder.h"

#include <Common/log.h>
#include <Core/Graphics/mesh.h>

//#include "geometry.h"
//#include "geometry_desc.h"



//#include <andromeda/andromeda.h>
//#include <andromeda/graphics.h>

using namespace andromeda;


/*

*/
GeometryBuilder::GeometryBuilder()
{

}


/*

*/
GeometryBuilder::~GeometryBuilder()
{

}



/*

*/
void GeometryBuilder::addVertexData(const std::string & id, void * data, Size length, Size stride, Size elements, DataType type, VertexAttribute attribute)
{
	Size bytes = length * stride;

	// Copy everything to a vector
	std::vector<UInt8> vector((UInt8*)data, (UInt8*)data + bytes);

	// IF TRIM == true AND stride != elements * elementSize
	// Copy to the vector manually :S

	// Setup Geometry
	_VertexData geometry;

	// Move data to the structture
	geometry.id = id;

	geometry.attribute = attribute;
	geometry.length = length;
	geometry.stride = stride;
	geometry.elements = elements;

	geometry.dataType = type;
	geometry.data = std::move(vector);

	
	// Maximum Length of Array
	if (geometry.length >= _length)
		_length = geometry.length;

	// Total Stride
	_stride += geometry.stride;

	// Add to List
	_geometry.push_back(geometry);
}



/*
	Set Index Data
*/
void GeometryBuilder::setIndexData(UInt32 * indices, Size length)
{
	// Copy Everything to a Vector
	std::vector<UInt32> vector(indices, indices + length);

	_indices = std::move(vector);

	return;
}



#if 0
/*

*/
Boolean GeometryBuilder::build(std::shared_ptr<IVertexBuffer> vb, std::shared_ptr<IGeometryDescription> desc, std::shared_ptr<IIndexBuffer> ib)
{
	// Interleave Vertices
	Boolean b = interleave(vb, desc);

	// Copy Index Data :: If their is any to copy
	if (ib && _indices.size() > 0)
		ib->data(&_indices[0], _indices.size() * sizeof(UInt32));

	return b;
}
#endif


/*

*/
std::shared_ptr<Mesh> GeometryBuilder::build()
{
	// Create Mesh
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

	if (_indices.size() > 0)
		mesh->setIndexBufferData(&_indices[0], _indices.size() * sizeof(UInt32));

	interleave(mesh);

	// Create Default Subset
	mesh->addGeometry(_length, _indices.size());

	// Create Geometry
	return mesh;
}


/*

*/
Boolean GeometryBuilder::interleave(std::shared_ptr<Mesh> mesh)
{
	assert(mesh);

	Size len = length();
	Int32 str = stride();

	UInt32 geomIndex = 0;

	// Create Array
	UInt32 bytes = str * len;
	UInt8 * data = new UInt8[bytes];
	
	UInt32 offset = 0;

	// Build Interleaved Array
	for (auto gd : _geometry)
	{
		Int32 pos = offset;

		// Pointer to data to Interleave
		UInt8 * ptr = (UInt8*)&gd.data[0];

		// Pointer to interleaved data
		UInt8 * pdata = data;
		pdata += offset;

		// Loop over all the vertices
		for (UInt32 i = 0; i < gd.length; ++i)
		{
			// Copy
			memcpy((void*)pdata, (void*)ptr, gd.stride);

			// Increment Position
			pos += str;

			// Update Pointers
			ptr += gd.stride;
			pdata += str;
		}


		// Add the Description
		if (mesh)
			mesh->addDeclaration(gd.elements, /*offset,*/ gd.dataType, gd.stride, gd.attribute);

		// Increase Starting Offset by the Vertex's 
		offset += gd.stride;
	}


	// Set Vertex Data
	mesh->setVertexBufferData(data, bytes);

	delete data;

	return true;
}



