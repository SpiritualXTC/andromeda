#ifndef _ANDROMEDA_ENGINE_SYSTEM_H_
#define _ANDROMEDA_ENGINE_SYSTEM_H_

/*
	System:
	Controls the running configuration of the engine :)

	This would be the central "controller", if you were to associate as an MVC application :)
*/
#include <set>

#include "module.h"
#include "../Graphics/display.h"

namespace andromeda
{
	// Forward Declarations
	class Config;
	class Engine;

	

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
	
	*/
	class System : public Module < System >
	{
	public:
		friend class Engine;

		enum _SystemEvents
		{
		//	Initialise,
			Close,
			Resize,
			Pause,
			Resume,
		};


	public:
		System(Engine * engine, std::weak_ptr<Module<Config>> config);
		virtual ~System();

		// Getters
		const Int32 displayWidth() const { return _display.format.width; }
		const Int32 displayHeight() const { return _display.format.height; }
		const DisplayMode displayMode() const { return _display.mode; }
		

		/*
			These will need to take a lot more parameters (quite possibly an entire structure :P
			But for the most part, method-overloading will solve it :)

			Adjust these so that they have default parameters instead of 600 functions.
		*/
		Boolean changeDisplaySettings(Int width, Int32 height);
		Boolean changeDisplaySettings(DisplayMode mode);
		Boolean changeDisplaySettings(DisplayFormat format);
		Boolean changeDisplaySettings(Int width, Int32 height, DisplayMode mode);


		/*
			Looks at the Platform for a list of supported Display Settings
			...
			Should probably be a list, instead of a set.
		*/
		Boolean enumerateDisplaySettings(std::set<DisplayFormat> & displayModes);


		/*
			Updates the Current Display Settings to the Configuration, for export
		*/
		Boolean updateDisplaySettings();


		/*
			Get Display Resolution.
		*/
		Boolean getDisplayResolution(Int32 & width, Int32 & height);



		

		/*
			
		*/
		Boolean quit();

		Boolean close();
		Boolean pause();
		Boolean resume();



		// IModule
		void onResume() override { return; }
		void onPause() override { return; }
		void update() override { return; }
		
	private:


		/*
			Bootstrap Initialisation!
		*/
		Boolean run();



		Boolean changeDisplaySettings(const DisplayParameters & dp);

		void dispatchResizeEvent();

		DisplayParameters _display;

		Engine * _engine = nullptr;
	};
}

typedef andromeda::System aSystem;

#endif