#ifndef _ANDROMEDA_ENGINE_ENGINE_HPP_
#define _ANDROMEDA_ENGINE_ENGINE_HPP_

namespace andromeda
{
	/*
		Add a System
	*/
	template<class T>
	Boolean Engine::addModule()
	{
		// Component Installed Already!
		// This saves creating an instance of the module
		if (isInstalled<T>())
			return false;

		// Add System to Map
		return addModule(std::make_shared<T>());
	}


	/*
		Adds the System
	*/
	template<class T>
	Boolean Engine::addModule(std::shared_ptr<T> module)
	{
		static_assert(std::is_base_of<andromeda::IModule, T>::value, "Module is NOT an IModule");

		assert(module);
		
		// Insert 
		Boolean inserted = _map.insert<T>(module);

		// Validate
		if (!inserted) return false;
		
		// Start Module :: If the engine is running
		if (_running)
			resume(module);

		return inserted;

	}


	/*
		Removes the System
	*/
	template <class T>
	Boolean Engine::removeModule()
	{
		// Get Module
		std::shared_ptr<T> module = getModulePtr<T>();

		// Validate
		if (!module) return false;

		// Stop Component
		pause(module, true);
		
		// Erase the Module
		return _map.erase<T>();
	}


	/*
		Gets the Module
	*/
	template <class T>
	std::shared_ptr<T> Engine::getModulePtr()
	{
		if (!_map.exists<T>()) return nullptr;

		return _map.at<T>();
	}


	/*
		Resume the Specified System
	*/
	template <class T>
	Boolean Engine::resume()
	{
		return resume(getSystem<T>());
	}

	/*
		Pause the Specified System
	*/
	template <class T>
	Boolean Engine::pause()
	{
		return pause(getModule<T>(), false);
	}



	


}

#endif