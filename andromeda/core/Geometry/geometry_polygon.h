#pragma once


#include <vector>

#include <boost/optional.hpp>

#include "geometry_generate.h"
#include "primitive_builder.h"

#include "shape.h"

namespace andromeda
{
	namespace geometry
	{
		/*
			Generates shapes!

			This needs to be broken up into 2 classes....

			The First one manages the Contour. [Shape]
			The Second one converts the Contour into Primitives. [Polygon]

			Polygon is the second one
		*/
		class Polygon : private Shape, virtual public GeometryGenerate
		{
		public:
			Polygon();
			virtual ~Polygon();

			UInt32 getVertexCount() const override {return _primBuilder.getNumVertices();}
			UInt32 getFaceCount() const override {return _primBuilder.getNumFaces();}


			/*
				TODO: Make these inline passthru's to Shape
			*/
		//	Polygon & moveTo(const glm::vec3 & p);
		//	Polygon & lineTo(const glm::vec3 & p);
		//	Polygon & bezierTo(const glm::vec3 & control, const glm::vec3 & p);

			inline Polygon & moveTo(const glm::vec3 & p) { Shape::moveTo(p); return *this; }
			inline Polygon & lineTo(const glm::vec3 & p) { Shape::lineTo(p); return *this; }
			inline Polygon & bezierTo(const glm::vec3 & control, const glm::vec3 & p) 
			{ 
				Shape::bezierTo(control, p); 
				return *this; 
			}
			inline Polygon & bezierTo(const glm::vec3 & c0, const glm::vec3 & c1, const glm::vec3 & p)
			{
				return *this;
			}


			inline Polygon & setVertexBoundsMinimum(const glm::vec3 & v) { _vertexMinimum = v; }
			inline Polygon & setVertexBoundsMaximum(const glm::vec3 & v) { _vertexMaximum = v; }

		protected:
		//	Contour * getCurrent() { return _contours.size() == 0 ? nullptr : &_contours.back(); }

			Boolean prebuild();

			void buildPosition(glm::vec3 * pvertices, UInt32 count);
			void buildNormals(glm::vec3 * pvertices, UInt32 count);
			void buildTexCoords(glm::vec2 * pvertices, UInt32 count);
			void buildIndices(UInt32 * pindices, UInt32 count);


		private:
		//	std::vector<Contour> _contours;


			PrimitiveBuilder _primBuilder;


			// Texture Coordinate Bounds Scan
			boost::optional<glm::vec3> _vertexMinimum;
			boost::optional<glm::vec3> _vertexMaximum;


			std::vector<glm::vec2> _textureCoords;
		};


	}
}