#include <andromeda/Graphics/geometry_builder.h>

using namespace andromeda;

GeometryBuilder::GeometryBuilder()
{

}

GeometryBuilder::~GeometryBuilder()
{

}



/*

*/
void GeometryBuilder::addVertexData(const std::string & id, void * data, Size length, Size stride, Size elements, GLenum type)
{
	Size bytes = length * stride;

	// Copy everything to a vector
	std::vector<Int8> vector((Int8*)data, (Int8*)data + bytes);

	// Setup Geometry
	_GeometryData geometry;


	// Move data to the structture
	geometry.id = id;
	
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
Boolean GeometryBuilder::interleave()
{

	return true;
}
