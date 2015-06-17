#ifndef _ANDROMEDA_MATH_REGION_H_
#define _ANDROMEDA_MATH_REGION_H_

#include "glmx/glm_extension.h"
#include "glmx/glm_infinity.h"

#include "../Utilities/log.h"

namespace andromeda
{

	/*
		Experimental super conversion
		Not in use :)
	*/
	template <typename T, enum glm::precision P = glm::precision::defaultp, template <typename, glm::precision> class V, typename _T, enum glm::precision _P = glm::precision::defaultp, template <typename, glm::precision> class _V >
	V<T, P> convert(const V<_T, _P> & v, const T def)
	{
		return V(v);
	}

	


	/*
		Conversion Support Classes
	*/

	/* Base */
	template <typename T, enum glm::precision P = glm::precision::defaultp, template <typename, glm::precision> class V >
	struct _Convert
	{


	};

	/* 2D */
	template < typename T, enum glm::precision P>
	struct _Convert<T, P, glm::detail::tvec2>
	{
		typedef glm::detail::tvec2<T, P> TYPE;

		// Catch 2D / 3D / 4D
		template <typename _T, enum glm::precision _P = glm::precision::defaultp, template <typename, glm::precision> class _V >
		static inline TYPE convert(const _V<_T, _P> & v, const T def)
		{
			return TYPE(v);
		}

		// 2D Doesn't need any conversions downwards. (1D regions aren't supported yet)
		// The basic conversion can be handled by GLM. it just loses the extra elements.
	};

	/* 3D */
	template < typename T, enum glm::precision P>
	struct _Convert<T, P, glm::detail::tvec3>
	{
		typedef glm::detail::tvec3<T, P> TYPE;

		// Catch 3D / 4D
		template <typename _T, enum glm::precision _P = glm::precision::defaultp, template <typename, glm::precision> class _V >
		static inline TYPE convert(const _V<_T, _P> & v, const T def)
		{
			return TYPE(v);
		}

		// Convert to 2D to 3D
		template <typename _T, enum glm::precision _P = glm::precision::defaultp>
		static inline TYPE convert(const glm::detail::tvec2<_T, _P> & v, const T def)
		{
			return TYPE(v, def);
		}
	};

	/* 4D */
	template < typename T, enum glm::precision P>
	struct _Convert<T, P, glm::detail::tvec4>
	{
		typedef glm::detail::tvec4<T, P> TYPE;

		// Catch 4D
		template <typename _T, enum glm::precision _P = glm::precision::defaultp, template <typename, glm::precision> class _V >
		static inline TYPE convert(const _V<_T, _P> & v, const T def)
		{
			return TYPE(v);
		}

		// Convert to 2D to 4D
		template <typename _T, enum glm::precision _P = glm::precision::defaultp>
		static inline TYPE convert(const glm::detail::tvec2<_T, _P> & v, const T def)
		{
			return TYPE(v, def, def);
		}

		// Convert to 3D to 4D
		template <typename _T, enum glm::precision _P = glm::precision::defaultp>
		static inline TYPE convert(const glm::detail::tvec3<_T, _P> & v, const T def)
		{
			return TYPE(v, def);
		}
	};









	/*
		Region!
	*/
	template <typename T, enum glm::precision P = glm::precision::defaultp, template <typename, glm::precision> class V >
	struct Region
	{
		typedef V<T, P> TYPE;
		typedef Region<T, P, V> REGION;

		/*

		*/
		Region()
		{

		}


		/*

		*/
		Region(const TYPE & min, const TYPE & max)
		{
			minimum = min;
			maximum = max;
		}

		/*
			Super Awesome, Conversion Constructor!

			So... it allows dropping a dimension, but not defaulting a dimension!
		*/
		template <typename _T, enum glm::precision _P = glm::precision::defaultp, template <typename, glm::precision> class _V >
		Region(const Region<_T, _P, _V> & region) //: minimum(convert<T, P, V>(region.minimum, -55)), maximum(convert<T, P, V>(region.maximum, 44))
		{
			minimum = _Convert<T, P, V>::convert(region.minimum, glmx::neg_infinity<T>());
			maximum = _Convert<T, P, V>::convert(region.maximum, glmx::pos_infinity<T>());
		}


		//template <typename T, enum glm::precision P = glm::precision::defaultp, template <typename, glm::precision> class V >



		/*
			makeProper():

			I want a better name.
			Fixes the min/max value so min is min and max is max!
		*/
		const void makeProper()
		{
			TYPE min = glm::min(minimum, maximum);
			TYPE max = glm::max(minimum, maximum);

			minimum = min;
			maximum = max;
		}


		/*
			size():

			Absolute Size of the region
		*/
		const TYPE size() const
		{
			return glm::abs(maximum - minimum);
		}


		/*
			center():

			Center of the region
		*/
		const TYPE center() const
		{
			return (maximum + minimum) / 2;
		}


		/*
			isNegative():

			Is the region Negative?
			If any elements maximum is less than the minimum, then the region is negative
		*/
		const Boolean isNegative() const
		{
			return glmx::lessOR(maximum, minimum);
		}


		/*
			isEmpty():

			Is the region Empty?
			One of the dimensions in the min/max coordinates are equal
		*/
		const Boolean isEmpty() const
		{
			return glmx::equalOR(minimum, maximum);
		}


		/*
			contains():

			Does the region contain the point ?
		*/
		const Boolean contains(const TYPE & point) const
		{
			return glmx::lessEqualAND<T, P>(minimum, point) && glmx::greaterEqualAND<T, P>(maximum, point);
		}


		/*
			overlap():

			Does the region overlap the current region?
		*/
		const Boolean overlap(const REGION & region) const
		{
			return glmx::lessAND<T, P>(minimum, region.maximum) && glmx::greaterAND<T, P>(maximum, region.minimum);
		}


		/*
			intesect():

			Intersection region. May return a "negative region" if no overlap.
		*/
		const Boolean intersect(const REGION & region, REGION & result) const
		{
			result.minimum = glm::max(minimum, region.minimum);
			result.maximum = glm::min(maximum, region.maximum);

			return overlap(region);
		}


		TYPE maximum;
		TYPE minimum;
	};





	/* 1D Typedef :: the glm::min/max functions do not like 1D vectors. Go Figure. */
	//typedef Region<Float, glm::highp, glm::detail::tvec1> Region1f;
	//typedef Region<Double, glm::highp, glm::detail::tvec1> Region1d;
	//typedef Region<Int32, glm::highp, glm::detail::tvec1> Region1i;

	/* 2D Typedef */
	typedef Region<Float, glm::highp, glm::detail::tvec2> Region2f;
	typedef Region<Double, glm::highp, glm::detail::tvec2> Region2d;
	typedef Region<Int32, glm::highp, glm::detail::tvec2> Region2i;

	/* 3D Typedef */
	typedef Region<Float, glm::highp, glm::detail::tvec3> Region3f;
	typedef Region<Double, glm::highp, glm::detail::tvec3> Region3d;
	typedef Region<Int32, glm::highp, glm::detail::tvec3> Region3i;

	/* 4D Typedef */
	typedef Region<Float, glm::highp, glm::detail::tvec4> Region4f;
	typedef Region<Double, glm::highp, glm::detail::tvec4> Region4d;
	typedef Region<Int32, glm::highp, glm::detail::tvec4> Region4i;
}


#endif