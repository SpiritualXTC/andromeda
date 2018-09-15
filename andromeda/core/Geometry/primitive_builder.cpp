#include "primitive_builder.h"

using namespace andromeda;
using namespace andromeda::geometry;


/*

*/
void PrimitiveBuilder::setPrimitiveType(PrimitiveMode primType)
{
	_primType = primType;

	_firstVertex = VERTEX_UNSET;
	_secondVertex = VERTEX_UNSET;
}


/*

*/
void PrimitiveBuilder::addVertex(const glm::dvec3 & v)
{
	// Get Current Index
	Int32 index = _vertices.size();

	// Add Vertex
	_vertices.push_back(glm::vec3(v));


	if (_primType == PrimitiveMode::Triangles)
	{
		addIndexToTriangleList(index);
	}
	else if (_primType == PrimitiveMode::TriangleStrip)
	{
		addIndexToTriangleStrip(index);
	}
	else if (_primType == PrimitiveMode::TriangleFan)
	{
		addIndexToTriangleFan(index);
	}
}


/*

*/
void PrimitiveBuilder::addIndexToTriangleList(UInt32 index)
{
	if (_firstVertex == VERTEX_UNSET)
	{
		_firstVertex = index;
	}
	else if (_secondVertex == VERTEX_UNSET)
	{
		_secondVertex = index;
	}
	else
	{
		_faces.push_back(_firstVertex);
		_faces.push_back(_secondVertex);
		_faces.push_back(index);

		_firstVertex = VERTEX_UNSET;
		_secondVertex = VERTEX_UNSET;
	}
}

/*

*/
void PrimitiveBuilder::addIndexToTriangleFan(UInt32 index)
{
	if (_firstVertex == VERTEX_UNSET)
	{
		_firstVertex = index;
	}
	else if (_secondVertex == VERTEX_UNSET)
	{
		_secondVertex = index;
	}
	else
	{
		_faces.push_back(_firstVertex);
		_faces.push_back(_secondVertex);
		_faces.push_back(index);

		_secondVertex = index;
	}
}

/*

*/
void PrimitiveBuilder::addIndexToTriangleStrip(UInt32 index)
{
	if (_firstVertex == VERTEX_UNSET)
	{
		_firstVertex = index;
	}
	else if (_secondVertex == VERTEX_UNSET)
	{
		_secondVertex = index;
	}
	else
	{
		_faces.push_back(_firstVertex);
		_faces.push_back(_secondVertex);
		_faces.push_back(index);

		_firstVertex = _secondVertex;
		_secondVertex = index;
	}
}


/*

*/
glm::dvec3 & PrimitiveBuilder::cache(const glm::dvec3 & v)
{
	_cache.push_back(v);
	
	return _cache.back();
}