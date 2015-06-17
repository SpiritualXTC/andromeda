#ifndef _ANDROMEDA_ENGINE_SYSTEM_H_
#define _ANDROMEDA_ENGINE_SYSTEM_H_

/*
	System:
	Controls the running configuration of the engine :)

	This would be the central "controller", if you were to associate as an MVC application :)
*/
#include <set>

#include "module.h"

namespace andromeda
{
	class Config;
	class Engine;

	/*
		Display Structures

		allt he display structures/enums should be moved to graphics/display.h
	*/

	enum class DisplayMode
	{
	//	Fullscreen,		// Fullscreen Exclusive Mode
		Borderless,		// Fullscreen Borderless Window Mode
		Windowed,		// Windowed Mode
	};



	struct DisplayFormat
	{
		Int32 width;
		Int32 height;
		//Int32 bitDepth;		// Is anything else other 32bit likely to be needed ??

		/*
			operators for the std::set.
		*/
		friend Boolean operator ==(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return lhs.width == rhs.width && lhs.height == rhs.height;// && lhs.bitDepth == rhs.bitDepth;
		}
		friend Boolean operator <(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return lhs.width < rhs.width || lhs.height < lhs.height;// || lhs.bitDepth < rhs.bitDepth;
		}
	};


	struct DisplayParameters
	{
		//	Int32 width;
		//	Int32 height;
		DisplayFormat format;

		DisplayMode mode;
	};


	/*
		System Events
	*/
	struct CloseEventArgs
	{
		Boolean cancel;
	};

	struct ResizeEventArgs
	{
		Int32 displayWidth;
		Int32 displayHeight;
	};

	struct AppEventArgs
	{

	};

	





	/*
	
	*/
	class System : public Module < System >
	{
	public:
		enum _SystemEvents
		{
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
			Close
		*/
		Boolean close();
		Boolean pause();
		Boolean resume();



		// IModule
		void onResume() override { return; }
		void onPause() override { return; }
		void update() override { return; }
		
	private:
		Boolean changeDisplaySettings(const DisplayParameters & dp);

		void dispatchResizeEvent();

		DisplayParameters _display;

		Engine * _engine = nullptr;
	};
}

typedef andromeda::System aSystem;

#endif