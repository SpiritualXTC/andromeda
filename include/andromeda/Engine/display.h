#ifndef _ANDROMEDA_GRAPHICS_DISPLAY_H
#define _ANDROMEDA_GRAPHICS_DISPLAY_H

/*
	display.h:

	This file should probably be in another folder. probably engine (ie: Core)
*/

#include <set>

#include <andromeda/stddef.h>

#include <andromeda/Utilities/observer.h>

namespace andromeda
{
	// Forward Declarations
	class Platform;



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

		/*
			operators for the std::set.
		*/
		friend Boolean operator ==(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return lhs.width == rhs.width && lhs.height == rhs.height;
		}

		friend Boolean operator !=(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return !(lhs == rhs);
		}

		friend Boolean operator <(const DisplayFormat & lhs, const DisplayFormat & rhs)
		{
			return lhs.width < rhs.width || lhs.height < lhs.height;
		}
	};


	struct DisplayParameters
	{
		DisplayFormat resolution;

		DisplayMode mode;

		friend Boolean operator ==(const DisplayParameters & lhs, const DisplayParameters & rhs)
		{
			return lhs.resolution == rhs.resolution && lhs.mode == rhs.mode;
		}

		friend Boolean operator !=(const DisplayParameters & lhs, const DisplayParameters & rhs)
		{
			return !(lhs == rhs);
		}
	};




	/*
		Controls the Display...	
	*/
	class Display : virtual public IObserver<Platform>
	{
	public:
		enum _DisplayEvents
		{
			Resize,
		};


	public:
		Display(const DisplayParameters & dp);
		virtual ~Display();

		/*
			Get Number of Displays Connected to the Device
		*/
		virtual Int32 getNumDisplays() = 0;

		/*
			Get List of Display Devices
		*/
		virtual Boolean enumDisplayDevices() = 0;

		/*
			Get List Display Settings Available for the Primary Device
		*/
		virtual std::set<DisplayFormat> enumDisplaySettings() = 0;

		/*
			Get Current Screen Resolution
		*/
		virtual Boolean getScreenResolution(Int32 & width, Int32 & height) = 0;
		



		/*
			Gets Display Mode
		*/
		const DisplayMode & getDisplayMode() { return _display.mode; }
		const DisplayParameters & getDisplayParameters() { return _display; }



		/*
			Change Display Settings :: Changes the DisplayParameters :: Some Systems this may be limited (EG Mobile)
		*/
		Boolean changeDisplaySettings(const DisplayParameters & dp);



		/*
			Get Display Resolution
		*/
		Boolean getDisplayFormat(Int32 & width, Int32 & height);

		/* Get Display Width */
		const inline Int32 getDisplayWidth() const { return _displayWidth; }

		/* Get Display Height */
		const inline Int32 getDisplayHeight() const { return _displayHeight; }




		// Observable
		void notify(const Platform * const platform) override;


		virtual Boolean restoreScreenResolution() = 0;

	protected:
		virtual Boolean changeScreenResolution(const Int32 width, const Int32 height) = 0;


		

	private:

		/*
			Set Display Dimensions, Dispatch Resize Event
		*/
		Boolean resize(Int32 width, Int32 height);

		DisplayParameters _display;

		// Actual Display Dimensions
		Int32 _displayWidth;
		Int32 _displayHeight;
	};

}

#endif