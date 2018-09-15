#pragma once

#include <memory>

#include "geometry.h"

namespace andromeda
{

	class IVertexBuffer;
	class IIndexBuffer;
	class IGeometry;

	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh();

		Boolean setVertexBufferData(const void* ptr, UInt32 length);
		Boolean setIndexBufferData(const void* ptr, UInt32 length);

		// TODO: Piggy backing for now
		Boolean addDeclaration(Int32 elements, DataType dataType, Int32 stride, VertexAttribute attribute = VertexAttribute::Auto);
		Boolean addGeometry(Int32 vertices, Int32 indices);


		Boolean render();
		Boolean render(Int32 subset);

	private:
		std::shared_ptr<IVertexBuffer> _vertices;
		std::shared_ptr<IIndexBuffer> _indices;
		std::shared_ptr<IGeometry> _geometry;
	};
}