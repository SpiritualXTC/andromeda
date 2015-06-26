#ifndef _ANDROMEDA_PLATFORM_PLATFORM_H_
#define _ANDROMEDA_PLATFORM_PLATFORM_H_

#include <memory>
#include <set>


#include "../stddef.h"
#include "../Engine/module.h"


namespace andromeda
{
	// Forward Declarations
	class System;
	struct DisplayFormat;
	struct DisplayParameters;





	/*
	
	*/
	class Platform : public Module<Platform>
	{
	public:
		friend class System;


	public:
		Platform(std::weak_ptr<System> system);
		virtual ~Platform();


		/*
			Get Resolution of the Screen
		*/
		virtual Boolean getScreenResolution(Int32 & width, Int32 & height) = 0;

		/*
			Get Resolution of the only the Display Area
		*/
		virtual Boolean getClientResolution(Int32 & width, Int32 & height) = 0;

		/*
			Enumerate Displays
		*/
		virtual Boolean enumerateDisplaySettings(std::set<DisplayFormat> & displayModes) = 0;

	protected:
	
		/*
			Change Display Settings: This is called by system (friend class)
		*/
		virtual Boolean changeDisplaySettings(const DisplayParameters & dp) = 0;





		// Call Helpers: Tyically only pass to a dependant module :: These might be better being called directly from the platform implementation!
		void keyDown(Int8 key);
		void keyUp(Int8 key);

		void mouseDown(Int8 button, Int32 x, Int32 y);
		void mouseUp(Int8 button, Int32 x, Int32 y);
		void mouseMove(Int32 x, Int32 y);
		void mouseWheel(Int32 delta);



		void resize(Int32 width, Int32 height);


		/*
			Bootstrap Initialiser
		*/
		virtual void show() = 0;




		void close();
		void activate();
		void deactivate();

	//	void start();
	//	void stop();
		
	private:

	};

}

typedef andromeda::Platform aPlatform;


#endif