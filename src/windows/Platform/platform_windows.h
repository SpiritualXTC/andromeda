#ifndef _ANDROMEDA_WINDOWS_PLATFORM_PLATFORM_WINDOWS_H_
#define _ANDROMEDA_WINDOWS_PLATFORM_PLATFORM_WINDOWS_H_



#include <boost/predef.h>


// OS Restriction: Windows
#if BOOST_OS_WINDOWS
#include <string>

#define VC_EXTRALEAN
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>




#include <andromeda/stddef.h>
#include <andromeda/Platform/platform.h>



// TEMP
#include <andromeda/Utilities/log.h>

namespace andromeda
{
	class Keyboard;
	class Mouse;
	
	namespace windows
	{
		class Window;

		class PlatformWindows : public Platform
		{
		private:
			static const std::wstring WINDOW_CLASS_NAME;
			static const std::wstring WINDOW_CLASS_TITLE;

			static const aLong WINDOW_STYLE = WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
			static const aLong WINDOW_STYLE_FULLSCREEN = WS_POPUP | PlatformWindows::WINDOW_STYLE;
			static const aLong WINDOW_STYLE_WINDOWED = WS_OVERLAPPEDWINDOW | PlatformWindows::WINDOW_STYLE;

			static const aLong WINDOW_STYLEEX = WS_EX_APPWINDOW;


		public:
			PlatformWindows(HINSTANCE hInstance);
			virtual ~PlatformWindows();

			// Getters
			inline HWND getHWND() { return _hWnd; }
			inline HDC getHDC() { return _hDC; }
			inline HINSTANCE getHInstance() { return _hInstance; }


			// Window Procedure
			LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




			// IModule
			void onResume() override;
			void onPause() override;
			void onStop() override;

			void update() override;



			// Platform
			Boolean getClientResolution(Int32 & width, Int32 & height) const override;
			Boolean changeWindowSettings(const DisplayParameters & dp, const Int32 screenWidth, const Int32 screenHeight) override;

			// TEMP
			inline std::shared_ptr<Mouse> getMouse() override { return _mouse; }
			inline std::shared_ptr<Keyboard> getKeyboard() override { return _keyboard; }


		protected:
			void show();




			// Call Helpers: Tyically only pass to a dependant module
			void keyDown(Int8 key);
			void keyUp(Int8 key);

			void mouseDown(Int8 button, Int32 x, Int32 y);
			void mouseUp(Int8 button, Int32 x, Int32 y);
			void mouseMove(Int32 x, Int32 y);
			void mouseWheel(Int32 delta);


		private:
			Boolean registerWindow();

			Boolean getWindowSize(Int32 & width, Int32 & height);



			Boolean		_paused = false;

			HWND		_hWnd = nullptr;
			HDC			_hDC = nullptr;
			HINSTANCE	_hInstance = nullptr;


			// Native Resolution
			Int32 _nativeWidth = 0;
			Int32 _nativeHeight = 0;

			// Standard Input Modules
			std::shared_ptr<Mouse> _mouse;				// Generic Keyboard
			std::shared_ptr<Keyboard> _keyboard;		// Generic Mouse

			// Game Controllers

		};
	}
}




#endif	//OS Restrictions
#endif
