#ifndef _ANDROMEDA_PLATFORM_PLATFORM_H_
#define _ANDROMEDA_PLATFORM_PLATFORM_H_

#include <memory>
#include <set>


#include <andromeda/stddef.h>
#include <andromeda/Engine/module.h>

#include <andromeda/Utilities/observable.h>

namespace andromeda
{
	// Forward Declarations

	class System;
	struct DisplayFormat;
	struct DisplayParameters;



	class Mouse;
	class Keyboard;

	/*
	
	*/
	class Platform : public Module<Platform>, virtual public Observable<Platform>
	{
	public:
		friend class System;


	public:
		//Platform(std::weak_ptr<System> system);
		Platform();
		virtual ~Platform();




		/*
			Change Window Settings

			TODO: Rename, maybe pass screen resolution into the function as well
		*/
		virtual Boolean changeWindowSettings(const DisplayParameters & dp, const Int32 screenWidth, const Int32 screenHeight) = 0;

		/*
			Get Resolution of the only the Display Area
		*/
		virtual Boolean getClientResolution(Int32 & width, Int32 & height) const = 0;	// THIS IS NEEDED



		// TEMP
		// TODO: Require a way to retrieve a list of Input Devices
		virtual inline std::shared_ptr<Mouse> getMouse() { return nullptr; }
		virtual inline std::shared_ptr<Keyboard> getKeyboard() { return nullptr; }

	protected:
	
		/*
			Window is resized by OS, dispatches notification to observers
		*/
		void resize(Int32 width, Int32 height);


		/*
			Bootstrap Initialiser
		*/
		virtual void show() = 0;



		/*
		
		*/
		void close();

		/*
		
		*/
		void activate();

		/*
		
		*/
		void deactivate();

		
	private:
		
	};

}

typedef andromeda::Platform aPlatform;


#endif