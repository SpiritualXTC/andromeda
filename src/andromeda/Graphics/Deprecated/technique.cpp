#include <andromeda/Graphics/Deprecated/technique.h>

#include <algorithm>
#include <cassert>

#include <andromeda/Graphics/Deprecated/pass.h>

using namespace andromeda;

/*

*/
Technique::Technique(Int32 group)
	: _group(group)
{

}


/*

*/
Technique::~Technique()
{

}

#if 0
/*

*/
Boolean Technique::addPass(const std::string & pass)
{
	assert(!_active);

	

	return addPass(std::make_shared<Pass>(pass));
}
#endif

/*

*/
Boolean Technique::addPass(std::shared_ptr<Pass> pass)
{
	assert(!_active);

	// Push to Back (Allow for Insertion Later)
	_passes.push_back(pass);

	return true;
}




/*

*/
Boolean Technique::removePass(const std::string & pass)
{
	assert(!_active);

	// Remove passes with matching names
	auto rem = std::remove_if(_passes.begin(), _passes.end(), [&](const std::shared_ptr<Pass> p){return pass == p->name(); });
	
	// Erase any elements at the end...
	if (rem != _passes.end())
		_passes.erase(rem, _passes.end());

	return true;
}





/*

*/
Boolean Technique::beginPass(Int32 index)
{
	assert(!_active);

	// Set Active Pass
	_active = _passes[index];

	// Begin Pass
	_active->begin();

	return true;
}


/*

*/
Boolean Technique::endPass()
{
	assert(_active);

	// End Pass
	_active->end();

	// Set Inactive Pass
	_active = nullptr;

	return true;
}
