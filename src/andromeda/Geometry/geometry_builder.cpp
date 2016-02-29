#include <andromeda/Geometry/geometry_builder.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_desc.h>

#include <andromeda/Utilities/log.h>

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

*/
Boolean GeometryBuilder::build(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<GeometryDescription> desc, std::shared_ptr<IndexBuffer> ib)
{
	// Interleave Vertices
	Boolean b = interleave(vb, desc);

	



	return b;
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



