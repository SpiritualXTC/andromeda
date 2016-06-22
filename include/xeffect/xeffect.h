#pragma once


#include <memory>
#include <string>



/*
	Sections of XEffect can be moved to the core engine :: Specifically as they are generic implementations of an interface :D

	However it will need to be done as the library is tested...
*/
namespace andromeda
{
	namespace xeffect
	{
		// Forward Declarations
		class XEffect;


		std::shared_ptr<XEffect> LoadEffect(const std::string & filename);
		std::shared_ptr<XEffect> LoadEffectFromSource(const std::string & source);
	}
}
