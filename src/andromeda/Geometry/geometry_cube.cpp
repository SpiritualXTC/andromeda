#include <andromeda/Geometry/geometry_generate.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>
#include <andromeda/Geometry/geometry_desc.h>

#include <andromeda/glm.h>
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
		{ -w, h, d }, { w, h, d }, { -w, -h, d }, { w, -h, d },

		// Neg X
		{ -w, h, -d }, { -w, h, d }, { -w, -h, -d }, { -w, -h, d },

		// Neg Z
		{ w, h, -d }, { -w, h, -d }, { w, -h, -d }, { -w, -h, -d },

		// Pos X
		{ w, h, d }, { w, h, -d }, { w, -h, d }, { w, -h, -d },

		// Pos Y
		{ -w, h, -d }, { w, h, -d }, { -w, h, d }, { w, h, d },

		// Neg Y
		{ -w, -h, d }, { w, -h, d }, { -w, -h, -d }, { w, -h, -d },
	};

	glm::vec3 normal[] = 
	{
		{ 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 },
		{ -1, 0, 0 }, { -1, 0, 0 }, { -1, 0, 0 }, { -1, 0, 0 },
		{ 0, 0, -1 }, { 0, 0, -1 }, { 0, 0, -1 }, { 0, 0, -1 },
		{ 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 },
		{ 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 },
		{ 0, -1, 0 }, { 0, -1, 0 }, { 0, -1, 0 }, { 0, -1, 0 }
	};

	glm::vec2 texture[] = 
	{
		{ 0, 1 }, { 1, 1 }, { 0, 0 }, {1, 0 },
		{ 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 0 },
		{ 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 0 },
		{ 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 0 },
		{ 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 0 },
		{ 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 0 }
	};



	UInt32 indices[] =
	{
		0, 1, 2, 2, 1, 3,
		4, 5, 6, 6, 5, 7,
		8, 9, 10, 10, 9, 11,
		12, 13, 14, 14, 13, 15,
		16, 17, 18, 18, 17, 19,
		20, 21, 22, 22, 21, 23
	};



	// Add Vertex Data
	GeometryBuilder gb;

	//gb.addVertexData("pos", position, 36);	// Non-indexed version
	gb.addVertexData("pos", position, 24, GeometryLocation::Position);

	if (genMask & GEN_NORMALS)
		gb.addVertexData("norm", normal, 24, GeometryLocation::Normal);

	if (genMask & GEN_TEXTURE)
		gb.addVertexData("tex", texture, 24, GeometryLocation::Texture0);

	gb.setIndexData(indices, 36);

	// Build Geometry
	return gb.build();
}