#include <xeffect/xeffect.h>

#include "x_effect.h"
#include "xloader.h"

using namespace andromeda;
using namespace andromeda::xeffect;




/*
	Loads an Effect from File
*/
std::shared_ptr<XEffect> xeffect::LoadEffect(const std::string & filename, IXEffectLoadFileCallback * callback)
{
	XEffectLoader loader;

	if (callback)
		loader.setLoadFileCallback(std::bind(&IXEffectLoadFileCallback::loadFile, callback, std::placeholders::_1));

	return loader.loadFromFile(filename);
}


/*
	Loads an Effect from Source
*/
std::shared_ptr<XEffect> xeffect::LoadEffectFromSource(const std::string & source, IXEffectLoadFileCallback * callback)
{
	XEffectLoader loader;

	if (callback)
		loader.setLoadFileCallback(std::bind(&IXEffectLoadFileCallback::loadFile, callback, std::placeholders::_1));

	return loader.loadFromSource(source);
}