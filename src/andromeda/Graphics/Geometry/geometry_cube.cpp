#include <andromeda/Graphics/geometry_builder.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/geometry.h>
#include <andromeda/Graphics/geometry_desc.h>

#include <glm/glm.hpp>

using namespace andromeda;

/*

*/
std::shared_ptr<Geometry> andromeda::CreateCube(Float width, Float height, Float depth, UInt32 genMask)
{
	const Float w = width * 0.5f;
	const Float h = height * 0.5f;
	const Float d = depth * 0.5f;

	glm::vec3 position[] =
	{
		// Pos Z
		{ -w, h, d },{ w, h, d },{ -w, -h, d },
		{ -w, -h, d },{ w, h, d },{ w, -h, d },

		// Neg X
		{ -w, h, -d },{ -w, h, d },{ -w, -h, -d },
		{ -w, -h, -d },{ -w, h, d },{ -w, -h, -d },

		// Neg Z
		{ w, h, -d },{ -w, h, -d },{ w, -h, -d },
		{ w, -h, -d },{ -w, h, -d },{ -w, -h, -d },

		// Pos X
		{ w, h, d },{ w, h, -d },{ w, -h, d },
		{ w, -h, d },{ w, h, -d },{ w, -h, d },

		// Pos Y
		{ -w, h, -d },{ w, h, -d },{ -w, h, d },
		{ -w, h, d },{ w, h, -d },{ w, h, d },

		// Neg Y
		{ -w, -h, d },{ w, -h, d },{ -w, -h, -d },
		{ -w, -h, -d },{ w, -h, d },{ w, -h, -d },
	};


	// Add Vertex Data
	GeometryBuilder gb;
	gb.addVertexData("pos", position, 36);

	// Create Buffers
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>();
	std::shared_ptr<GeometryDescription> desc = std::make_shared<GeometryDescription>(GL_TRIANGLES, 36);
	
	// Interleave Data amongst buffers
	gb.interleave(vb, desc);

	// Create Geometry Object
	return std::make_shared<Geometry>(vb, desc, nullptr);
}