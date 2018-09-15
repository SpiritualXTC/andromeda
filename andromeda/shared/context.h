#pragma once

#include <common/types.h>

namespace andromeda
{
	class IGraphics;

	class IContext
	{
	public:
		IContext() {}
		virtual ~IContext() {}
 
		virtual Boolean swap() = 0;
	};
}