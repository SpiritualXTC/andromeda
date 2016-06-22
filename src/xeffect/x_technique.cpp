#include "x_technique.h"

#include <cassert>
#include <algorithm>

#include "x_pass.h"

using namespace andromeda;
using namespace andromeda::xeffect;


/*

*/
XTechnique::XTechnique(const std::string & name)
	: _name(name)
{

}


/*

*/
XTechnique::~XTechnique()
{


}


/*

*/
Boolean XTechnique::hasPass(const std::string & name) const
{
	//const auto & find = _passes.find(name);
	const auto & find = std::find_if(_passes.begin(), _passes.end(), [&name](const std::shared_ptr<XPass> & pass) {return pass->getName() == name; });

	return find != _passes.end();
}


/*

*/
Boolean XTechnique::addPass(std::shared_ptr<XPass> & pass)
{
	assert(pass);

	const std::string & name = pass->getName();

	// Pass Exists ?
	if (hasPass(name))
		return false;

	// Insert Pass
	//_passes[name] = pass;
	_passes.push_back(pass);

	return true;
}


/*

*/
std::shared_ptr<IPass> XTechnique::getPass(const std::string & name) const
{
//	const auto & find = _passes.find(name);
//	return find != _passes.end() ? find->second : nullptr;
	const auto & find = std::find_if(_passes.begin(), _passes.end(), [&name](const std::shared_ptr<XPass> & pass) {return pass->getName() == name; });

	return find != _passes.end() ? *find : nullptr;
}


/*

*/
std::shared_ptr<IPass> XTechnique::getPass(const Int32 index) const
{
	return _passes[index];
}