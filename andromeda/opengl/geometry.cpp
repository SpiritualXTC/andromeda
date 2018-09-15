#include "geometry.h"

#include <GL/glew.h>

#include <core/Graphics/buffer.h>

#include "mapping.h"

using namespace andromeda;
using namespace andromeda::opengl;

GeometryGL::GeometryGL(PrimitiveMode mode, IndexType indexType)
	: _primitiveMode(mode)
	, _indexType(indexType)
{
	_glIndexType = convIndexDataType(_indexType);
	_glPrimitiveMode = convPrimitiveMode(_primitiveMode);
}

GeometryGL::~GeometryGL()
{

}

Boolean GeometryGL::addDeclaration(Int32 elements, DataType datatype, Int32 stride, VertexAttribute attribute)
{
	GeometryDeclaration decl;

	if (attribute == VertexAttribute::Auto)
	{
		// This needs to be a little smarter :P
		// Needs to choose the first NON selected attribute
		decl.attribute = _declaration.size();
	}
	else
	{
		decl.attribute = (Int32)attribute;
	}

	decl.dataType = datatype;
	decl.offset = _stride;//offset;
	decl.elements = elements;

	_stride += stride;

	_declaration.push_back(decl);
	return true;
}

Boolean GeometryGL::addGeometry(Int32 vertices, Int32 indices)
{
	GeometrySubset subset;

	// TODO: Some Assertions.
	// Can't add index data when no index data has been added previously, but vertex data has been.
	// Can't add no index data, when index data has been added previously
	assert(vertices);

	Int32 offset = 0;
	
	if (_subsets.size() > 0)
	{
		assert(!_indices && indices);
		assert(_indices && !indices);

		GeometrySubset& lastSubset = _subsets.back();
		offset = indices == 0 ? lastSubset.vertices : lastSubset.indices;
		offset += lastSubset.offset;
	}

	subset.vertices = vertices;
	subset.indices = indices;
	subset.offset = offset;

	_vertices += vertices;
	_indices += indices;

	_subsets.push_back(subset);
	return true;
}

Boolean GeometryGL::begin()
{
	for (auto decl : _declaration)
	{
		// TODO: This needs to be accounted for somewhere... when copying to a shader?
		glEnableVertexAttribArray(decl.attribute);
		glVertexAttribPointer(decl.attribute, decl.elements, decl.glDataType, false, _stride, (GLvoid*)decl.offset);
	}
	return true;
}

Boolean GeometryGL::end()
{
	for (auto decl : _declaration)
	{
		glDisableVertexAttribArray(decl.attribute);
	}
	return true;
}

Boolean GeometryGL::render()
{
	if (_indices == 0 || _indexType == IndexType::None)
		glDrawArrays(_glPrimitiveMode, 0, _vertices);
	else
		glDrawElements(_glPrimitiveMode, _indices, _glIndexType, 0);
	return true;
}

Boolean GeometryGL::render(Int32 subset)
{
	return true;
}


#if 0
Boolean GeometryGL::render()
{
	// Bind VB
//	_vertexBuffer->bind();

	// Set Attribute Options
	_description->begin();

	if (_indexBuffer)
	{
		// Bind IB
		_indexBuffer->bind();

		// Draw Indexed Primitives
		glDrawElements(_description->mode(), _description->indices(), _description->indexType(), 0);

		// Unbind IB
		_indexBuffer->unbind();
	}
	else
	{
		// Draw Primitives
		glDrawArrays(_description->mode(), 0, _description->vertices());
	}

	// Unset Attribute Options
	_description->end();

	// Unbind VB
//	_vertexBuffer->unbind();

	return true;
}
#endif