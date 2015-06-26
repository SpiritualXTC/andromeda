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
		GeometryDescription(const GLenum mode, const Int32 length);
		virtual ~GeometryDescription();


		void begin();
		void end();

		const inline Int32 length() const { return _length; }
		const inline Int32 stride() const { return _stride; }
		const inline GLenum mode() const { return _primitiveType; }


		Boolean addDeclaration(const Int32 elements, const Int32 offset, const GLenum datatype, const Int32 stride, const Int32 location = -1);

	private:
		Int32 _length = 0;
		Int32 _stride = 0;

		GLenum _primitiveType = GL_TRIANGLES;


		std::list<_GeometryDeclaration> _declaration;
	};
}

#endif