#include <andromeda/Geometry/geometry_polygon.h>

#include <andromeda/Geometry/tesselation.h>

#include <andromeda/Math/glmx/glm_infinity.h>

#include <andromeda/Utilities/log.h>



using namespace andromeda;
using namespace andromeda::geometry;


















/*

*/
geometry::Polygon::Polygon()
{

}

/*

*/
geometry::Polygon::~Polygon()
{

}





#if 0
/*

*/
geometry::Polygon & Polygon::moveTo(const glm::vec3 & p)
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
geometry::Polygon & Polygon::lineTo(const glm::vec3 & p)
{
	// Start if their is no current
	if (! getCurrent())
		moveTo(glm::vec3(0, 0, 0));

	// Add Line
	Contour * current = getCurrent();
	if (current)
		current->lineTo(glm::dvec3(p));

	return *this;
}

geometry::Polygon & Polygon::bezierTo(const glm::vec3 & control, const glm::vec3 & p)
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
#endif




/*

*/
Boolean Polygon::prebuild()
{ 
	/*
		Triangulation	
	*/

	// Close Current Contour
	Contour * current = getCurrent();
	if (current)
		current->close();



	// Run Tesselation Across all the Contours
	Tesselation tess(_primBuilder);

	tess.beginPolygon();

	for (auto & it : getContours())
	{
		tess.addContour(it.contour().data(), it.contour().size());
	}

	tess.endPolygon();

	// Build Texture Coordinates for "Normal" Primitives
	for (UInt32 i = 0; i < _primBuilder.getNumVertices() / 3; ++i)
	{
		_textureCoords.push_back(glm::vec2(0.9f, 0.9f));
		_textureCoords.push_back(glm::vec2(1.0f, 1.0f));
		_textureCoords.push_back(glm::vec2(0.9f, 0.9f));
	}
	
	// Append the "Curveh" Triangles
	for (auto & it : getContours())
	{
		std::vector<Line> & lines = it.lines();

		for (const auto & it : lines)
		{
			_primBuilder.setPrimitiveType(PrimitiveMode::TriangleStrip);

			if (!it.isLinear() && it.getNumControlPoints() == 1)
			{
				// The First Line Shouldn't be able to be a curve
				

				// Inner Beziers this is fine for.
				// Outer Beziers are currently inverted ><

				if (it.getCross() <= 0.0f)
				{
					// Inner (Concave??)
					_primBuilder.addVertex(it.getCoordinate0());
					_primBuilder.addVertex(it.getControlPoint(0));	// This could be a strip or a fan? when using multipel control points ???
					_primBuilder.addVertex(it.getCoordinate1());

					_textureCoords.push_back(glm::vec2(0.0f, 1.0f));
					_textureCoords.push_back(glm::vec2(1.0f, 1.0f));
					_textureCoords.push_back(glm::vec2(1.0f, 0.0f));

				//	_textureCoords.push_back(glm::vec2(0.0f, 0.0f));
				//	_textureCoords.push_back(glm::vec2(-0.5f, 0.0f));
				//	_textureCoords.push_back(glm::vec2(-1.0f, -1.0f));
				}
				else
				{
					// Outer (Convex)
					_primBuilder.addVertex(it.getCoordinate1());
					_primBuilder.addVertex(it.getControlPoint(0));	// This could be a strip or a fan? when using multipel control points ???
					_primBuilder.addVertex(it.getCoordinate0());

					_textureCoords.push_back(glm::vec2(0.0f, 1.0f));
					_textureCoords.push_back(glm::vec2(0.0f, 0.0f));
					_textureCoords.push_back(glm::vec2(1.0f, 0.0f));

				//	_textureCoords.push_back(glm::vec2(0.0f, 0.0f));
				//	_textureCoords.push_back(glm::vec2(0.5f, 0.0f));
				//	_textureCoords.push_back(glm::vec2(1.0f, 1.0f));
				}
			}
		}
	}

	return true; 
}


/*

*/
void Polygon::buildPosition(glm::vec3 * pvertices, UInt32 count)
{
	const std::vector<glm::vec3> vertices = _primBuilder.getVertices();

	// Copy!
	for (const auto & v : vertices)
	{
		*pvertices++ = v;
	}
}


/*

*/
void Polygon::buildNormals(glm::vec3 * pvertices, UInt32 count)
{
	// Set Normal
	for (UInt32 i = 0; i < count; ++i)
		*pvertices++ = glm::vec3(0, 0, 1);
}


/*

*/
void Polygon::buildTexCoords(glm::vec2 * pvertices, UInt32 count)
{
	assert(count == _textureCoords.size());

	// Copy Texture Coordinates Across
	for (const auto & v : _textureCoords)
	{
		*pvertices++ = v;
	}




#if 0	
	
	// This is the actual texture coordinates :: Reintroduce this Code when 
	// bezier texture coordinates are setup using their own channel
	// Do NOT remove it. lololol

	glm::vec3 vPosMin = glm::vec3(glmx::pos_infinity<Float>());
	glm::vec3 vPosMax = glm::vec3(glmx::neg_infinity<Float>());


	// Determine Vertex Bounds [Minimum]
	if (!_vertexMinimum.is_initialized())
	{
		const glm::vec3 * pposition = getPositionData();

		for (UInt32 i = 0; i < count; ++i)
		{
			const glm::vec3 & v = *pposition++;

			if (v.x < vPosMin.x)
				vPosMin.x = v.x;
			if (v.y < vPosMin.y)
				vPosMin.y = v.y;
			if (v.z < vPosMin.z)
				vPosMin.z = v.z;
		}
	}
	else
		vPosMin = _vertexMinimum.get();
	
	// Determine Vertex Bounds [Maximum]
	if (!_vertexMaximum.is_initialized())
	{
		const glm::vec3 * pposition = getPositionData();

		for (UInt32 i = 0; i < count; ++i)
		{
			const glm::vec3 & v = *pposition++;

			if (v.x > vPosMax.x)
				vPosMax.x = v.x;
			if (v.y > vPosMax.y)
				vPosMax.y = v.y;
			if (v.z > vPosMax.z)
				vPosMax.z = v.z;
		}
	}
	else
		vPosMax = _vertexMaximum.get();


	// Calculate Texture Coordinates
	glm::vec3 size = vPosMax - vPosMin;

	const glm::vec3 * pposition = getPositionData();

	for (UInt32 i = 0; i < count; ++i)
	{
		const glm::vec3 & v = *pposition++;

		Float tu = (v.x - vPosMin.x) / size.x;
		Float tv = (v.y - vPosMin.y) / size.y;

		*pvertices++ = glm::vec2(tu, tv);
	}
#endif
}


/*

*/
void Polygon::buildIndices(UInt32 * pindices, UInt32 count)
{
	const std::vector<UInt32> indices = _primBuilder.getFaces();

	// Copy
	for (const auto & it : indices)
		*pindices++ = it;
}