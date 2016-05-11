#include <andromeda/Geometry/geometry_generate.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>
#include <andromeda/Geometry/geometry_desc.h>

#include <andromeda/glm.h>


using namespace andromeda;


/*
	This is not the final plane code.
	It is going to be converted to using a proper plane equation, alongside the dimensions.

	Also needs to add texture/normal information
*/
std::shared_ptr<Geometry> andromeda::CreatePlane(Float width, Float height, UInt32 genMask)
{
	const Float w = width * 0.5f;
	const Float d = height * 0.5f;

	glm::vec3 position[] =
	{
		{ -w, 0.0f, -d }, 
		{ w, 0.0f, -d }, 
		{ -w, 0.0f, d },
		{ w, 0.0f, d },
	};

	glm::vec2 texture[] = 
	{
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};

	glm::vec3 normals[] = 
	{
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 }
	};


	UInt32 indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};

	// Multiply into plane equation ...


	// Add Vertex Data
	GeometryBuilder gb;
	gb.addVertexData("pos", position, 4, GeometryLocation::Position);

	if (genMask & GEN_NORMALS)
		gb.addVertexData("norm", normals, 4, GeometryLocation::Normal);

	if (genMask & GEN_TEXTURE)
		gb.addVertexData("tex", texture, 4, GeometryLocation::Texture0);
	
	// Set Index Data
	gb.setIndexData(indices, 6);

	// Build Geometry
	return gb.build();
}