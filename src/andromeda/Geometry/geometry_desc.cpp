#include <andromeda/Geometry/geometry_desc.h>

using namespace andromeda;


/*

*/
GeometryDescription::GeometryDescription(const GLenum mode, const Int32 vertices)
	: _primitiveType(mode)
	, _vertices(vertices)
	, _indices(0)
	, _indexType(GL_NONE)
{

}


/*

*/
GeometryDescription::GeometryDescription(const GLenum mode, const Int32 vertices, const Int32 indices, const GLenum indexType)
	: _primitiveType(mode)
	, _vertices(vertices)
	, _indices(indices)
	, _indexType(indexType)
{

}


/*

*/
GeometryDescription::~GeometryDescription()
{

}

/*

*/
Boolean GeometryDescription::addDeclaration(const Int32 elements, const GLenum dataType, const Int32 stride, const GeometryLocation location)
{
	/*
		Use the Current Stride as the Offset
	*/

	return addDeclaration(elements, _stride, dataType, stride, location);
}


/*

*/
//Boolean GeometryDescription::addDeclaration(const Int32 elements, const Int32 offset, const GLenum datatype, const Int32 stride, const Int32 location)
Boolean GeometryDescription::addDeclaration(const Int32 elements, const Int32 offset, const GLenum datatype, const Int32 stride, const GeometryLocation location)
{
	_GeometryDeclaration decl;

	if (location == GeometryLocation::Auto)
	{
		// This needs to be a little smarter :P
		// Needs to choose the first NON selected index
		decl.location = _declaration.size();
	}
	else
	{
		decl.location = (Int32)location;
	}


	decl.dataType = datatype;
	decl.offset = offset;		// This could be automatic :P back().offset + back().stride
	decl.elements = elements;

	_stride += stride;

	// Add Declaration
	_declaration.push_back(decl);

	return true;
}



/*

*/
void GeometryDescription::begin()
{
	for (auto decl : _declaration)
	{
		glEnableVertexAttribArray(decl.location);
		glVertexAttribPointer(decl.location, decl.elements, decl.dataType, false, _stride, (GLvoid*)decl.offset);
	}
}


/*

*/
void GeometryDescription::end()
{
	for (auto decl : _declaration)
	{
		glDisableVertexAttribArray(decl.location);
	}
}