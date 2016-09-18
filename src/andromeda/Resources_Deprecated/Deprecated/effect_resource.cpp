#include "effect_resource.h"
//#include <andromeda/Resources/effect_resource.h>

#include <andromeda/Graphics/effect.h>

#include <andromeda/Resources/resource_manager.h>

#include <string>

#include <andromeda/andromeda.h>

#include "../../xeffect/x_effect.h"
#include "../../xeffect/xloader.h"

using namespace andromeda;



class EffectLoaderBypass
{
public:
	EffectLoaderBypass(std::string & location)
		: _location(location)
	{

	}

	std::string loadFileResource(const std::string & filename)
	{
		//	andromeda::LoadResource<andromeda::Effect>(filename);
		
		log_debugp("Loading '%1%' from resource bypass callback", filename);

		log_warnp("Resource is loaded from first found location");
		log_warnp("Loading from same (or Specified) location is currently unsupported");

		std::shared_ptr<File> file = andromeda::Andromeda::instance()->getResourceManager()->loadResourceSupport<Effect>(filename);

		return file->data();
	}

private:
	std::string _location;
};





template<>
std::shared_ptr<Effect> ResourceLoader::build<Effect>(std::shared_ptr<File> file)
{
	std::string loc = "";

	EffectLoaderBypass bypass(loc);

	xeffect::XEffectLoader loader;

	loader.setLoadFileCallback(std::bind(&EffectLoaderBypass::loadFileResource, bypass, std::placeholders::_1));

	std::shared_ptr<Effect> effect = loader.loadFromSource(file->data());

	return effect;
}