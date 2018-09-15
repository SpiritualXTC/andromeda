#pragma once

#include <string>

#define VC_EXTRALEAN
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>




#include <common/types.h>
#include <common/observer.h>
#include <shared/platform.h>
#include <core/Engine/module.h>

namespace andromeda
{
	class Keyboard;
	class Mouse;

	namespace windows
	{
		class Window;

		class WindowsGUI : public IModule, public Observable<LRESULT&, HWND, UINT, WPARAM, LPARAM>
		{
		private:
			static const std::wstring WINDOW_CLASS_NAME;
			static const std::wstring WINDOW_CLASS_TITLE;

			static const aLong WINDOW_STYLE = WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
			static const aLong WINDOW_STYLE_FULLSCREEN = WS_POPUP | WindowsGUI::WINDOW_STYLE;
			static const aLong WINDOW_STYLE_WINDOWED = WS_OVERLAPPEDWINDOW | WindowsGUI::WINDOW_STYLE;

			static const aLong WINDOW_STYLEEX = WS_EX_APPWINDOW;


		public:
			WindowsGUI(HINSTANCE hInstance = NULL);
			virtual ~WindowsGUI();

			// Getters
			inline HWND getHWND() { return _hWnd; }
			inline HDC getHDC() { return _hDC; }
			inline HINSTANCE getHInstance() { return _hInstance; }


			// Window Procedure
			LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



			Boolean resume() override;
			Boolean pause() override;

			Boolean open() override;
			Boolean close() override;
			Boolean update() override;



			void show();




			// Platform
			Boolean getClientResolution(Int32 & width, Int32 & height) const;
		//	Boolean changeWindowSettings(const DisplayParameters & dp, const Int32 screenWidth, const Int32 screenHeight);

			// TEMP
		//	inline std::shared_ptr<Mouse> getMouse() override { return _mouse; }
			//inline std::shared_ptr<Keyboard> getKeyboard() override { return _keyboard; }


		protected:
			




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



			void activate();
			void deactivate();
			void resize(Int32 width, Int32 height);


			Boolean		_paused = false;

			HWND		_hWnd = nullptr;
			HDC			_hDC = nullptr;
			HINSTANCE	_hInstance = nullptr;


			// Native Resolution
			Int32 _nativeWidth = 0;
			Int32 _nativeHeight = 0;

			// Standard Input Modules
		//	std::shared_ptr<Mouse> _mouse;				// Generic Keyboard
		//	std::shared_ptr<Keyboard> _keyboard;		// Generic Mouse

														// Game Controllers

		};
	}
}


