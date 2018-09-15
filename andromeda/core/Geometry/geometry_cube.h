#pragma once

#include "geometry_generate.h"

namespace andromeda
{
	namespace geometry
	{
		class Cube : virtual public GeometryGenerate
		{
		private:
			static const Int32 SIDES = 6;

			static const Int32 VERTICES_PER_SIDE = 4;
			static const Int32 FACES_PER_SIDE = 2;
			static const Int32 INDICES_PERS_SIDE = FACES_PER_SIDE * 3;

			static const Int32 VERTICES = SIDES * VERTICES_PER_SIDE;
			static const Int32 FACES = SIDES * FACES_PER_SIDE;
			static const Int32 INDICES = FACES * 3;
	
		public:
			Cube();
			Cube(Float f);
			Cube(Float fw, Float fh, Float fd);
			
			UInt32 getVertexCount() const override
			{
				return VERTICES;
			}
			UInt32 getFaceCount() const override
			{
				return FACES;
			}



			Cube & setDimensions(Float f)
			{
				_width = f;
				_height = f;
				_depth = f;

				return *this;
			}

			Cube & setWidth(Float width)
			{
				_width = width;

				return *this;
			}

			Cube & setHeight(Float height)
			{
				_height = height;

				return *this;
			}

			Cube & setDepth(Float depth)
			{
				_depth = depth;

				return *this;
			}

		protected:
			void buildPosition(glm::vec3 * pvertices, UInt32 count) override;
			void buildNormals(glm::vec3 * pvertices, UInt32 count) override;
			void buildTexCoords(glm::vec2 * pvertices, UInt32 count) override;
			void buildIndices(UInt32 * pindices, UInt32 count) override;


		private:
			Float _width = 1.0f;
			Float _height = 1.0f;
			Float _depth = 1.0f;
		};
	}
}