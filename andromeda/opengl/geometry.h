#pragma once

#include <list>
#include <memory>


#include <core/Graphics/types.h>
#include <core/Graphics/geometry.h>

#include <GL/glew.h>

namespace andromeda
{
	namespace opengl
	{
		struct GeometryDeclaration
		{
			Int32 attribute;

			Int32 elements;
			Int32 offset;

			DataType dataType;
			GLenum glDataType;
		};

		struct GeometrySubset
		{
			Int32 vertices;
			Int32 indices;
			Int32 offset;
		};

		class GeometryGL : public IGeometry
		{
		public:
			GeometryGL(PrimitiveMode mode, IndexType indexType);
			virtual ~GeometryGL();

			Int32 stride() override { return _stride; }

			Int32 vertices() override { return _vertices; }
			Int32 indices() override { return _indices; }
			Int32 subsets() override { return _subsets.size(); }

			IndexType indexType() override { return _indexType; }
			PrimitiveMode mode() override { return _primitiveMode; }

			Boolean addGeometry(Int32 vertices, Int32 indices);
			Boolean addDeclaration(Int32 elements, DataType datatype, Int32 stride, VertexAttribute attribute = VertexAttribute::Auto);

			Boolean begin() override;
			Boolean end() override;
			
			Boolean render() override;
			Boolean render(Int32 subset) override;

		private:
			Int32 _stride = 0;

			Int32 _vertices = 0;
			Int32 _indices = 0;

			PrimitiveMode _primitiveMode = PrimitiveMode::Triangles;
			IndexType _indexType = IndexType::None;

			GLenum _glPrimitiveMode = GL_NONE;
			GLenum _glIndexType = GL_NONE;

			std::list<GeometryDeclaration> _declaration;
			std::list<GeometrySubset> _subsets;
		};
	}
}