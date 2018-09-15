#pragma once

#include <vector>

#include <common/types.h>
#include <common/glm.h>

namespace andromeda
{
	namespace geometry
	{



		/*
			Segment of a Contour
		*/
		class Line
		{
		public:
			enum LineType
			{
				Linear,
				ConvexCurve,
				ConcaveCurve,
			};

		public:
			Line(const glm::dvec3 & v0, const glm::dvec3 & v1);

			void addControlPoint(const glm::dvec3 & control);

			// Is the Line Linear
			inline Boolean isLinear() const { return _control.size() == 0; }

			// Get End Point
			const glm::dvec3 & getCoordinate0() const { return _coordinate0; }
			const glm::dvec3 & getCoordinate1() const { return _coordinate1; }

			// Get Control Point Count
			const Int32 getNumControlPoints() const { return _control.size(); }

			// Get Control Point
			const glm::dvec3 & getControlPoint(Int32 index) const { return _control[index]; }

			const Double getCross() const;



			/*
				Gets the Line Type
			*/
			const LineType getLineType() const;

		private:

			glm::dvec3 _coordinate0;
			glm::dvec3 _coordinate1;

			std::vector<glm::dvec3> _control;
		};



		/*
			A Shape Segment
		*/
		class Contour
		{
		public:
			Contour(const glm::vec3 & p);

			Contour & lineTo(const glm::dvec3 & p);
			Contour & bezierTo(const glm::dvec3 & control, const glm::dvec3 & p);

			Contour & close();


			// Gets the Contour Points
			std::vector<glm::dvec3> & contour() { return _contour; }

			// Gets the Line information
			std::vector<Line> & lines() { return _lines; }


		private:

			Boolean subdivide(const glm::dvec3 & v0, const glm::dvec3 & v1, const glm::dvec3 & c);

			Line & insertLine(const glm::dvec3 & p);

			std::vector<glm::dvec3> _contour;

			std::vector<Line> _lines;


			glm::dvec3 _lastLineCoordinate;
		};


		/*
			Collection of Contours
		*/
		class Shape
		{
		public:
			Shape();
			virtual ~Shape();

			Shape & moveTo(const glm::vec3 & p);
			Shape & lineTo(const glm::vec3 & p);
			Shape & bezierTo(const glm::vec3 & control, const glm::vec3 & p);


			std::vector<Contour> & getContours() { return _contours; }

		protected:
			Contour * getCurrent() { return _contours.size() == 0 ? nullptr : &_contours.back(); }



		private:
			std::vector<Contour> _contours;
		};
	}
}