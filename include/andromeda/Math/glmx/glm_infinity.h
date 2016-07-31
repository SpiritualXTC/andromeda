#ifndef _ANDROMEDA_MATH_GLMX_GLM_INFINITY_H_
#define _ANDROMEDA_MATH_GLMX_GLM_INFINITY_H_

#include "../../stddef.h"

#include <cfloat>

namespace andromeda
{
	namespace glmx
	{

		template<typename T>
		const inline T pos_infinity()
		{
			return (T)0;
		}

		template<typename T>
		const inline T neg_infinity()
		{
			return (T)0;
		}


		template<>
		const inline Int32 pos_infinity<Int32>()
		{
			return INT32_MAX;
		}
		template<>
		const inline Int32 neg_infinity<Int32>()
		{
			return INT32_MIN;
		}



		template<>
		const inline Float pos_infinity<Float>()
		{
			return FLT_MAX;
		}
		template<>
		const inline Float neg_infinity<Float>()
		{
			return -FLT_MAX;
		}


		template<>
		const inline Double pos_infinity<Double>()
		{
			return DBL_MAX;
		}
		template<>
		const inline Double neg_infinity<Double>()
		{
			return -DBL_MAX;
		}






	}
}



#endif