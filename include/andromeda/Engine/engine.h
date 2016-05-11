#ifndef _ANDROMEDA_ENGINE_ENGINE_H_
#define _ANDROMEDA_ENGINE_ENGINE_H_

#include <set>
#include <unordered_map>
#include <memory>


#include <andromeda/stddef.h>

#include <andromeda/Containers/template_map.h>
#include <andromeda/Utilities/template.h>


namespace andromeda
{
	// Forward Declarations
	class IModule;
	class System;


	/*
	
	*/
	class Engine : public TemplateContainer<IModule>
	{
	public:
		Engine();
		virtual ~Engine();


		/*
			Run the Engine 
			
			TODO Rename :: start();
		*/
		void run();

		/*
			Stop the Engine, after the next completed update cycle
		*/
		void stop();

	
		/*
			Determines if a System is installed :: Potential Bug
		*/
		template <class T>
		const inline Boolean isInstalled() { return _map.exists<T>(); }


		/*
			Is the System Active? :: Potential Bug
		*/
		template <class T>
		const inline Boolean isRunning() { return isRunning(getModuleId<T>()); }


		/*
			Creates and Adds the System: Currently Requires an Empty constructor :)
		*/
		template <class T>
		Boolean addModule();


		/*
			Adds the System
		*/
		template <class T>
		Boolean addModule(std::shared_ptr<T> module);


		/*
			Removes the System
		*/
		template <class T>
		Boolean removeModule();


		/*
			Gets the Module Pointer
		*/
		template <class T>
		std::shared_ptr<T> getModulePtr();


		/*
			Gets the Module as a raw pointer
		*/
		template <class T>
		inline T * getModule()
		{
			std::shared_ptr<T> p = getModulePtr<T>();
			return p.get();
		}


		/*
			Sets a Module as a Dependancy
		*/
//		template <class T, class DEPENDANCY>
//		Boolean setDependancy();


		/*
			Resume the Module
		*/
		template <class T>
		Boolean resume();


		/*
			Pause the Module
		*/
		template <class T>
		Boolean pause();

		/*
			Resume the Engine and all Components
		*/
		void resume();

		/*
			Pause the Engine and all Components
		*/
		void pause(Boolean stop);



		/*
			Debug Output
		*/
		void debugOutput();

	private:
		
		
		
		/*
			Resume the Specified Component
		*/
		Boolean resume(std::shared_ptr<IModule> module);

		/*
			Pause the Specified Component
		*/
		Boolean pause(std::shared_ptr<IModule> system, Boolean stop);

		/*
			Is the Specified Module Running ?
		*/
		Boolean isRunning(std::shared_ptr<IModule> module);


		Boolean _running = false;											// Is the System Running ?



		std::multiset<std::shared_ptr<IModule>> _active;					// Running Modules

		TemplateMap<IModule> _map;											// All Modules
	};
}

// Include Template Functionality
#include "engine.hpp"


typedef andromeda::Engine aEngine;

#endif