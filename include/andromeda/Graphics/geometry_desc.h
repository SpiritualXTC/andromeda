#ifndef _ANDROMEDA_GRAPHICS_GEOMETRY_DESC_H_
#define _ANDROMEDA_GRAPHICS_GEOMETRY_DESC_H_

#include <list>

#include "../stddef.h"

#include "opengl.h"

namespace andromeda
{


	class GeometryDescription
	{
	private:
		struct _GeometryDeclaration
		{
			Int32 location;

			Int32 elements;
			Int32 offset;

			GLenum dataType;
		};


	public:
		GeometryDescription(const GLenum mode, const Int32 vertices);
		GeometryDescription(const GLenum mode, const Int32 vertices, const Int32 indices, const GLenum indexType = GL_UNSIGNED_INT);

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
		const inline GLenum indexType() const { return _indexType; }


		/*
			Primitive mode
		*/
		const inline GLenum mode() const { return _primitiveType; }


		Boolean addDeclaration(const Int32 elements, const Int32 offset, const GLenum datatype, const Int32 stride, const Int32 location = -1);

	private:
		Int32 _stride = 0;

		Int32 _vertices = 0;
		Int32 _indices = 0;

		GLenum _primitiveType = GL_TRIANGLES;
		GLenum _indexType = GL_NONE;

		std::list<_GeometryDeclaration> _declaration;
	};
}

#endif