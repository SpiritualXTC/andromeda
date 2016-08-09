#pragma once

// Standard Library
#include <memory>

// Andromeda
#include "stddef.h"



namespace andromeda
{
	// Forward Declarations
	class Application;
	class Config;
	class Engine;
	class Graphics;
	class ResourceManager;
	class SceneManager;
	class System;
	class Timing;
	
	
	// TEMP
	class IAndromedaConfig;






	/*
		Namespace Functionality
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

		virtual inline std::shared_ptr<SceneManager> & getSceneManager() = 0;


		virtual void run(std::shared_ptr<Application> app) = 0;
		virtual void quit() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;
	};















	/*

	*/
	class Andromeda : virtual public IAndromeda
	{
		// Static :: Special Case Singleton
		// TODO: Move to another class, that isn't exposed to the API

	public:

		/*
			Initialise Andromeda
		*/
		static Boolean initialise(IAndromedaConfig * config);

		/*
			Destroy Andromeda
		*/
		static Boolean destroy();


		/*
			Get Instance :: MOST functionality should have namespace-level functions
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

		inline std::shared_ptr<SceneManager> & getSceneManager() override { return _scenes; }

		void run(std::shared_ptr<Application> app);
		void quit();

		void pause();
		void resume();



	private:


		std::shared_ptr<Config> _config;
		std::shared_ptr<System> _system;

		std::shared_ptr<Engine> _engine;
		std::shared_ptr<Graphics> _graphics;

		std::shared_ptr<Timing> _timing;
		std::shared_ptr<SceneManager> _scenes;

		std::shared_ptr<ResourceManager> _resources;
	};









	/* Run */
	inline void run(std::shared_ptr<Application> app)
	{
		Andromeda::instance()->run(app);
	}

	/* Destroy */
	inline void destroy()
	{
		Andromeda::destroy();
	}


	/* Resource Manager */
	inline std::shared_ptr<ResourceManager> resources()
	{
		return Andromeda::instance()->getResourceManager();
	}

	/* Scene Manager */
	inline std::shared_ptr<SceneManager> scenes()
	{
		return Andromeda::instance()->getSceneManager();
	}

	/* Graphics API */
	inline std::shared_ptr<Graphics> graphics()
	{
		return Andromeda::instance()->getGraphics();
	}
}
