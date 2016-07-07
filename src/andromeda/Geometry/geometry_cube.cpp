#include <andromeda/Geometry/geometry_cube.h>

using namespace andromeda;
using namespace andromeda::geometry;


/*

*/
Cube::Cube()
{

}

/*

*/
Cube::Cube(Float f)
	: _width(f)
	, _height(f)
	, _depth(f)
{

}


/*

*/
Cube::Cube(Float fw, Float fh, Float fd)
	: _width(fw)
	, _height(fh)
	, _depth(fd)
{

}


/*

*/
void Cube::buildPosition(glm::vec3 * pvertices, UInt32 count)
{
	glm::vec3 position[VERTICES] = 
	{
		// Pos Z
		{ -1, 1, 1 }, { 1, 1, 1 }, { -1, -1, 1 }, { 1, -1, 1 },

		// Neg X
		{ -1, 1, -1 }, { -1, 1, 1 }, { -1, -1, -1 }, { -1, -1, 1 },

		// Neg Z
		{ 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 },

		// Pos X
		{ 1, 1, 1 }, { 1, 1, -1 }, { 1, -1, 1 }, { 1, -1, -1 },

		// Pos Y
		{ -1, 1, -1 }, { 1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 },

		// Neg Y
		{ -1, -1, 1 }, { 1, -1, 1 }, { -1, -1, -1 }, { 1, -1, -1 }
	};

	glm::vec3 size = glm::vec3(_width * 0.5f, _height * 0.5f, _depth * 0.5f);

	for (Int32 i = 0; i < VERTICES; ++i)
	{
		*pvertices++ = position[i] * size;
	}
}


/*

*/
void Cube::buildNormals(glm::vec3 * pvertices, UInt32 count)
{
	glm::vec3 normal[SIDES] =
	{
		// Pos Z - Back
		{ 0, 0, 1 },
		
		// Neg X - Left
		{ -1, 0, 0 },

		// Neg Z - Front
		{ 0, 0, -1 },

		// Pos X - Right
		{ 1, 0, 0 },

		// Pos Y - Top
		{ 0, 1, 0 },

		// Neg Y - Bottom
		{ 0, -1, 0 }
	};


	for (Int32 i = 0; i < SIDES; ++i)
	{
		for (Int32 j = 0; j < VERTICES_PER_SIDE; ++j)
			*pvertices++ = normal[i];
	}


}


/*

*/
void Cube::buildTexCoords(glm::vec2 * pvertices, UInt32 count)
{
	glm::vec2 tex[VERTICES_PER_SIDE] = { { 0, 1 }, { 1, 1 }, { 0, 0 }, { 1, 0 } };

	for (Int32 i = 0; i < SIDES; ++i)
	{
		for (Int32 j = 0; j < VERTICES_PER_SIDE; ++j)
			*pvertices++ = tex[j];
	}
}


/*

*/
void Cube::buildIndices(UInt32 * pindices, UInt32 count)
{
	UInt32 indices[INDICES_PERS_SIDE] = { 0, 1, 2, 2, 1, 3};
	UInt32 offset = 0;

	for (Int32 i = 0; i < SIDES; ++i)
	{
		for (Int32 j = 0; j < INDICES_PERS_SIDE; ++j)
			*pindices++ = indices[j] + offset;
		
		offset += VERTICES_PER_SIDE;
	}
}
