#pragma once

#include <list>
#include <vector>
#include <memory>

#include <andromeda/stddef.h>
#include <andromeda/glm.h>





#include <Windows.h>
#include <gl/GLU.h>

namespace andromeda
{
	namespace geometry
	{
		class PrimitiveBuilder;

		/*
			Tesselation

			TODO: Determine why its crashing when using the 'this' as the user data to the tesselator, but not when using PrimitiveBuilder
			TODO: Setup the Cache on the Tesselator, rather than the PrimitiveBuilder
		*/
		class Tesselation
		{
		public:
			Tesselation(PrimitiveBuilder & pbuilder);
			virtual ~Tesselation();


			void beginPolygon();
			void endPolygon();


			void beginContour();
			void endContour();


			void addContour(glm::dvec3 * p, UInt32 count);

		//	inline PrimitiveBuilder & getBuilder() { return _primBuilder; }

		//	glm::dvec3 & cache(const glm::dvec3 & v);

		private:
			GLUtesselator * _tess = nullptr;

			PrimitiveBuilder & _primBuilder;


		//	std::list<glm::dvec3> _cache;
		};
	}
}