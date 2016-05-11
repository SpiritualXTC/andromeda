#include <andromeda/Geometry/geometry_generate.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>
#include <andromeda/Geometry/geometry_desc.h>

#include <andromeda/glm.h>
#include <glm/ext.hpp>

using namespace andromeda;


/*
	THERE IS A BUG IN THIS CODE WITH RESPECT TO THE CAPS and SLICE COUNTS
	DEBUG LATER
*/
std::shared_ptr<Geometry> andromeda::CreateEllipse(Float width, Float height, Float depth, Int32 slices, Int32 stacks, UInt32 genMask)
{
	Float w = width * 0.5f;
	Float h = height * 0.5f;
	Float d = depth * 0.5f;

	// Validation!
	Float pi = glm::pi<Float>();

	// Calculate Number of Vertices
	Int32 vertex_count = slices * stacks + 2 - slices;

	// Allocation
	glm::vec3 * position = new glm::vec3[vertex_count];
	glm::vec3 * normal = new glm::vec3[vertex_count];
	glm::vec2 * texture = new glm::vec2[vertex_count];


	Int32 vertex = 0;
	Int32 cap_neg = 0, cap_pos = 0;

	for (Int32 vst = 1; vst < stacks; vst++)
	{
		Float angle_st = (Float)vst / (Float)(stacks)* pi - pi * 0.5f;
		Float angle_st2 = (Float)vst / (Float)(stacks)* pi;

		for (Int32 vsl = 0; vsl < slices; vsl++)
		{
			Float angle_sl = (Float)vsl / (Float)(slices)* pi * 2.0f;

			// Calculate Position
			Float x = w * glm::cos(angle_st) * glm::cos(angle_sl);
			Float y = d * glm::sin(angle_st);
			Float z = h * glm::sin(angle_st2) * glm::sin(angle_sl);
			

			position[vertex] = glm::vec3(x, y, z);
			normal[vertex] = glm::normalize(glm::vec3(x, y, z));

			texture[vertex] = glm::vec2(vsl / (float)slices, vst / (float)stacks);

			vertex++;
		}
	}
	

	// Add Cap
	cap_neg = vertex++;
	cap_pos = vertex++;

	position[cap_neg] = glm::vec3(0, -h, 0);
	position[cap_pos] = glm::vec3(0, h, 0);

	normal[cap_pos] = glm::vec3(0, 1, 0);
	normal[cap_neg] = glm::vec3(0, -1, 0);

	texture[cap_pos] = glm::vec2(0, 0);	// This coordinate just doesn't exist properly in a fully indexed sphere
	texture[cap_neg] = glm::vec2(0, 0);	// This coordinate just doesn't exist properly in a fully indexed sphere



	// Indexing
	Int32 index = 0;
	Int32 index_count = (slices * (stacks - 2)) * 2 + slices * 2;

	index_count *= 3;

	UInt32 * indices = new UInt32[index_count];

	for (Int32 fst = 0; fst < stacks - 2; fst++)
	{
		for (Int32 fsl = 0; fsl < slices; fsl++)
		{
			//Int32 fsl = 0;
			UInt32 iA = (UInt32)(((fsl + 0) % (UInt32)slices) + (fst + 1) * (slices));
			UInt32 iB = (UInt32)(((fsl + 0) % (UInt32)slices) + (fst + 0) * (slices));
			UInt32 iC = (UInt32)(((fsl + 1) % (UInt32)slices) + (fst + 1) * (slices));
			UInt32 iD = (UInt32)(((fsl + 1) % (UInt32)slices) + (fst + 0) * (slices));

			indices[index++] = iA;
			indices[index++] = iB;
			indices[index++] = iC;

			indices[index++] = iC;
			indices[index++] = iB;
			indices[index++] = iD;
		}
	}

	//::	caps
	for (Int32 fsl = 0; fsl < slices; fsl++)
	{
		//Neg-Cap
		UInt32 capA = (fsl + 1) % (UInt32)slices;
		UInt32 capB = (fsl + 0) % (UInt32)slices;
		
		indices[index++] = cap_neg;
		indices[index++] = capA;
		indices[index++] = capB;

		//Pos-Cap
		UInt32 capC = (fsl + 0) % (UInt32)slices;
		UInt32 capD = (fsl + 1) % (UInt32)slices;
		UInt32 capBase = cap_pos - 1 - (UInt32)slices;

		indices[index++] = cap_pos;
		indices[index++] = capBase + capC;
		indices[index++] = capBase + capD;
	}









	// Add Vertex Data
	GeometryBuilder gb;
	gb.addVertexData("pos", position, vertex_count, GeometryLocation::Position);

	if (genMask & GEN_NORMALS)
		gb.addVertexData("norm", normal, vertex_count, GeometryLocation::Normal);

	if (genMask & GEN_TEXTURE)
		gb.addVertexData("tex", texture, vertex_count, GeometryLocation::Texture0);

	// Set Index Data
	gb.setIndexData(indices, index_count);

	// Build Geometry
	std::shared_ptr<Geometry> geometry = gb.build();

	// Delete Buffers
	if (indices)
		delete[] indices;

	// Deallocate
	if (texture)
		delete[] texture;
	if (normal)
		delete[] normal;
	if (position)
		delete[] position;

	// Return 
	return geometry;
}