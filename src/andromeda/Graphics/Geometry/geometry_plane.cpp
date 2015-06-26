#include <andromeda/Graphics/geometry_builder.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/geometry.h>
#include <andromeda/Graphics/geometry_desc.h>

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
		{ -w, 0.0f, -d }, { w, 0.0f, -d }, { -w, 0.0f, d },
		{ -w, 0.0f, d }, { w, 0.0f, -d }, { w, 0.0f, d },
	};


	glm::vec3 normal[] = 
	{
		{ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }
	};


	// Add Vertex Data
	GeometryBuilder gb;
	gb.addVertexData("pos", position, 6);

	// Create Buffers
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>();
	std::shared_ptr<GeometryDescription> desc = std::make_shared<GeometryDescription>(GL_TRIANGLES, 6);

	// Interleave Data amongst buffers
	gb.interleave(vb, desc);

	// Create Geometry Object
	return std::make_shared<Geometry>(vb, desc, nullptr);
}