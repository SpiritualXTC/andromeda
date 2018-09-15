#pragma once

#include <set>
#include <unordered_map>
#include <memory>

#include <common/types.h>
#include <common/class.h>

/*
	TODO:

	Look into boost::concept_check to force constraints on the modules being added
*/

namespace andromeda
{
	// Forward-Declarations
	class IModule;


	class Engine
	{
	public:
		Engine();
		virtual ~Engine();


		Boolean open();
		Boolean close();
		Boolean resume();
		Boolean pause();
		Boolean update();


		Boolean run();
		Boolean quit();


		template <typename T>
		Boolean insert(std::shared_ptr<IModule> m) { return insert(IClass<T>::id(), m); }

		template <typename T>
		Boolean exists() { return exists(IClass<T>::id()); }

		template <typename T>
		std::shared_ptr<T> find() 
		{
			std::shared_ptr<IModule> m = find(IClass<T>::id());
			return std::static_pointer_cast<T>(m);
		}
	protected:
		
		Boolean insert(ClassId id, std::shared_ptr<IModule> _modules);
		Boolean exists(ClassId id);

		std::shared_ptr<IModule> find(ClassId id);

	private:
		// TODO: Sort modules ...  by something other than their insertion order :)
		std::unordered_map<ClassId, std::shared_ptr<IModule>> _modules;
		Boolean _running;
	};

#if 0
	// Forward Declarations
	class IModuleOLD;

	/*

	*/
	class Engine : public TemplateContainer<IModuleOLD>
	{
	public:
		Engine();
		virtual ~Engine();

		// Run the Engine
		void run();

		// Stop the Engine, after the next completed update cycle
		void stop();

		// Determines if a Module is installed :: Potential Bug
		template <class T>
		const inline Boolean isInstalled() { return _map.exists<T>(); }

		// Is the Module Active? :: Potential Bug
		template <class T>
		const inline Boolean isRunning() { return isRunning(getModuleId<T>()); }

		// Adds the Module
		template <class T>
		Boolean addModule(std::shared_ptr<T> module);

		// Removes the Module
		template <class T>
		Boolean removeModule();

		// Gets the Module as a raw pointer
		template <class T>
		inline T * getModule()
		{
			std::shared_ptr<T> p = getModulePtr<T>();
			return p.get();
		}

		// Gets the Module Pointer
		template <class T>
		std::shared_ptr<T> getModulePtr()
		{
			if (!_map.exists<T>()) return nullptr;
			return _map.at<T>();
		}



		/*
		// Resume a module
		template <class T>
		Boolean resume();

		// Pause a module
		template <class T>
		Boolean pause();
		*/



		void resume();
		void pause();



		/*
			TEMP: Debug Output
		*/
		void debugOutput();

	private:

		Boolean start(std::shared_ptr<IModuleOLD> module);
		Boolean resume(std::shared_ptr<IModuleOLD> module);
		Boolean pause(std::shared_ptr<IModuleOLD> module);
		Boolean stop(std::shared_ptr<IModuleOLD> module);

		Boolean isRunning(std::shared_ptr<IModuleOLD> module);


		Boolean _running = false;											// Is the System Running ?



		std::multiset<std::shared_ptr<IModuleOLD>> _active;					// Running Modules

		TemplateMap<IModuleOLD> _map;											// All Modules
	};

#endif
}

// Include Template Functionality
//#include "engine.hpp"


//typedef andromeda::Engine aEngine;
