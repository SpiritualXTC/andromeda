#pragma once

#include <andromeda/glm.h>

namespace andromeda
{
	template <typename T, enum glm::precision P = glm::precision::defaultp, template <typename, glm::precision> class V >
	struct Plane
	{
		typedef V<T, P> TYPE;
		typedef Plane<T, P, V> PLANE;

		/*
		
		*/
		Plane()
		{

		}

		/*

		*/
		Plane(const TYPE & n)
			: Plane(n, 0)
		{

		}

		/*
		
		*/
		Plane(const TYPE & n, T f)
			: normal(n)
			, d(f)
		{

		}

		/*
			Conversion Constructor
		*/
		template <typename _T, enum glm::precision _P = glm::precision::defaultp, template <typename, glm::precision> class _V >
		Plane(const Plane<_T, _P, _V> & plane)
		{
			normal = glmx::_Convert<T, P, V>::convert(plane.normal, glmx::neg_infinity<T>());
			d = plane.d;
		}


		/*
			
		*/
		inline T length() const
		{
			return glm::length(normal);
		}

		/*
		
		*/
		void normalize()
		{
			T len = 1.0f / length();

			normal *= len;

			d *= len;
		}

		/*
			Is a sphere on the "positive" side of the plane 
		*/
		Boolean positive(const TYPE & point, T radius) const
		{
			T dot = glm::dot(point, normal);

			return dot + d + radius > 0;

			// TODO: REMOVE FOLLING
	//		if (vecCenter.Dot(p[i].n) + p[i].d + flRadius <= 0)
	//			return false;
		}


		/*
			Sphere intesects a plane?
		*/
		Boolean intersect(const TYPE & point, T radius) const
		{
			/*
				TODO Test this function... not sure if correct or not :)
			*/
			T dot = glm::dot(point, normal);

			return abs(dot + d) < radius;
		}


		TYPE normal;
		T d;
	};





	/* 2D Typedef */
	typedef Plane<Float, glm::highp, glm::detail::tvec2> Plane2f;
	typedef Plane<Double, glm::highp, glm::detail::tvec2> Plane2d;
	typedef Plane<Int32, glm::highp, glm::detail::tvec2> Plane2i;

	/* 3D Typedef */
	typedef Plane<Float, glm::highp, glm::detail::tvec3> Plane3f;
	typedef Plane<Double, glm::highp, glm::detail::tvec3> Plane3d;
	typedef Plane<Int32, glm::highp, glm::detail::tvec3> Plane3i;

	/* 4D Typedef */
	typedef Plane<Float, glm::highp, glm::detail::tvec4> Plane4f;
	typedef Plane<Double, glm::highp, glm::detail::tvec4> Plane4d;
	typedef Plane<Int32, glm::highp, glm::detail::tvec4> Plane4i;
}