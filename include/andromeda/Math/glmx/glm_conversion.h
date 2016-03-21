#ifndef _ANDROMEDA_MATH_GLMX_GLM_CONVERSION_H_
#define _ANDROMEDA_MATH_GLMX_GLM_CONVERSION_H_

#include <andromeda/glm.h>

namespace andromeda
{
	namespace glmx
	{

		/*
			Conversion Support Classes

			These work!
			Still trying to make it possible for a little  it more automatic conversion.
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
			static const inline TYPE convert(const _V<_T, _P> & v, const T def)
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
			static const inline TYPE convert(const _V<_T, _P> & v, const T def)
			{
				return TYPE(v);
			}

			// Convert to 2D to 3D
			template <typename _T, enum glm::precision _P = glm::precision::defaultp>
			static const inline TYPE convert(const glm::detail::tvec2<_T, _P> & v, const T def)
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
			static const inline TYPE convert(const _V<_T, _P> & v, const T def)
			{
				return TYPE(v);
			}

			// Convert to 2D to 4D
			template <typename _T, enum glm::precision _P = glm::precision::defaultp>
			static const inline TYPE convert(const glm::detail::tvec2<_T, _P> & v, const T def)
			{
				return TYPE(v, def, def);
			}

			// Convert to 3D to 4D
			template <typename _T, enum glm::precision _P = glm::precision::defaultp>
			static const inline TYPE convert(const glm::detail::tvec3<_T, _P> & v, const T def)
			{
				return TYPE(v, def);
			}
		};









		/*
			Namespace functions relying on auto type deduction:

			These do not work correctly!
		*/


#if 0
		/* No Change! */
		template <typename T, enum glm::precision P = glm::precision::defaultp, template <typename, glm::precision> class V>
		const inline V<T, P> convert(const V<T, P> & v, const T def)
		{
			return v;
		}


		/* Converts down a dimension */
		template <typename T, enum glm::precision P = glm::precision::defaultp, template <typename, glm::precision> class V, typename _T, enum glm::precision _P = glm::precision::defaultp, template <typename, glm::precision> class _V >
		const inline V<T, P> convert(const V<_T, _P> & v, const T def)
		{
			return V(v);
		}



		/* Convert 2D to 4D */
		template <typename T, enum glm::precision P>
		const inline glm::detail::tvec4<T, P> convert(const glm::detail::tvec2<T, P> & v, const T def)
		{
			return glm::detail::tvec4<T, P>(v, def, def);
		}

		/* Convert 3D to 4D */
		template <typename T, enum glm::precision P>
		const inline glm::detail::tvec4<T, P> convert(const glm::detail::tvec3<T, P> & v, const T def)
		{
			return glm::detail::tvec4<T, P>(v, def);
		}

		/* Convert 2D to 3D */
		template <typename T, enum glm::precision P>
		const inline glm::detail::tvec3<T, P> convert(const glm::detail::tvec2<T, P> & v, const T def)
		{
			return glm::detail::tvec3<T, P>(v, def);
		}
#endif

	}
}

#endif