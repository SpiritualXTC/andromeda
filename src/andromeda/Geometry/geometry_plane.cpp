#include <andromeda/Geometry/geometry_generate.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>
#include <andromeda/Geometry/geometry_desc.h>


#include <glm/glm.hpp>


using namespace andromeda;


/*
	This is not the final plane code.
	It should support axis selection
*/
std::shared_ptr<Geometry> andromeda::CreatePlane(Float width, Float height, UInt32 genMask)
{
	const Float w = width * 0.5f;
	const Float d = height * 0.5f;

	glm::vec3 position[] =
	{
		// Pos Y
		{ -w, 0.0f, -d }, 
		{ w, 0.0f, -d }, 
		{ -w, 0.0f, d },
		{ w, 0.0f, d },
	};



	UInt32 indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};


	// Add Vertex Data
	GeometryBuilder gb;
	gb.addVertexData("pos", position, 4);

	// Create Buffers
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>();
	std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>();
	
	std::shared_ptr<GeometryDescription> desc = std::make_shared<GeometryDescription>(GL_TRIANGLES, 4, 6, GL_UNSIGNED_INT);


	ib->data(indices, 6 * sizeof(UInt32));
	
	// Interleave Data amongst buffers
	gb.build(vb, desc);

	// Create Geometry Object
	return std::make_shared<Geometry>(vb, desc, ib);
}