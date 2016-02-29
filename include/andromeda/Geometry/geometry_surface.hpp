#ifndef _ANDROMEDA_GRAPHICS_GEOMETRY_SURFACE_HPP_
#define _ANDROMEDA_GRAPHICS_GEOMETRY_SURFACE_HPP_

namespace andromeda
{
	template <typename T>
	std::shared_ptr<Geometry> CreateSurface(Float minX, Float minY, Float maxX, Float maxY, Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const T *)> generator, const T * data)
	{
		// Create Vertices
		Int32 vertex = 0;
		Int32 vertex_count = (divX + 1) * (divY + 1);
		glm::vec3 * position = new glm::vec3[vertex_count];
		glm::vec3 * normal = new glm::vec3[vertex_count];
		glm::vec2 * texture = new glm::vec2[vertex_count];

		Float stepX = (maxX - minX) / divX;
		Float stepY = (maxY - minY) / divY;

		for (Int32 j = 0; j <= divY; ++j)
		{
			for (Int32 i = 0; i <= divX; ++i)
			{
				Float x = ((Float)i / divX) * (maxX - minX) + minX;
				Float y = ((Float)j / divY) * (maxY - minY) + minY;

				glm::vec3 p(0.0f);

				// Run Callback!
				if (generator)
				{
					/* call the passed function to generate the position from the given inputs */
					p = generator(x, y, data);
				}
				else
				{
					/* Default Behaviour (A Grid - woooo) */
					p.x = x;
					p.y = 0.0f;
					p.z = y;
				}

				// Set Position
				position[vertex] = p;
				normal[vertex] = glm::vec3(0, 1, 0);

				texture[vertex] = glm::vec2((Float)i / divX, (Float)j / divY);

				vertex++;
			}
		}

		// Generate Indices
		// Indexing
		Int32 index = 0;
		Int32 index_count = divX * divY * 2 * 3;

		UInt32 * indices = new UInt32[index_count];

		for (Int32 j = 0; j < divY; j++)
		{
			for (Int32 i = 0; i < divX; i++)
			{
				UInt32 iA = (UInt32)((i + 1) + (j + 1) * (divX + 1));
				UInt32 iB = (UInt32)((i + 1) + (j + 0) * (divX + 1));
				UInt32 iC = (UInt32)((i + 0) + (j + 1) * (divX + 1));
				UInt32 iD = (UInt32)((i + 0) + (j + 0) * (divX + 1));


				indices[index++] = iA;
				indices[index++] = iB;
				indices[index++] = iC;

				indices[index++] = iC;
				indices[index++] = iB;
				indices[index++] = iD;
			}
		}

		// Add Vertex Data
		GeometryBuilder gb;
		gb.addVertexData("pos", position, vertex_count);

		if (genMask & andromeda::GEN_NORMALS)
			gb.addVertexData("pos", normal, vertex_count);

		if (genMask & andromeda::GEN_TEXTURE)
			gb.addVertexData("pos", texture, vertex_count);

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

		if (texture)
			delete[] texture;

		if (normal)
			delete[] normal;

		if (position)
			delete[] position;

		// Create Geometry Object
		return std::make_shared<Geometry>(vb, desc, ib);
	}
}

#endif