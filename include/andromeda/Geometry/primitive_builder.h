#pragma once

#include <list>
#include <vector>

#include <andromeda/stddef.h>
#include <andromeda/glm.h>

#include <andromeda/graphics_types.h>

namespace andromeda
{
	namespace geometry
	{
		/*

		*/
		class PrimitiveBuilder
		{
		private:
			static const UInt32 VERTEX_UNSET = 0xFFFFFFFF;

		public:

			// Sets the Primitive Type
			void setPrimitiveType(PrimitiveMode primType);

			void addVertex(const glm::dvec3 & v);


			inline UInt32 getNumVertices() const { return _vertices.size(); }
			inline UInt32 getNumFaces() const { return _faces.size() / 3; }


			const inline std::vector<glm::vec3> & getVertices() const { return _vertices; }
			const inline std::vector<UInt32> & getFaces() const { return _faces; }



			/*
				Caches a Vertex in its own memory

				This is purely for the tesselator
			*/
			glm::dvec3 & cache(const glm::dvec3 & v);

		private:


			void addIndexToTriangleList(UInt32 index);
			void addIndexToTriangleFan(UInt32 index);
			void addIndexToTriangleStrip(UInt32 index);

			PrimitiveMode _primType = PrimitiveMode::Triangles;

			UInt32 _firstVertex = VERTEX_UNSET;
			UInt32 _secondVertex = VERTEX_UNSET;

			std::vector<glm::vec3> _vertices;
			std::vector<UInt32> _faces;


			// The List maintains the SAME memory location for a dvec3 throughout the lifecycle of the PrimitiveBuilder
			// this makes it suitable to use for the GLU Tesselation :)
			std::list<glm::dvec3> _cache;
		};
	}
}