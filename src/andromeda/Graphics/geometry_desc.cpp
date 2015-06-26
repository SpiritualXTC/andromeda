#include <andromeda/Graphics/geometry_desc.h>

using namespace andromeda;


/*

*/
GeometryDescription::GeometryDescription(const GLenum mode, const Int32 length)
	: _length(length)
	, _primitiveType(mode)
{

}


/*

*/
GeometryDescription::~GeometryDescription()
{

}


/*

*/
Boolean GeometryDescription::addDeclaration(const Int32 elements, const Int32 offset, const GLenum datatype, const Int32 stride, const Int32 location)
{
	_GeometryDeclaration decl;

	if (location == -1)
	{
		decl.location = _declaration.size();
	}

	decl.dataType = datatype;
	decl.offset = offset;
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