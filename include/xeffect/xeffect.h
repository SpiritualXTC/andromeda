#pragma once


#include <memory>
#include <string>



/*
	Sections of XEffect can be moved to the core engine :: Specifically as they are generic implementations of an interface :D

	However it will need to be done as the library is tested...



	TODO:
	Remove the andromeda namespace
*/
namespace andromeda
{
	namespace xeffect
	{
		// Forward Declarations
		class XEffect;


		// Callback function for the loader when loading support files.
		class IXEffectLoadFileCallback
		{
		public:
			virtual std::string loadFile(const std::string & filename) = 0;
		};

		std::shared_ptr<XEffect> LoadEffect(const std::string & filename, IXEffectLoadFileCallback * callback = nullptr);
		std::shared_ptr<XEffect> LoadEffectFromSource(const std::string & source, IXEffectLoadFileCallback * callback = nullptr);
	}
}
