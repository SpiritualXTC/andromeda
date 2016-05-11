#pragma once

#include <andromeda/Utilities/log.h>

namespace andromeda
{

	/*
		Technically not needed ?
	*/
	template <typename T>
	class AndromedaConfig : virtual public IAndromedaConfig
	{
	public:
		void test()
		{
			log_errp("Unknown Platform");
		}
	};
}