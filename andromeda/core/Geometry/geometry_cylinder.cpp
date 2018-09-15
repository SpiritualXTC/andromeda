#include "geometry_cylinder.h"

#include <Common/log.h>

using namespace andromeda;
using namespace andromeda::geometry;

/*
	TODO:
	Write this class :)
	Support Cylinder Thickness. 
	Thickness of zero should be allowed for one or both the top and bottom.
*/


/*

*/
Cylinder::Cylinder()
{

}


/*

*/
Cylinder::Cylinder(Float radius)
	: _radiusUpper(radius)
	, _radiusLower(radius)
{

}


/*

*/
Cylinder::Cylinder(Float radius, Float height)
	: _radiusUpper(radius)
	, _radiusLower(radius)
	, _height(height)
{

}


/*

*/
UInt32 Cylinder::getVertexCount() const
{
	UInt32 verts = 0;

	// If no thickness
	// Cylinder (Top + Bottom, include wrapping)
	verts += (_slices + 1) * 2;

	// Caps (Top + Bottom, vertex side swapping)
	verts += (_slices + 1) * 2;


	// If thickness
	/*
	// Outer Cylinder (with wrapping)
	verts += (_slices + 1) * 2;
	
	// Inner Cylinder (with wrapping)
	verts += (_slices + 1) * 2;

	// Top
	verts += _slices * 2;
	
	verts += _slices * 2;
	*/

	return verts;
}


/*

*/
UInt32 Cylinder::getFaceCount() const
{
	UInt32 faces = 0;
	
	// Cylinder
	faces += _slices * 2;

	// Caps (Top + Bottom)
	faces += _slices * 2;


	// If thickness
	/*
	// Outer
	faces += _slices * 2;

	// Inner
	faces += _slices * 2;
	
	// Top
	faces += _slices * 2;
	
	// Bottom
	faces += _slices * 2;
	*/


	return faces;
}





/*

*/
void Cylinder::buildPosition(glm::vec3 * pvertices, UInt32 count)
{
	Float h = _height * 0.5f;

	// Build Outer Cylinder
	for (UInt32 i = 0; i <= _slices; ++i)
	{
		Float angle = i / (Float)_slices * glm::pi<Float>() * 2.0f;

		Float x = cosf(angle);
		Float z = sinf(angle);

		// Upper
		*pvertices++ = glm::vec3(x * _radiusUpper, h, z * _radiusUpper);

		// Lower
		*pvertices++ = glm::vec3(x * _radiusLower,-h, z * _radiusLower);
	}

	// Build Caps [Thickness <= 0.0]
	// Top

	*pvertices++ = glm::vec3(0.0f, h, 0.0f);
	for (UInt32 i = 0; i < _slices; ++i)
	{
		Float angle = i / (Float)_slices * glm::pi<Float>() * 2.0f;

		Float x = cosf(angle);
		Float z = sinf(angle);

		*pvertices++ = glm::vec3(x * _radiusUpper, h, z * _radiusUpper);
	}

	// Bottom
	*pvertices++ = glm::vec3(0.0f, -h, 0.0f);
	for (UInt32 i = 0; i < _slices; ++i)
	{
		Float angle = i / (Float)_slices * glm::pi<Float>() * -2.0f;

		Float x = cosf(angle);
		Float z = sinf(angle);

		*pvertices++ = glm::vec3(x * _radiusLower, -h, z * _radiusLower);
	}


	// Build Inner Cylinder [Thickness > 0.0]

	// Build Caps [Thickness > 0.0]
	

}

/*

*/
void Cylinder::buildNormals(glm::vec3 * pvertices, UInt32 count)
{
	Float h = _height * 0.5f;

	// Calculate the Cylinder 2D Normal from the Radius's
	glm::vec2 v0 = glm::vec2(_radiusUpper, h);
	glm::vec2 v1 = glm::vec2(_radiusLower, -h);

	glm::vec2 vs = v1 - v0;

	glm::vec2 n = glm::vec2(-vs.y, vs.x);


	// Outer Cylinder
	for (UInt32 i = 0; i <= _slices; ++i)
	{
		Float angle = i / (Float)_slices * glm::pi<Float>() * 2.0f;

		Float x = cosf(angle);
		Float z = sinf(angle);

		// Upper
		*pvertices++ = glm::vec3(n.x * x, n.y, n.x * z);

		// Lower
		*pvertices++ = glm::vec3(n.x * x, n.y, n.x * z);
	}


	// Caps
	for (UInt32 i = 0; i <= _slices; ++i)
	{
		*pvertices++ = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	for (UInt32 i = 0; i <= _slices; ++i)
	{
		*pvertices++ = glm::vec3(0.0f, -1.0f, 0.0f);
	}
}

/*

*/
void Cylinder::buildTexCoords(glm::vec2 * pvertices, UInt32 count)
{
	// Cylinder
	for (UInt32 i = 0; i <= _slices; ++i)
	{
		Float w = i / (Float)_slices;

		// Upper
		*pvertices++ = glm::vec2(w, 0.0f);

		// Lower
		*pvertices++ = glm::vec2(w, 1.0f);
	}

	// Caps
	*pvertices++ = glm::vec2(0.5f, 0.5f);
	for (UInt32 i = 0; i < _slices; ++i)
	{
		Float angle = i / (Float)_slices * glm::pi<Float>() * 2.0f;

		Float tu = cosf(angle);
		Float tv = sinf(angle);

		*pvertices++ = glm::vec2(tu * 0.5f + 0.5f, tv * 0.5f + 0.5f);
	}

	*pvertices++ = glm::vec2(0.5f, 0.5f);
	for (UInt32 i = 0; i < _slices; ++i)
	{
		Float angle = i / (Float)_slices * glm::pi<Float>() * 2.0f;

		Float tu = cosf(angle);
		Float tv = sinf(angle);

		*pvertices++ = glm::vec2(tu * 0.5f + 0.5f, tv * 0.5f + 0.5f);
	}
}

/*

*/
void Cylinder::buildIndices(UInt32 * pindices, UInt32 count)
{
	UInt32 * pi = pindices;

	// Cylinder
	for (UInt32 i = 0; i < _slices; ++i)
	{
		
		*pindices++ = i * 2 + 1;
		*pindices++ = i * 2;
		*pindices++ = (i + 1) * 2 + 1;

		*pindices++ = (i + 1) * 2 + 1;
		*pindices++ = i * 2;
		*pindices++ = (i + 1) * 2; 
	}



	// Top
	UInt32 start = (_slices + 1) * 2;
	UInt32 center = start;
	++start;
	for (UInt32 i = 0; i < _slices; ++i)
	{
		*pindices++ = center;
		*pindices++ = start + (i + 1) % _slices;
		*pindices++ = start + i;
	}




	// Bottom
	start += _slices;
	center = start;
	++start;
	for (UInt32 i = 0; i < _slices; ++i)
	{
		*pindices++ = center;
		*pindices++ = start + (i + 1) % _slices;;
		*pindices++ = start + i;
	}




	for (UInt32 i = 0; i < count / 3; ++i)
	{
		log_debugp("%1%, %2%, %3%", *pi++, *pi++, *pi++);
	}

}







