#pragma once

#include <common/types.h>
#include "types.h"

namespace andromeda
{
	class IVertexBuffer;
	class IIndexBuffer;
	class IDeclaration;	//?

	enum class VertexAttribute
	{
		Position,
		Normal,
		Texture0,
		Texture1,

		Color,


		Auto = 0xFF,
	};

	class IGeometry
	{
	public:
		IGeometry() {}
		virtual ~IGeometry() {}

		virtual Int32 stride() = 0;

		virtual Int32 vertices() = 0;
		virtual Int32 indices() = 0;
		virtual Int32 subsets() = 0;

		virtual IndexType indexType() = 0;

		virtual PrimitiveMode mode() = 0;

		// TODO: Use unsigned
		virtual Boolean addDeclaration(Int32 elements, DataType dataType, Int32 stride, VertexAttribute attribute = VertexAttribute::Auto) = 0;
		virtual Boolean addGeometry(Int32 vertices, Int32 indices) = 0;

		virtual Boolean begin() = 0;
		virtual Boolean end() = 0;

		virtual Boolean render() = 0;
		virtual Boolean render(Int32 subset) = 0;

		/*
		virtual Boolean nextSubset() = 0;
		*/
	private:
	};

#if 0
	class IGeometry
	{
	public:
		IGeometry(){}
		virtual ~IGeometry() {}

		virtual Boolean render() = 0;

	private:

	};
#endif
}
