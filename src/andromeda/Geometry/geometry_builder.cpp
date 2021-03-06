#include <andromeda/Geometry/geometry_builder.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_desc.h>

#include <andromeda/Utilities/log.h>

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

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
void GeometryBuilder::addVertexData(const std::string & id, void * data, Size length, Size stride, Size elements, GLenum type, const GeometryLocation location)
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
	
	geometry.location = location;
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




/*

*/
Boolean GeometryBuilder::build(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<GeometryDescription> desc, std::shared_ptr<IndexBuffer> ib)
{
	// Interleave Vertices
	Boolean b = interleave(vb, desc);

	// Copy Index Data :: If their is any to copy
	if (ib && _indices.size() > 0)
		ib->data(&_indices[0], _indices.size() * sizeof(UInt32));

	return b;
}


/*

*/
std::shared_ptr<Geometry> GeometryBuilder::build()
{
	// Create Buffers
//	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>();
//	std::shared_ptr<IndexBuffer> ib = _indices.size() == 0 ? nullptr : std::make_shared<IndexBuffer>();

	std::shared_ptr<VertexBuffer> vb = andromeda::graphics()->createVertexBuffer();
	std::shared_ptr<IndexBuffer> ib;
	
	if (_indices.size() > 0)
		ib = andromeda::graphics()->createIndexBuffer();


	std::shared_ptr<GeometryDescription> desc = std::make_shared<GeometryDescription>(GL_TRIANGLES, _length, _indices.size(), GL_UNSIGNED_INT);

	// Build
	build(vb, desc, ib);

	// Create Geometry
	return std::make_shared<Geometry>(vb, desc, ib);
}


/*

*/
Boolean GeometryBuilder::interleave(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<GeometryDescription> desc)
{
	assert(vb);

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
		if (desc)
			desc->addDeclaration(gd.elements, offset, gd.dataType, gd.stride, gd.location);

		// Increase Starting Offset by the Vertex's 
		offset += gd.stride;
	}


	// Set Vertex Data
	vb->data(data, bytes);

	delete data;

	return true;
}



