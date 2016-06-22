#pragma once

#include <andromeda/stddef.h>
#include <andromeda/exception.h>

namespace andromeda
{
	namespace xeffect
	{
		class XShaderException : virtual public Exception
		{
		public:
			XShaderException(const std::string & message) : Exception(message)
			{

			}

		private:
		};
	}
}
