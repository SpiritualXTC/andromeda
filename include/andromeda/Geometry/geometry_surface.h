#ifndef _ANDROMEDA_GRAPHICS_GEOMETRY_SURFACE_H_
#define _ANDROMEDA_GRAPHICS_GEOMETRY_SURFACE_H_

#include <functional>
#include <glm/glm.hpp>


#include "geometry_builder.h"

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/geometry/geometry_desc.h>



namespace andromeda
{
	/*
		CreateSurface():

		Creates a surface using a templated generator, with custom data
	*/
	template <typename T>
	std::shared_ptr<Geometry> CreateSurface(Float minX, Float minY, Float maxX, Float maxY, Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const T *)> generator, const T * data);
	

	/*
		CreateSurface():

		Creates a surface using a templated generator, with custom data, using the default range [-1, 1]
	*/
	template <typename T>
	std::shared_ptr<Geometry> CreateSurface(Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const T *)> generator, const T * data)
	{
		return CreateSurface<T>(-1.0f, -1.0f, 1.0f, 1.0f, divX, divY, genMask, generator, data);
	}



	

	/*
		CreateSurface():

		Creates a surface using an untyped generator, with custom data.
	*/
	std::shared_ptr<Geometry> CreateSurface(Float minX, Float minY, Float maxX, Float maxY, Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const void *)> generator, const void * data)
	{
		return CreateSurface<void>(minX, minY, maxX, maxY, divX, divY, genMask, generator, data);
	}

	/*
		CreateSurface():

		Creates a surface using an untyped generator, with custom data, using the default range.
	*/
	inline std::shared_ptr<Geometry> CreateSurface(Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const void*)> generator, const void * data)
	{
		return CreateSurface<void>(-1.0f, -1.0f, 1.0f, 1.0f, divX, divY, genMask, generator, data);
	}



	/*
		CreateSurface():

		Creates a surface using a custom generator type.
	*/
	std::shared_ptr<Geometry> CreateSurface(Float minX, Float minY, Float maxX, Float maxY, Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float)> generator)
	{
		if (! generator)
			return CreateSurface<void>(minX, minY, maxX, maxY, divX, divY, genMask, nullptr, nullptr);

		return CreateSurface<void>(minX, minY, maxX, maxY, divX, divY, genMask, [&](Float x, Float y, const void *){return generator(x, y); }, nullptr);
	}


	/*
		CreateSurface():

		Creates a surface using a custom generator type, using the default range.
	*/
	std::shared_ptr<Geometry> CreateSurface(Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float)> generator)
	{
		if (!generator)
			return CreateSurface<void>(-1.0f, -1.0f, 1.0f, 1.0f, divX, divY, genMask, nullptr, nullptr);

		return CreateSurface<void>(-1.0f, -1.0f, 1.0f, 1.0f, divX, divY, genMask, [&](Float x, Float y, const void *){return generator(x, y); }, nullptr);
	}


	
}

#include "geometry_surface.hpp"

#endif