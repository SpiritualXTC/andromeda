#include <andromeda/Geometry/shape.h>



using namespace andromeda;
using namespace andromeda::geometry;

/*

*/
Line::Line(const glm::dvec3 & v0, const glm::dvec3 & v1)
	: _coordinate0(v0)
	, _coordinate1(v1)
{

}

/*

*/
void Line::addControlPoint(const glm::dvec3 & control)
{
	_control.push_back(control);
}


/*

*/
const Double Line::getCross() const
{
	if (_control.size() == 0)
		return true;

	glm::dvec3 s0 = _coordinate1 - _coordinate0;
	glm::dvec3 s1 = _control.front() - _coordinate0;

	return s0.x * s1.y - s0.y * s1.x;
}


/*

*/
const Line::LineType Line::getLineType() const
{
	if (_control.size() == 0)
		return Linear;

	glm::dvec3 s0 = _coordinate1 - _coordinate0;
	glm::dvec3 s1 = _control.front() - _coordinate0;

	Double cross = s0.x * s1.y - s0.y * s1.x;

	return (cross >= 0.0f) ? ConvexCurve : ConcaveCurve;
}











/*

*/
Contour::Contour(const glm::vec3 & p)
{
	glm::dvec3 v(p);

	// Add the First Coordinate to the Contour
	_contour.push_back(v);

	// Set Last Coordinate Added
	_lastLineCoordinate = p;
}


/*

*/
Line & Contour::insertLine(const glm::dvec3 & p)
{
	// Create the new Line
	Line line(_lastLineCoordinate, p);

	// Insert Line
	_lines.push_back(line);

	// Set Last Coordinate Added
	_lastLineCoordinate = p;

	return _lines.back();
}


/*

*/
Contour & Contour::lineTo(const glm::dvec3 & p)
{
	glm::dvec3 v(p);

	// Insert the Line
	Line & line = insertLine(v);

	// Add the End Point to the Contour
	_contour.push_back(v);

	return *this;
}




/*

*/
Boolean Contour::subdivide(const glm::dvec3 & v0, const glm::dvec3 & v1, const glm::dvec3 & c)
{
	// Determine whether a subdivision will be necessary

	// The goal of subdividing the bezier curve is to prevent the bezier control point on the contour, intersecting with the opposite contour
	// Make the control point as close as possible to the line -- by adding mode curves, will minimum the how much the polygon will "dig" into the main contour


	// Length between the two end points.
	aDouble len = glm::length(v1 - v0);

	glm::dvec3 s = (v0 + v1) * 0.5;
	aDouble dist = glm::length(c - s);

	// The factor value will need some experimentation
	aDouble factor = 0.25f;


	if (dist < len * factor)
		return false;



#if 0
	log_debugp("Bezier Subdivison : v0 = (%1%, %2%) : c = (%3%, %4%) : v1 = (%5%, %6%)", v0.x, v0.y, c.x, c.y, v1.x, v1.y);
	log_tree();

	log_infop("Line Length = %1%", len);
	log_infop("Control Distance = %1%", dist);
#endif




	aDouble weight = 0.5f;	// Division Weight

	aDouble w0 = weight;
	aDouble w1 = 1.0f - weight;



	//	glm::dvec3 v00 = v0;	// Line Start
	glm::dvec3 v0c = w1 * v0 + w0 * c;

	glm::dvec3 vj = w1 * w1 * v0 + 2.0 * w1 * w0 * c + w0 * w0 * v1;		// Line Join

	glm::dvec3 v1c = w1 * c + w0 * v1;
	//	glm::dvec3 v11 = v1;	// Line End


#if 0
	log_debugp("Bezier Division 1");
	log_treepush();
	log_infop("v0 = (%1%, %2%)", _lastLineCoordinate.x, _lastLineCoordinate.y);
	log_infop("c = (%1%, %2%)", v0c.x, v0c.y);
	log_infop("v1 = (%1%, %2%)", vj.x, vj.y);
	log_treepop();

	log_debugp("Bezier Division 2");
	log_treepush();
	log_infop("v0 = (%1%, %2%)", vj.x, vj.y);
	log_infop("c = (%1%, %2%)", v1c.x, v1c.y);
	log_infop("v1 = (%1%, %2%)", v1.x, v1.y);
	log_treepop();
#endif

	// Process Subdivision
	bezierTo(v0c, vj);
	bezierTo(v1c, v1);

	return true;
}



/*

*/
Contour & Contour::bezierTo(const glm::dvec3 & control, const glm::dvec3 & p)
{
	glm::dvec3 v(p);
	glm::dvec3 c(control);




	// Does the Curve need to be subdivided??
	if (subdivide(_lastLineCoordinate, v, c))
	{
		// Do Not Continue Processing this Bezier Curve
		return *this;
	}

	// Insert the Line
	Line & line = insertLine(v);
	line.addControlPoint(c);

	// Add the Control point to the Contour
	if (line.getCross() <= 0.0f)
		_contour.push_back(c);

	// Add the Line End to the Contour
	_contour.push_back(v);


	return *this;
}


/*

*/
Contour & Contour::close()
{
	// Prevent the Contour from being Closed :: Merging vertices in the tesselator doesn't work yet :P

	glm::dvec3 & d1 = _contour.front();
	glm::dvec3 & d2 = _contour.back();

	// The Last Coordiante
	if (d1 == d2)
	{
		//	log_debugp("Contour :: Remove Last");
		_contour.pop_back();
	}

	return *this;
}






/*

*/
Shape::Shape()
{

}

/*

*/
Shape::~Shape()
{

}



/*

*/
Shape & Shape::moveTo(const glm::vec3 & p)
{
	Contour c(p);

	// Close Current Contour
	Contour * current = getCurrent();
	if (current)
		current->close();

	// Add new Contour
	_contours.push_back(std::move(c));

	return *this;
}

/*

*/
Shape & Shape::lineTo(const glm::vec3 & p)
{
	// Start if their is no current
	if (!getCurrent())
		moveTo(glm::vec3(0, 0, 0));

	// Add Line
	Contour * current = getCurrent();
	if (current)
		current->lineTo(glm::dvec3(p));

	return *this;
}


/*

*/
Shape & Shape::bezierTo(const glm::vec3 & control, const glm::vec3 & p)
{

	// Start if their is no current
	if (!getCurrent())
		moveTo(glm::vec3(0, 0, 0));

	// Add Line
	Contour * current = getCurrent();
	if (current)
		current->bezierTo(glm::dvec3(control), glm::dvec3(p));

	return *this;
}