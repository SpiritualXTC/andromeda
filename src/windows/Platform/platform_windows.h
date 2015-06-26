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

namespace andromeda
{
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
		PlatformWindows(std::weak_ptr<System> system, HINSTANCE hInstance);
		virtual ~PlatformWindows();

		// Getters
		inline HWND getHWND() { return _hWnd; }
		inline HDC getHDC() { return _hDC; }
		inline HINSTANCE getHInstance() { return _hInstance; }


		// Window Procedure
		LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


		
		// Platform
		Boolean getScreenResolution(Int32 & width, Int32 & height) override;
		Boolean getClientResolution(Int32 & width, Int32 & height) override;

		Boolean enumerateDisplaySettings(std::set<DisplayFormat> & displayModes) override;

		

		// IModule
		void onResume() override;
		void onPause() override;
		void update() override;

	protected:
		
		Boolean changeDisplaySettings(const DisplayParameters & dp) override;

		void show();

	
	private:
		Boolean changeDisplaySettingWindows(const DisplayFormat & df);
		Boolean changeDisplaySettingBorderless(const DisplayFormat & df);
		Boolean changeDisplaySettingFullscreen(const DisplayFormat & df);

		Boolean getWindowSize(Int32 & width, Int32 & height);


		Boolean changeScreenResolution(const Int32 width, const Int32 height);

		Boolean restoreScreenResolution();



		Boolean		_paused = false;

		HWND		_hWnd = nullptr;
		HDC			_hDC = nullptr;
		HINSTANCE	_hInstance = nullptr;


		// Native Resolution
		Int32 _nativeWidth = 0;
		Int32 _nativeHeight = 0;
	};
}




#endif	//OS Restrictions
#endif
