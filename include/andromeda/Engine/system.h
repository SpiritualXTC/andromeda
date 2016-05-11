#ifndef _ANDROMEDA_ENGINE_SYSTEM_H_
#define _ANDROMEDA_ENGINE_SYSTEM_H_

/*

*/
#include <set>

#include "module.h"
#include "display.h"

#include <andromeda/Utilities/log.h>

namespace andromeda
{
	// Forward Declarations
	class Context;
	class Display;
	class Platform;

	class IAndromedaConfig;
	

	/*
		System Events
	*/
	struct CloseEventArgs
	{
		Boolean cancel;
	};


	struct AppEventArgs
	{
		Int32 displayWidth;
		Int32 displayHeight;
	};

	

	/*
		used for access... add to later :)
	*/
	class ISystem
	{
	public:
		ISystem() {}
		virtual ~ISystem() {}

	// Interface

	};



	/*
		System:
	*/
	class System : virtual public ISystem
	{
	public:
		enum _SystemEvents
		{
		//	Initialise,
			Close,
			Resize,	// TODO: Move to Display
			Pause,
			Resume,
		};


	public:
		System(IAndromedaConfig * config);
		virtual ~System();


		/*
			Getters
		*/
		const inline std::shared_ptr<Display> getDisplay() { return _display; }
		const inline std::shared_ptr<Platform> getPlatform() { return _platform; }
		const inline std::shared_ptr<Context> getContext() { return _context; }

		/*
			Final Initialisation
		*/
		Boolean init();

		/*
			Final Destruction
		*/
		Boolean destroy();


		/*
			Close

			TODO:: Remove or clean up
		*/
		Boolean close();





		/* Pass Through Functions :: Display */
		

		/*
			Change Display Settings
		*/
		Boolean changeDisplaySettings(DisplayParameters & dp);

		/* Pass Through Functions :: Platform */

		/* Pass Through Functions :: Context */

	private:		
		std::shared_ptr<Display> _display;
		std::shared_ptr<Platform> _platform;
		std::shared_ptr<Context> _context;
	};
}

typedef andromeda::System aSystem;

#endif