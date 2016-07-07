#include <andromeda/Geometry/geometry_surface.h>

#include <cassert>

#include <andromeda/Geometry/geometry_surface_function.h>
#include <andromeda/Math/math.h>


using namespace andromeda;
using namespace andromeda::geometry;


/*

*/
void Surface::buildPosition(glm::vec3 * pvertices, UInt32 count)
{
	SurfaceFunctionGrid sfg;

	// Set Default Surface Function Generator
	if (!_positionFunction)
		_positionFunction = &sfg;

	assert(_positionFunction);



	Float range0 = _maximum0 - _minimum0;
	Float range1 = _maximum1 - _minimum1;

	// Position
	Float stepX = range0 / _divisions0;
	Float stepY = range1 / _divisions1;

	for (UInt32 j = 0; j <= _divisions1; ++j)
	{
		for (UInt32 i = 0; i <= _divisions0; ++i)
		{
			Float n0 = ((Float)i / _divisions0) * range0 + _minimum0;
			Float n1 = ((Float)j / _divisions1) * range1 + _minimum1;

			// Set Position
			*pvertices++ = _positionFunction->calc(n0, n1);
		}
	}
}



/*

*/
void Surface::buildNormals(glm::vec3 * pvertices, UInt32 count)
{
	if (!_normalFunction)
		buildNormalSmoothing(pvertices, count);
	else
	{

	}
}


/*

*/
void Surface::buildNormalSmoothing(glm::vec3 * pvertices, UInt32 count)
{

	// Allocate & Initialise Weight Factors
	UInt32 * weight = new UInt32[count];
	for (UInt32 i = 0; i < count; ++i)
	{
		weight[i] = 0;
		pvertices[i] = glm::vec3(0, 0, 0);
	}


	// Get Data
	UInt32 indexCount = getFaceCount() * 3;

	const glm::vec3 * pposition = getPositionData();
	const UInt32 * pindices = getIndexData();


	// Calculate Weight & Totals
	glm::vec3 normal;
	for (UInt32 i = 0; i < indexCount; i += 3)
	{
		UInt32 a = pindices[i + 0];
		UInt32 b = pindices[i + 1];
		UInt32 c = pindices[i + 2];

		// Calc Face Normal
		calcNormal(normal, pposition[a], pposition[b], pposition[c]);

		// Add Weight
		pvertices[a] += normal;
		pvertices[b] += normal;
		pvertices[c] += normal;

		// Add Count
		weight[a]++;
		weight[b]++;
		weight[c]++;
	}


	// Smoothing
	for (UInt32 i = 0; i < count; ++i)
	{
		if (weight[i] != 0)
		{
			// Average Weight
			pvertices[i] = pvertices[i] / (Float)weight[i];

			// Normalise
			pvertices[i] = pvertices[i] / glm::length(pvertices[i]);
		}
	}

	// Delete Weight
	if (weight)
		delete[] weight;
}


/*

*/
void Surface::buildTexCoords(glm::vec2 * pvertices, UInt32 count)
{
	for (UInt32 j = 0; j <= _divisions1; ++j)
	{
		for (UInt32 i = 0; i <= _divisions0; ++i)
		{
			*pvertices++ = glm::vec2((Float)i / _divisions0, (Float)j / _divisions1);
		}
	}
}


/*

*/
void Surface::buildIndices(UInt32 * pindices, UInt32 count)
{
	for (UInt32 j = 0; j < _divisions1; j++)
	{
		for (UInt32 i = 0; i < _divisions0; i++)
		{
			UInt32 iA = (UInt32)((i + 1) + (j + 1) * (_divisions0 + 1));
			UInt32 iB = (UInt32)((i + 1) + (j + 0) * (_divisions0 + 1));
			UInt32 iC = (UInt32)((i + 0) + (j + 1) * (_divisions0 + 1));
			UInt32 iD = (UInt32)((i + 0) + (j + 0) * (_divisions0 + 1));

			*pindices++ = iA;
			*pindices++ = iB;
			*pindices++ = iC;

			*pindices++ = iC;
			*pindices++ = iB;
			*pindices++ = iD;
		}
	}
}




