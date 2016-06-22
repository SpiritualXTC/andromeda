#ifndef _ANDROMEDA_ANDROMEDA_H_
#define _ANDROMEDA_ANDROMEDA_H_


// Standard Library
#include <memory>

// Andromeda
#include "stddef.h"

#include "Utilities/singleton.h"



// TMEP
#include <andromeda/Utilities/log.h>


#if BOOST_OS_WINDOWS
#include <Windows.h>
#endif





// TEMP
#include <andromeda/Resources/resource_manager.h>




namespace andromeda
{
	// Forward Declarations
	class Application;
	class Display;
	struct DisplayParameters;
	class Engine;
	class Config;
	class Renderer;
	class System;
	class Timing;
	
	class ResourceManager;

	class Platform;
	class Context;


	class Mouse;
	class Keyboard;


	class Graphics;

	/*
		Namespace Functionality :)
	*/





	class IAndromeda
	{
	public:

		virtual inline std::shared_ptr<ResourceManager> & getResourceManager() = 0;
		virtual inline std::shared_ptr<Config> & getConfig() = 0;
		virtual inline std::shared_ptr<System> & getSystem() = 0;
		virtual inline std::shared_ptr<Engine> & getEngine() = 0;
		virtual inline std::shared_ptr<Graphics> & getGraphics() = 0;

		virtual inline std::shared_ptr<Timing> & getTiming() = 0;

		virtual inline std::shared_ptr<Renderer> & getRenderer() = 0;


		virtual void run(std::shared_ptr<Application> & app) = 0;
		virtual void quit() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;
	};






	/*
	
		Move this OUT of the interface library
	
	*/







	/*
		Class used to initialise the engine
	*/
	class IAndromedaConfig
	{
	public:
		virtual void init() = 0;

		virtual std::shared_ptr<Display> initDisplay(const DisplayParameters & dp) = 0;
		virtual std::shared_ptr<Platform> initPlatform() = 0;
		virtual std::shared_ptr<Context> initContext() = 0;
		virtual std::shared_ptr<Graphics> initGraphics() = 0;
	};




	/*
		This is going to be the new access point rather than the engine...

		This access point will be able to access quite a lot of things... engine, resources, configs, etc

		It will control how each platform loads

		This COULD be a singleton, however it will depend on how it gets initialise whether it will work as a singleton... :)
	*/
	class Andromeda : virtual public IAndromeda
	{
		// Static :: Special Case Singleton :: This could even be moved to another class altogether, once namespace functions are in use.
	public:

		/*
			Initialise Andromeda
		*/
		static Boolean initialise(IAndromedaConfig * config)
		{
			assert(!_instance);

			log_debugp("Andromeda :: initialise();");

			// Create Instance
			_instance = std::make_shared<Andromeda>(config);
			 

			log_debugp("Andromeda :: initialisation() done;");

			return !!_instance;
		}


		/*
			Destroy Andromeda
		*/
		static Boolean destroy()
		{
			log_debugp("Andromeda :: destroy();");

			assert(_instance);
			_instance->quit();

			// Lower Reference Count
			_instance.reset();

			return true;
		}


		/*
			Get Instance of the Engine :: MOST functionality should have namespace-level functions
		*/
		static inline IAndromeda * instance() 
		{ 
			assert(_instance);
			return _instance.get(); 
		}

	private:
		static std::shared_ptr<Andromeda> _instance;














		// Instance
	public:
		Andromeda(IAndromedaConfig * config);
		virtual ~Andromeda();

		


		inline std::shared_ptr<ResourceManager> & getResourceManager() override { return _resources; }
		
		inline std::shared_ptr<Config> & getConfig() override{ return _config; };
		inline std::shared_ptr<System> & getSystem() override { return _system; };
		inline std::shared_ptr<Engine> & getEngine() override { return _engine; };
		inline std::shared_ptr<Graphics> & getGraphics() override { return _graphics; }

		inline std::shared_ptr<Timing> & getTiming() override {return _timing;}

		inline std::shared_ptr<Renderer> & getRenderer() override { return _renderer; }

		void run(std::shared_ptr<Application> & app);
		void quit();

		void pause();
		void resume();



	private:


		std::shared_ptr<Config> _config;
		std::shared_ptr<System> _system;

		std::shared_ptr<Engine> _engine;
		std::shared_ptr<Graphics> _graphics;

		std::shared_ptr<Timing> _timing;
		std::shared_ptr<Renderer> _renderer;

		std::shared_ptr<ResourceManager> _resources;
	};




	/*
		Namespace level "quick" functions

		Not sure if they should exist in THIS file or not...
	*/

	template <typename RESOURCE>
	inline std::shared_ptr<RESOURCE> LoadResource(const std::string filename, const std::string locationName = "")
	{
		return Andromeda::instance()->getResourceManager()->loadResource<RESOURCE>(filename, locationName);
	}




	/* Run */
	inline void run(std::shared_ptr<Application> & app)
	{
		Andromeda::instance()->run(app);
	}

	/* Destroy */
	inline void destroy()
	{
		Andromeda::destroy();
	}






	inline std::shared_ptr<ResourceManager> resources()
	{
		return Andromeda::instance()->getResourceManager();
	}

	inline std::shared_ptr<Graphics> graphics()
	{
		return Andromeda::instance()->getGraphics();
	}




	/* Initialise - Platform Specific */
#if BOOST_OS_WINDOWS
	Boolean initialise(HINSTANCE hInstance);
#endif

}



#endif