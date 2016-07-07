#include <andromeda/Geometry/geometry_ellipse.h>

#include <glm/ext.hpp>

using namespace andromeda;
using namespace andromeda::geometry;

/*

*/
Ellipse::Ellipse()
{

}


/*

*/
Ellipse::Ellipse(Float radius)
	: _rX(radius)
	, _rY(radius)
	, _rZ(radius)
{

}

/*

*/
void Ellipse::buildPosition(glm::vec3 * pvertices, UInt32 count)
{
	Float pi = glm::pi<Float>();

	for (UInt32 i = 0; i <= _slices; ++i)
	{
		// Range = [0, 360]
		Float slice_angle = (Float)i / _slices * pi * 2.0f;

		Float slice_cos = glm::cos(slice_angle);
		Float slice_sin = glm::sin(slice_angle);

		// Stacks
		for (UInt32 j = 0; j <= _stacks; ++j)
		{
			// Range = -90, 90
			Float stack_angle = (Float)j / _stacks * pi - pi * 0.5f;

			Float stack_cos = glm::cos(-stack_angle);
			Float stack_sin = glm::sin(-stack_angle);

			Float x = _rX * stack_cos * slice_cos;
			Float y = _rY * stack_sin;
			Float z = _rZ * stack_cos * slice_sin;

			*pvertices++ = glm::vec3(x, y, z);
		}
	}
}

/*

*/
void Ellipse::buildNormals(glm::vec3 * pvertices, UInt32 count)
{
	/*
		TODO:
		This may or may not be incorrect.
		Requires testing / display

		It Probably isn't :P
	*/
	Float pi = glm::pi<Float>();

	for (UInt32 i = 0; i <= _slices; ++i)
	{
		// Range = [0, 360]
		Float slice_angle = (Float)i / _slices * pi * 2.0f;

		Float slice_cos = glm::cos(slice_angle);
		Float slice_sin = glm::sin(slice_angle);

		// Stacks
		for (UInt32 j = 0; j <= _stacks; ++j)
		{
			// Range = -90, 90
			Float stack_angle = (Float)j / _stacks * pi - pi * 0.5f;

			Float stack_cos = glm::cos(-stack_angle);
			Float stack_sin = glm::sin(-stack_angle);

			Float x = (1.0f / _rX) * stack_cos * slice_cos;
			Float y = (1.0f / _rY) * stack_sin;
			Float z = (1.0f / _rZ) * stack_cos * slice_sin;

			*pvertices++ = glm::normalize(glm::vec3(x, y, z));
		}
	}
}


/*

*/
void Ellipse::buildTexCoords(glm::vec2 * pvertices, UInt32 count)
{
	Float uCapOffset = 0.5f / _slices;

	for (UInt32 i = 0; i <= _slices; ++i)
	{
		Float tu = (Float)i / _slices;

	
		// Top Cap
		*pvertices++ = glm::vec2(tu + uCapOffset, 0.0f);


		// Stacks
		for (UInt32 j = 1; j <= _stacks - 1; ++j)
		{
			Float tv = (Float)j / _stacks;

			*pvertices++ = glm::vec2(tu, 0.0f);
		}

		// Bottom Cap
		*pvertices++ = glm::vec2(tu + uCapOffset, 1.0f);
	}
}

/*

*/
void Ellipse::buildIndices(UInt32 * pindices, UInt32 count)
{
	
	Int32 stack_mul = _stacks + 1;

	for (UInt32 i = 0; i < _slices; ++i)
	{
		UInt32 stack = 0;

		// Top Cap
		UInt32 topA = (stack + 1) + (i + 0) * stack_mul;
		UInt32 topB = (stack + 0) + (i + 0) * stack_mul;
		UInt32 topC = (stack + 1) + (i + 1) * stack_mul;

		*pindices++ = topA;
		*pindices++ = topB;
		*pindices++ = topC;

		stack++;
		
		// Elliptical Centre
		for (UInt32 j = 0; j < _stacks - 2; ++j, ++stack)
		{
			UInt32 iA = (stack + 0) + (i + 0) * stack_mul;
			UInt32 iB = (stack + 0) + (i + 1) * stack_mul;
			UInt32 iC = (stack + 1) + (i + 0) * stack_mul;
			UInt32 iD = (stack + 1) + (i + 1) * stack_mul;

			*pindices++ = iA;
			*pindices++ = iB;
			*pindices++ = iC;

			*pindices++ = iC;
			*pindices++ = iB;
			*pindices++ = iD;
		}

		// Bottom Cap
		UInt32 bottomA = (stack + 0) + (i + 0) * stack_mul;
		UInt32 bottomB = (stack + 0) + (i + 1) * stack_mul;
		UInt32 bottomC = (stack + 1) + (i + 0) * stack_mul;

		*pindices++ = bottomA;
		*pindices++ = bottomB;
		*pindices++ = bottomC;
	}
}