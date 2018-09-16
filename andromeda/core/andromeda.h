#pragma once

#include <list>
#include <memory>
#include <common/types.h>

namespace andromeda
{
	// Forward-Declarations
	class Config;
	class Platform;

	class Input;

	class SceneControl;
	class Timing;
	class Graphics;

	class Engine;

//	class System;
//	

//	class ResourceFactory;

	class Andromeda
	{
	public:
		Andromeda();
		virtual ~Andromeda();

		
		Boolean run();
		Boolean quit();


		inline std::shared_ptr<Engine> getEngine() { return _engine; }

	private:
		std::shared_ptr<Engine> _engine;
		
		std::shared_ptr<Config> _config;
		std::shared_ptr<Platform> _platform;

		// Modules
		std::shared_ptr<Timing> _timing;
		std::shared_ptr<Graphics> _graphics;
		
		bool _running;
	};
}