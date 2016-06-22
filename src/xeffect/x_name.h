#pragma once

#include <string>

namespace andromeda
{
	namespace xeffect
	{

		template <class T>
		struct XNameGenerator
		{
			std::string generate(const std::string & def)
			{
				static Int32 counter = 0;

				// Setup Default Name
				std::stringstream defName;
				defName << def << "_" << (++counter);

				return defName.str();
			}
		};
	}
}