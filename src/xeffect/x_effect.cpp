#include "x_effect.h"

#include "x_technique.h"

using namespace andromeda;
using namespace andromeda::xeffect;

/*

*/
XEffect::XEffect()
{

}


/*

*/
XEffect::~XEffect()
{

}






/*
	Technique Exists 
*/
Boolean XEffect::hasTechnique(const std::string & name) const
{
	const auto & find = _technique.find(name);

	return find != _technique.end();
}

/*
	Get the Technique
*/
std::shared_ptr<ITechnique> XEffect::getTechnique(const std::string & name) const
{
	const auto & find = _technique.find(name);

	return find != _technique.end() ? find->second : nullptr;
}

std::shared_ptr<ITechnique> XEffect::getTechniqueDefault() const
{
	/*
		TODO: Add a default technique thingy to XEffect and the XML

		TODO: Test this ....
	*/
	const auto & first = _technique.begin();

	return first != _technique.end() ? first->second : nullptr;
}

/*
	Add a Technique
*/
Boolean XEffect::addTechnique(std::shared_ptr<XTechnique> & technique)
{
	assert(technique);

	const std::string & name = technique->getName();

	// Pass Exists ?
	if (hasTechnique(name))
		return false;

	// Insert Pass
	_technique[name] = technique;

	return true;
}