#pragma once

#include "geometry_generate.h"

namespace andromeda
{
	namespace geometry
	{
		class Ellipse : virtual public GeometryGenerate
		{
		private:
			static const Int32 SIDES = 6;



		public:
			Ellipse();
			Ellipse(Float radius);
	
			UInt32 getVertexCount() const
			{
				return (_slices + 1) * (_stacks + 1);
			}
			UInt32 getFaceCount() const
			{
				return _slices * (_stacks - 2) * 2 + _slices * 2;
			}



			Ellipse & setRadius(Float f)
			{
				_rX = f;
				_rY = f;
				_rZ = f;

				return *this;
			}

			Ellipse & seRadiusX(Float width)
			{
				_rX = width;

				return *this;
			}

			Ellipse & seRadiusY(Float height)
			{
				_rY = height;

				return *this;
			}

			Ellipse & seRadiusZ(Float depth)
			{
				_rZ = depth;

				return *this;
			}

			Ellipse & setSlices(UInt32 slices)
			{
				if (_slices < 3)
					return *this;

				_slices = slices;

				return *this;
			}

			Ellipse & setStacks(UInt32 stacks)
			{
				if (_stacks < 3)
					return *this;

				_stacks = stacks;

				return *this;
			}

		protected:
			void buildPosition(glm::vec3 * pvertices, UInt32 count) override;
			void buildNormals(glm::vec3 * pvertices, UInt32 count) override;
			void buildTexCoords(glm::vec2 * pvertices, UInt32 count) override;
			void buildIndices(UInt32 * pindices, UInt32 count) override;


		private:
			Float _rX = 1.0f;
			Float _rY = 1.0f;
			Float _rZ = 1.0f;

			UInt32 _slices = 8;
			UInt32 _stacks = 4;
		};
	}
}