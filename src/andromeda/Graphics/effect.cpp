#include <andromeda/Graphics/effect.h>

#include <cassert>

#include <andromeda/Graphics/pass.h>
#include <andromeda/Graphics/technique.h>

using namespace andromeda;

/*

*/
Effect::Effect()
{

}


/*

*/
Effect::~Effect()
{

}


/*

*/
Boolean Effect::addTechnique(const std::string & technique, Int32 group)
{
	// Must NOT be Active
	assert(!isActive());

	// Technique Exists ?
	if (hasTechnique(technique))
		return false;

	// Create Technique
	_techniques[technique] = std::make_shared<Technique>(group);

	// Set as Current Technique
	if (!_curTechnique)
		_curTechnique = _techniques[technique];

	// Technique Addded
	return hasTechnique(technique);
}

/*

*/
Boolean Effect::removeTechnique(const std::string & technique)
{
	// Must NOT be Active
	assert(!isActive());

	// Technique Exists ?
	if (! hasTechnique(technique))
		return false;

	// Unset Current Technique
	if (_curTechnique == _techniques[technique] && _techniques.begin() != _techniques.end())
		_curTechnique = _techniques.begin()->second;
	else
		_curTechnique = nullptr;

	// Erase Technique
	_techniques.erase(technique);

	// Technique Removed
	return !hasTechnique(technique);
}



/*

*/
Boolean Effect::hasTechnique(const std::string & technique)
{
	return !!_techniques[technique];
}



/*

*/
Boolean Effect::setActiveTechnique(const std::string & technique)
{
	// Must NOT be Active
	assert(!isActive());

	if (hasTechnique(technique))
	{
		_curTechnique = _techniques[technique];
		return true;
	}

	return false;
}








Boolean Effect::isActive()
{
	if (! _curTechnique)
		return false;

	return _curTechnique->isActive();;
}



#if 0
/*

*/
Boolean Effect::addPass(const std::string & technique, const std::string & pass)
{
	return addPass(_techniques[technique], pass);
}

/*

*/
Boolean Effect::addPass(const std::string & pass)
{
	return addPass(_curTechnique, pass);
}
#endif


/*

*/
Boolean Effect::addPass(const std::string & technique, std::shared_ptr<Pass> pass)
{
	return addPass(_techniques[technique], pass);
}

/*

*/
Boolean Effect::addPass(std::shared_ptr<Technique> technique, std::shared_ptr<Pass> pass)
{
	// Technique Must be Valid
	assert(technique);

	technique->addPass(pass);

	return false;
}





/*

*/
Boolean Effect::removePass(const std::string & technique, const std::string & pass)
{
	return removePass(_techniques[technique], pass);;
}

/*

*/
Boolean Effect::removePass(const std::string & pass)
{
	return removePass(_curTechnique, pass);;
}

/*

*/
Boolean Effect::removePass(std::shared_ptr<Technique> technique, const std::string & pass)
{
	// Technique Must be Valid
	assert(technique);

	return false;
}




/*

*/
std::shared_ptr<Pass> getPass(std::shared_ptr<Technique> technique, const std::string & pass)
{
	return nullptr;
}

/*

*/
std::shared_ptr<Pass> getPass(std::shared_ptr<Technique> technique, Int32 index)
{
	return nullptr;
}




/*

*/
Int32 Effect::numPasses()
{
	// Must have a current Technique
	assert(_curTechnique);

	return _curTechnique->numPasses();
}


/*

*/
Boolean Effect::beingPass(Int32 index)
{
	// Must have a current Technique
	assert(_curTechnique);

	// Begin the Pass
	return _curTechnique->beginPass(index);;
}


/*

*/
Boolean Effect::endPass()
{
	// Must have a current Technique
	assert(_curTechnique);

	// End the Pass
	return _curTechnique->endPass();;
}
















