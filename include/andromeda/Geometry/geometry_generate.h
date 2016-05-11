#ifndef _ANDROMEDA_GRAPHICS_GEOMETRY_GENERATE_H_
#define _ANDROMEDA_GRAPHICS_GEOMETRY_GENERATE_H_

#include <memory>

#include <andromeda/stddef.h>
#include <andromeda/glm.h>

namespace andromeda
{
	// Forward-Declarations
	class Geometry;


	enum GeometryGenerate
	{
		GEN_NORMALS = 0x01,
		GEN_TEXTURE = 0x02,
	};



	// Builder Functions
	
	// 3D
	std::shared_ptr<Geometry> CreateCube(Float width, Float height, Float depth, UInt32 genMask);
	std::shared_ptr<Geometry> CreateEllipse(Float width, Float height, Float depth, Int32 slices, Int32 stacks, UInt32 genMask);
	std::shared_ptr<Geometry> CreateTorus(Float radius, Float tubeRadius, Int32 segments, Int32 stacks, UInt32 genMask); // ToDo
	std::shared_ptr<Geometry> CreateIcosahedron(Float radius); // ToDo: Google & Implement

	inline std::shared_ptr<Geometry> CreateSphere(Float radius, Int32 slices, Int32 stacks, UInt32 genMask)
	{
		return CreateEllipse(radius * 2.0f, radius * 2.0f, radius * 2.0f, slices, stacks, genMask);
	}



	// 2D
	std::shared_ptr<Geometry> CreatePlane(Float width, Float height, UInt32 genMask); // Needs updating
	std::shared_ptr<Geometry> CreatePolygon(Float radius, Int32 sides, glm::vec3 & normal, UInt32 genMask); // ToDo


}

#endif