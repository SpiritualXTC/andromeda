#pragma once

#include <common/glm.h>

#include <common/types.h>

namespace andromeda
{
	namespace glmx
	{
		/* tvec1 */
#if 0
		/*
			equalOR():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean equalOR(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x == rhs.x;
		}

		/*
			lessOR():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean lessOR(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x < rhs.x;
		}

		/*
			lessEqualOR():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean lessEqualOR(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x <= rhs.x;
		}


		/*
			greaterOR():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterOR(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x > rhs.x;
		}


		/*
			greaterEqualOR():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterEqualOR(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x >= rhs.x;
		}


		/*
			equalAND():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean equalAND(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x == rhs.x;
		}


		/*
			lessAND():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean lessAND(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x < rhs.x;
		}


		/*
			lessEqualAND():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean lessEqualAND(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x <= rhs.x;
		}

		/*
			greaterAND():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterAND(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x > rhs.x;
		}


		/*
			greaterEqualAND():
		*/
		template <typename T, enum glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterEqualAND(const glm::tvec1<T, P> & lhs, const glm::tvec1<T, P> & rhs)
		{
			return lhs.x >= rhs.x;
		}
#endif







		/* tvec2 */

		
		/*
			equalOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean equalOR(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x == rhs.x
				|| lhs.y == rhs.y;
		}

		/*
			lessOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessOR(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x < rhs.x
				|| lhs.y < rhs.y;
		}

		/*
			lessEqualOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessEqualOR(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x <= rhs.x
				|| lhs.y <= rhs.y;
		}


		/*
			greaterOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterOR(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x > rhs.x
				|| lhs.y > rhs.y;
		}


		/*
			greaterEqualOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterEqualOR(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x >= rhs.x
				|| lhs.y >= rhs.y;
		}


		/*
			equalAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean equalAND(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x == rhs.x
				&& lhs.y == rhs.y;
		}


		/*
			lessAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessAND(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x < rhs.x
				&& lhs.y < rhs.y;
		}


		/*
			lessEqualAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessEqualAND(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x <= rhs.x
				&& lhs.y <= rhs.y;
		}

		/*
			greaterAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterAND(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x > rhs.x
				&& lhs.y > rhs.y;
		}


		/*
			greaterEqualAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterEqualAND(const glm::tvec2<T, P> & lhs, const glm::tvec2<T, P> & rhs)
		{
			return lhs.x >= rhs.x
				&& lhs.y >= rhs.y;
		}





		/* tvec3 */

		/*
			equalOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean equalOR(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x == rhs.x
				|| lhs.y == rhs.y
				|| lhs.z == rhs.z;
		}

		/*
			lessOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessOR(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x < rhs.x
				|| lhs.y < rhs.y
				|| lhs.z < rhs.z;
		}

		/*
			lessEqualOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessEqualOR(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x <= rhs.x
				|| lhs.y <= rhs.y
				|| lhs.z <= rhs.z;
		}


		/*
			greaterOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterOR(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x > rhs.x
				|| lhs.y > rhs.y
				|| lhs.z > rhs.z;
		}


		/*
			greaterEqualOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterEqualOR(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x >= rhs.x
				|| lhs.y >= rhs.y
				|| lhs.z >= rhs.z;
		}


		/*
			equalAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean equalAND(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x == rhs.x
				&& lhs.y == rhs.y
				&& lhs.z == rhs.z;
		}


		/*
			lessAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessAND(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x < rhs.x
				&& lhs.y < rhs.y
				&& lhs.z < rhs.z;
		}


		/*
			lessEqualAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessEqualAND(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x <= rhs.x
				&& lhs.y <= rhs.y
				&& lhs.z <= rhs.z;
		}

		/*
			greaterAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterAND(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x > rhs.x
				&& lhs.y > rhs.y
				&& lhs.z > rhs.z;
		}


		/*
			greaterEqualAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterEqualAND(const glm::tvec3<T, P> & lhs, const glm::tvec3<T, P> & rhs)
		{
			return lhs.x >= rhs.x
				&& lhs.y >= rhs.y
				&& lhs.z >= rhs.z;
		}








		/* tvec4 */

		/*
			equalOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean equalOR(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x == rhs.x
				|| lhs.y == rhs.y
				|| lhs.z == rhs.z
				|| lhs.w == rhs.w;
		}

		/*
			lessOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessOR(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x < rhs.x
				|| lhs.y < rhs.y
				|| lhs.z < rhs.z
				|| lhs.w < rhs.w;
		}

		/*
			lessEqualOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessEqualOR(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x <= rhs.x
				|| lhs.y <= rhs.y
				|| lhs.z <= rhs.z
				|| lhs.w <= rhs.w;
		}


		/*
			greaterOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterOR(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x > rhs.x
				|| lhs.y > rhs.y
				|| lhs.z > rhs.z
				|| lhs.w > rhs.w;
		}


		/*
			greaterEqualOR():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterEqualOR(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x >= rhs.x
				|| lhs.y >= rhs.y
				|| lhs.z >= rhs.z
				|| lhs.w >= rhs.w;
		}


		/*
			equalAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean equalAND(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x == rhs.x
				&& lhs.y == rhs.y
				&& lhs.z == rhs.z
				&& lhs.w == rhs.w;
		}


		/*
			lessAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessAND(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x < rhs.x
				&& lhs.y < rhs.y
				&& lhs.z < rhs.z
				&& lhs.w < rhs.w;
		}


		/*
			lessEqualAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean lessEqualAND(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x <= rhs.x
				&& lhs.y <= rhs.y
				&& lhs.z <= rhs.z
				&& lhs.w <= rhs.w;
		}

		/*
			greaterAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterAND(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x > rhs.x
				&& lhs.y > rhs.y
				&& lhs.z > rhs.z
				&& lhs.w > rhs.w;
		}


		/*
			greaterEqualAND():
		*/
		template <typename T, glm::precision P = glm::precision::defaultp>
		const inline Boolean greaterEqualAND(const glm::tvec4<T, P> & lhs, const glm::tvec4<T, P> & rhs)
		{
			return lhs.x >= rhs.x
				&& lhs.y >= rhs.y
				&& lhs.z >= rhs.z
				&& lhs.w >= rhs.w;
		}
	}
}