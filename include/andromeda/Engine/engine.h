#ifndef _ANDROMEDA_ENGINE_ENGINE_H_
#define _ANDROMEDA_ENGINE_ENGINE_H_

#include <set>
#include <unordered_map>
#include <memory>


#include "../stddef.h"

namespace andromeda
{
	// Forward Declarations
	class IModule;
	



	class Engine
	{
	public:
		Engine();
		virtual ~Engine();


		/*
			Run the Engine
		*/
		void run();

		/*
			Quit the Engine
		*/
		void quit();

		



		/*
			Gets the System ID Mapped to T
		*/
		template <class T>
		//const inline Int32 getModuleID() { return Module<T>::getTemplateID(); }
		//const inline Int32 getModuleID() { return T::getTemplateID(); }
		const inline Int32 getModuleID() { return TemplateID<T, IModule>::getTemplateID(); }

		/*
			Determines if a System is installed
		*/
		template <class T>
		const inline Boolean isInstalled() { return !!_modules[getModuleID<T>()]; }


		/*
			Is the System Active?
		*/
		template <class T>
		const inline Boolean isRunning() { return isRunning(getModuleID<T>()); }


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
		T * getModule();


		/*
			Sets a Module as a Dependancy
		*/
		template <class T, class DEPENDANCY>
		Boolean setDependancy();


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
		std::unordered_map<Int32, std::shared_ptr<IModule>> _modules;		// All Installed Modules
	};
}

// Include Template Functionality
#include "engine.hpp"


#endif