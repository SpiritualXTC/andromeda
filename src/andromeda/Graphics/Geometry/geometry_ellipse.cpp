#include <andromeda/Graphics/geometry_builder.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/geometry.h>
#include <andromeda/Graphics/geometry_desc.h>

#include <glm/glm.hpp>

using namespace andromeda;


std::shared_ptr<Geometry> andromeda::CreateEllipse(Float width, Float height, Float depth, Int32 slices, Int32 stacks, UInt32 genMask)
{
	Int32 vertex_count = slices * stacks + 2 - slices;

	glm::vec3 * position = new glm::vec3[vertex_count];





	// Add Vertex Data
	GeometryBuilder gb;
	gb.addVertexData("pos", position, vertex_count);



	// Delete Buffers
	if (position)
		delete[] position;



	// Create Buffers
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>();
	std::shared_ptr<GeometryDescription> desc = std::make_shared<GeometryDescription>(GL_TRIANGLES, vertex_count);

	// Interleave Data amongst buffers
	gb.interleave(vb, desc);

	// Create Geometry Object
	return std::make_shared<Geometry>(vb, desc, nullptr);
}