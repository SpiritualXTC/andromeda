#include <andromeda/Graphics/geometry.h>

#include <cassert>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/geometry_desc.h>

using namespace andromeda;


/*

*/
Geometry::Geometry()
{

}


/*

*/
Geometry::Geometry(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<GeometryDescription> desc, std::shared_ptr<IndexBuffer> ib)
{
	_vertexBuffer = vb;
	_description = desc;
	_indexBuffer = ib;
}


/*

*/
Geometry::~Geometry()
{

}


/*

*/
void Geometry::render()
{
	assert(_vertexBuffer);

	// Bind VB
	_vertexBuffer->bind();

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
	_vertexBuffer->unbind();
}















