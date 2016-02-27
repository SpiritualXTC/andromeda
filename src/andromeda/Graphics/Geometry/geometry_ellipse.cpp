#include <andromeda/Graphics/geometry_generate.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/geometry.h>
#include <andromeda/Graphics/geometry_builder.h>
#include <andromeda/Graphics/geometry_desc.h>


#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace andromeda;


std::shared_ptr<Geometry> andromeda::CreateEllipse(Float width, Float height, Float depth, Int32 slices, Int32 stacks, UInt32 genMask)
{
	Float w = width * 0.5f;
	Float h = height * 0.5f;
	Float d = depth * 0.5f;

	// Validation!
	Float pi = glm::pi<Float>();


	Int32 vertex_count = slices * stacks + 2 - slices;

	glm::vec3 * position = new glm::vec3[vertex_count];

	Int32 vertex = 0;

	Int32 cap_neg = 0, cap_pos = 0;

	for (Int32 vst = 1; vst < stacks; vst++)
	{
		Float angle_st = (Float)vst / (Float)(stacks)* pi - pi * 0.5f;
		Float angle_st2 = (Float)vst / (Float)(stacks)* pi;

		for (Int32 vsl = 0; vsl < slices; vsl++)
		{
			Float angle_sl = (Float)vsl / (Float)(slices)* pi * 2.0f;

			Float x = w * glm::cos(angle_st) * glm::cos(angle_sl);
			Float y = d * glm::sin(angle_st);
			Float z = h * glm::sin(angle_st2) * glm::sin(angle_sl);
			

			/*
			float nx = (float)(Math.Cos(angle_st) * Math.Cos(angle_sl));
			float ny = (float)(Math.Sin(angle_st));
			float nz = (float)(Math.Sin(angle_st2) * Math.Sin(angle_sl));
			float tu = (float)vst / (float)(stacks);
			float tv = (float)vsl / (float)(slices);
			*/

			position[vertex] = glm::vec3(x, y, z);


			vertex++;
		}
	}
	

	// Add Cap
	cap_neg = vertex++;
	cap_pos = vertex++;

	//position[cap_neg] = glm::vec3(0, 0, -depth);// *0.5f, 0, 0, -1, 0, 0);
	//position[cap_pos] = glm::vec3(0, 0, depth);// *0.5f, 0, 0, 1, 0, 0);

	position[cap_neg] = glm::vec3(0, -h, 0);// *0.5f, 0, 0, -1, 0, 0);
	position[cap_pos] = glm::vec3(0, h, 0);// *0.5f, 0, 0, 1, 0, 0);



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

		//	fa[fi++] = new Face(iA, iB, iC);
		//	fa[fi++] = new Face(iC, iB, iD);
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

		//fa[fi++] = new Face(cap_negz, capA, capB);

		//Pos-Cap
		UInt32 capC = (fsl + 0) % (UInt32)slices;
		UInt32 capD = (fsl + 1) % (UInt32)slices;
		UInt32 capBase = cap_pos - 1 - (UInt32)slices;

		indices[index++] = cap_pos;
		indices[index++] = capBase + capC;
		indices[index++] = capBase + capD;

		//fa[fi++] = new Face(cap_posz, capBase + capC, capBase + capD);
	}









	// Add Vertex Data
	GeometryBuilder gb;
	gb.addVertexData("pos", position, vertex_count);

	// Create Buffers
	std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>();
	std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>();
	std::shared_ptr<GeometryDescription> desc = std::make_shared<GeometryDescription>(GL_TRIANGLES, vertex_count, index_count, GL_UNSIGNED_INT);

	// Copy Index Data
	ib->data(indices, index_count * sizeof(UInt32));

	// Interleave Data amongst buffers
	gb.build(vb, desc);

	// Delete Buffers
	if (indices)
		delete[] indices;

	if (position)
		delete[] position;

	// Create Geometry Object
	return std::make_shared<Geometry>(vb, desc, ib);
}