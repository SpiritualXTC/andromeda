#pragma once

#include "geometry_generate.h"

namespace andromeda
{
	namespace geometry
	{
		class Cylinder : virtual public GeometryGenerate
		{
		public:
			Cylinder();
			Cylinder(Float radius);
			Cylinder(Float radius, Float height);


			UInt32 getVertexCount() const override;
			UInt32 getFaceCount() const override;


			// Set Radius
			Cylinder & setRadius(Float radius)
			{
				_radiusLower = radius;
				_radiusUpper = radius;

				return *this;
			}

			// Set Upper Radius
			Cylinder & setUpperRadius(Float radius)
			{
				_radiusUpper = radius;

				return *this;
			}

			// Set Lower Radius
			Cylinder & setLowerRadius(Float radius)
			{
				_radiusLower = radius;

				return *this;
			}


			// Set Height
			Cylinder & setHeight(Float height)
			{
				_height = height;

				return *this;
			}

			// Set Slice Count
			Cylinder & setSlices(UInt32 slices)
			{
				_slices = slices;

				return *this;
			}



		protected:
			void buildPosition(glm::vec3 * pvertices, UInt32 count) override;
			void buildNormals(glm::vec3 * pvertices, UInt32 count) override;
			void buildTexCoords(glm::vec2 * pvertices, UInt32 count) override;
			void buildIndices(UInt32 * pindices, UInt32 count) override;

		private:
			Float _radiusUpper = 0.5f;
			Float _radiusLower = 0.5f;
			Float _height = 1.0f;

			UInt32 _slices = 16;

		};

	}
}