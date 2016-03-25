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

#if 0
	/*
		Adds the System
	*/
	template<class T>
	Boolean Engine::addModule(std::shared_ptr<T> module)
	{
		static_assert(std::is_base_of<andromeda::IModule, T>::value, "Derived not derived from BaseClass");

		// Component Installed Already!
		if (isInstalled<T>())
			return false;

		// Get Module ID
		Int32 modId = getModuleId<T>();
		
		// Add System to Map
		_modules[modId] = module;

		// Is the Engine Running? Start Module
		if (_running)
		{
			resume(_modules[modId]);
		}

		// In the Map?
		return !!_modules[modId];
	}


	/*
		Removes the System
	*/
	template <class T>
	Boolean Engine::removeModule()
	{
		// Get Module ID
		Int32 modId = getSystemID<T>();

		// Component Doesn't Exist
		if (! isInstalled<T>())
			return false;

		// Stop Component
		pause(_modules[modId], true);

		// Destroy Component
		_modules.erase(modId);

		// In the Map?
		return !_modules[modId];
	}


	/*
		Gets the Module
	*/
	template <class T>
	std::shared_ptr<T> Engine::getModulePtr()
	{
		// Component Doesn't Exist
		if (!isInstalled<T>())
		{
			// Auto Create
			return nullptr;
		}

		// Get Module ID
		Int32 modId = getModuleId<T>();

		// Retrieve the Module
		return std::static_pointer_cast<T>(_modules[modId]);
	}
#endif

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





#if 0
	/*
		Gets the RAW Module Pointer
	*/
	template <class T>
	T * Engine::getModule()
	{
		// Get Module
		std::shared_ptr<T> module = getModulePtr<T>();

		// Retrieve RAW Pointer
		return ! module ? nullptr : static_cast<T*>(module.get());
	}
#endif




	/*
		Sets the Dependancy
	*/
	template <class T, class DEPENDANCY>
	Boolean Engine::setDependancy()
	{
		if (! isInstalled<T>())
			return false;

		// Sets the Dependancy
		getModule<T>()->addDependancy<DEPENDANCY>(getModulePtr<DEPENDANCY>());

		return true;
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