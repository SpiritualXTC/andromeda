#include "module.h"

using namespace andromeda;

ModuleContainer::ModuleContainer()
{

}

ModuleContainer::~ModuleContainer()
{

}

Boolean ModuleContainer::insert(ClassId id, std::shared_ptr<IModule> m)
{
	assert(m);

	if (exists(id))
		return false;
	_modules.insert({ id, m });
	return exists(id);
}

Boolean ModuleContainer::exists(ClassId id)
{
	return _modules.find(id) != _modules.end();
}


Boolean ModuleContainer::open()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->open();

	return b;
}

Boolean ModuleContainer::close()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->close();
	return b;
}

Boolean ModuleContainer::resume()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->resume();
	return b;
}

Boolean ModuleContainer::pause()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->pause();
	return b;
}

Boolean ModuleContainer::update()
{
	Boolean b = true;
	for (auto m : _modules)
		b &= m.second->update();
	return b;
}
