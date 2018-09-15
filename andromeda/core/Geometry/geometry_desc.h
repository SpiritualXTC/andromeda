#pragma once

#if 0
#include <list>

#include <Common/types.h>
#include <core/Graphics/types.h>
//#include <andromeda/opengl.h>

#include "geometry_builder.h"	//for GeometryLocation

namespace andromeda
{

	/*
		TODO:
		Remove the GL-centric enums.
	*/
	class GeometryDescription
	{
	private:
		struct _GeometryDeclaration
		{
			Int32 location;
	
			Int32 elements;
			Int32 offset;

			//GLenum dataType;
			DataType dataType;
		};


	public:
		GeometryDescription(const PrimitiveMode mode, const Int32 vertices);
		GeometryDescription(const PrimitiveMode mode, const Int32 vertices, const Int32 indices, const IndexType indexType = IndexType::UnsignedInt);

		virtual ~GeometryDescription();


		void begin();
		void end();


		/*
			Vertex Size
		*/
		const inline Int32 stride() const { return _stride; }

		/*
			Vertex Count
		*/
		const inline Int32 vertices() const { return _vertices; }

		/*
			Index Count
		*/
		const inline Int32 indices() const { return _indices; }

		/*
			Index Format
		*/
		const inline IndexType indexType() const { return _indexType; }


		/*
			Primitive mode
		*/
		const inline PrimitiveMode mode() const { return _primitiveType; }


		Boolean addDeclaration(const Int32 elements, const DataType dataType, const Int32 stride, const GeometryLocation location = GeometryLocation::Auto);
		Boolean addDeclaration(const Int32 elements, const Int32 offset, const DataType datatype, const Int32 stride, const GeometryLocation location = GeometryLocation::Auto);

	private:
		Int32 _stride = 0;

		Int32 _vertices = 0;
		Int32 _indices = 0;

		//GLenum _primitiveType = GL_TRIANGLES;
		PrimitiveMode _primitiveType = PrimitiveMode::Triangles;
		IndexType _indexType = IndexType::None;

		std::list<_GeometryDeclaration> _declaration;
	};
}
#endif