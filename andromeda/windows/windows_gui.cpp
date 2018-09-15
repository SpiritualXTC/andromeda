#include "windows_gui.h"

using namespace andromeda;
using namespace andromeda::windows;



#include <windowsx.h>

//#include <andromeda/Input/keyboard.h>
//#include <andromeda/Input/mouse.h>


#include <common/log.h>

#include "core/Engine/display.h"



// Pass the function straight back into the Platform class
LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	WindowsGUI * p = static_cast<WindowsGUI*>((void*)ptr);
	return p == nullptr ? DefWindowProc(hWnd, uMsg, wParam, lParam) : p->WndProc(hWnd, uMsg, wParam, lParam);
}





const std::wstring WindowsGUI::WINDOW_CLASS_NAME = L"andromeda";
const std::wstring WindowsGUI::WINDOW_CLASS_TITLE = L"andromeda";






/*

*/
WindowsGUI::WindowsGUI(HINSTANCE hInstance)
	: _hInstance(hInstance)
{
	// TODO: Add Exceptions!

	log_debugp("Windows :: Initialise GUI");

	// Register the Window
	registerWindow();

	// Get NATIVE Screen Resolution: Used for restoring the resolution back upon quitting :)
	//	getScreenResolution(_nativeWidth, _nativeHeight);


	// Window Mode
	DisplayMode mode = DisplayMode::Windowed;// sys->displayMode();

											 // Screen Width / Height
	Int32 width = 1600;// sys->displayWidth();
	Int32 height = 1200;// sys->displayHeight();

	// Create Window
	DWORD style = (mode == DisplayMode::Windowed) ? WindowsGUI::WINDOW_STYLE_WINDOWED : WindowsGUI::WINDOW_STYLE_FULLSCREEN;
	DWORD styleEx = WS_EX_APPWINDOW;

	_hWnd = CreateWindowEx(WindowsGUI::WINDOW_STYLEEX, WindowsGUI::WINDOW_CLASS_NAME.c_str(), WindowsGUI::WINDOW_CLASS_TITLE.c_str(),
		style, 0, 0, width, height,
		NULL, NULL, _hInstance, NULL);

	// Set User Data of the window to reference back to this class
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	// Get Device Context
	_hDC = GetDC(_hWnd);
	if (!_hDC)
	{
		log_err("No Device Context");
	}
}

/*

*/
WindowsGUI::~WindowsGUI()
{
	close();

	// Unregister Window
	UnregisterClass(WindowsGUI::WINDOW_CLASS_NAME.c_str(), NULL);
}


/*
registerWindow():

Registers the Window Class
*/
Boolean WindowsGUI::registerWindow()
{
	// Register Window
	WNDCLASSEX wdc;
	memset((void*)&wdc, 0, sizeof(WNDCLASSEX));

	wdc.cbSize = sizeof(WNDCLASSEX);
	wdc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wdc.lpfnWndProc = _WndProc;
	wdc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wdc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wdc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wdc.lpszMenuName = NULL;
	wdc.lpszClassName = WindowsGUI::WINDOW_CLASS_NAME.c_str();
	wdc.hInstance = _hInstance;
	wdc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wdc);

	return true;
}





Boolean WindowsGUI::open()
{
	// Flag indicating the display parameters were invalid, 
	// And that the system should be notified of the update.
	// (Happens at the end of the constructor)
	Boolean reconfigure = false;


	log_warnp("Display Parameters need to be passed into the Platform Initialisation");




						// Create Mouse and Keyboard
						//_mouse = std::make_shared<Mouse>();
						//_keyboard = std::make_shared<Keyboard>();


						// Needs to be reactive, depending on whether its fullscreen/borderless/windowed.
						// Fullscreen will need to call changeScreenResolution. for example!

#if 0
	if (mode != DisplayMode::Windowed)
	{
		// Check if its a supported resolution!
		// It is entirely possible that an invalid resolution has been passed in. [Invalid Configuration Data, etc]

		// If it is invalid.... or it fails...
		// Change the internal display mode here to windowed

		Boolean result = true; //changeDisplaySettings();


							   // Failed to changeDisplaySettings. Resorting to Windowed Mode.
		if (!result)
		{
			log_err("Unable to change display settings. Resorting to Windowed Mode");

			mode = DisplayMode::Windowed;
			reconfigure = true;
		}
	}
#endif

	/*
	Validate Windowed Mode.
	*/
//	if (mode == DisplayMode::Windowed)
	{
#if 0
		// Window can't be bigger than the screen resolution :)
		Int32 scrWidth = 0;
		Int32 scrHeight = 0;

		//		getScreenResolution(scrWidth, scrHeight);

		if (width > scrWidth)
		{
			width = scrWidth;
			reconfigure = true;
		}
		if (height > scrHeight)
		{
			height = scrHeight;
			reconfigure = true;
		}
#endif
	}





	// System Reconfigure - Something Broked. Alter the settings to make it good again
	if (reconfigure)
	{
		log_warn("System Display Settings need to be adjusted :: Unable to adjust");
		//sys->changeDisplaySettings(width, height, mode);
	}

	return true;
}

void WindowsGUI::activate()
{
	// Message needs to be sent all the way down to the engine :: Resume does NOT happen here
	_paused = false;
}

void WindowsGUI::deactivate()
{
	// Message needs to be sent all the way down to the engine :: Pause does NOT happen here
	_paused = true;
}

Boolean WindowsGUI::resume()
{
	_paused = false;
	show();
	return true;
}

Boolean WindowsGUI::pause()
{
	_paused = true;
	return true;
}

Boolean WindowsGUI::close()
{
	// Release Window & Handle
	if (_hWnd)
	{
		if (_hDC)
			ReleaseDC(_hWnd, _hDC);
		_hDC = NULL;

		CloseWindow(_hWnd);
		DestroyWindow(_hWnd);
	}
	_hWnd = NULL;

	// Restore Original Screen Resolution
	//	restoreScreenResolution();
	log_verbose("Windows Platform Destroyed");

	return true;
}

Boolean WindowsGUI::update()
{
	MSG msg;

	if (!_paused)
	{
		// Iterate though messages : Can I Haz Moar Hertz?
		while (PeekMessage(&msg, _hWnd, 0, 0, PM_REMOVE))
		{
			// Could Pre-Process Keyboard Events here, and not have them dispatched
			// Worry about it later :)
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{
		// Minimal Loop : When application isn't in focus it can idle
		// It does still need to process things. Otherwise you will never get it back!
		if (GetMessage(&msg, _hWnd, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return true;
}



#if 0
// Gets the Current Screen Resolution
Boolean PlatformWindows::getScreenResolution(Int32 & width, Int32 & height) const
{
	// Nearest Moniter
	HMONITOR monitor = MonitorFromWindow(_hWnd, MONITOR_DEFAULTTOPRIMARY);

	// Get Moniter Info
	MONITORINFO info;
	info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);

	// Set Dimensions
	width = info.rcMonitor.right - info.rcMonitor.left;
	height = info.rcMonitor.bottom - info.rcMonitor.top;

	return true;
}
#endif


/*
	Gets the Clients' Display Resolution [The resolution of the active display area]

	This should be the same if fullscreen/borderless as the screen resolution.
	Currently it is just pulling the client area of the window.
*/
Boolean WindowsGUI::getClientResolution(Int32 & width, Int32 & height) const
{
	assert(_hWnd);

	RECT r;

	GetClientRect(_hWnd, &r);

	width = (r.right - r.left);
	height = (r.bottom - r.top);

	return true;
}


// Get Size of the Window
Boolean WindowsGUI::getWindowSize(Int32 & width, Int32 & height)
{
	RECT r;
	GetWindowRect(_hWnd, &r);

	width = r.right - r.left;
	height = r.bottom - r.top;

	return true;
}




/*
Boolean WindowsGUI::changeWindowSettings(const DisplayParameters & dp, const Int32 screenWidth, const Int32 screenHeight)
{
	// This may also need to update the STYLE of a window
	// If switching from Windowed to FullScreen or Borderless


	// Update Window Style
	DWORD style = (dp.mode == DisplayMode::Windowed) ? WindowsGUI::WINDOW_STYLE_WINDOWED : WindowsGUI::WINDOW_STYLE_FULLSCREEN;
	SetWindowLong(_hWnd, GWL_STYLE, style);

	// Update Window Size/Position
	Int32 px = 0, py = 0;
	Int32 pw = 0, ph = 0;

	aInt32 flags = SWP_SHOWWINDOW | SWP_FRAMECHANGED;

	if (dp.mode != DisplayMode::Windowed)
	{
		pw = screenWidth;
		ph = screenHeight;
	}
	else
	{
		// Adjust Window Position [Leave as is for now]
		// TODO: Center Window

	}

	// Update Window
	SetWindowPos(_hWnd, HWND_TOP, px, py, dp.resolution.width, dp.resolution.height, flags);

	return false;
}
*/


#if 0
/*
Change Display Settings

This function gets called when the display settings need to be changed!
- Windowed MAY need to adjust the window size!
- Fullscreen & Borderless Windowed Mode Need to change native resolution
*/
Boolean PlatformWindows::changeDisplaySettings(const DisplayParameters & dp)
{
	// This may also need to update the STYLE of a window
	// If switching from Windowed to FullScreen or Borderless


	// Windowed Mode.
	if (dp.mode == DisplayMode::Windowed)
	{
		return changeDisplaySettingWindows(dp.resolution);
	}

	// Borderless Mode
	if (dp.mode == DisplayMode::Borderless)
	{
		return changeDisplaySettingBorderless(dp.resolution);
	}

#if 0
	// FullScreen Mode
	if (dp.mode == DisplayMode::Fullscreen)
	{
		// Change Native Screen Resolution
		return changeDisplaySettingFullscreen(dp.resolution);
	}
#endif

	return false;
}


/*

*/
Boolean PlatformWindows::changeDisplaySettingWindows(const DisplayFormat & df)
{
	Int32 winWidth = 0;
	Int32 winHeight = 0;

	getWindowSize(winWidth, winHeight);

	// When going to windowed mode, restore the native screen resolution 
	restoreScreenResolution();

	Int32 px = 0;
	Int32 py = 0;

	// Update Window Style
	aLong style = PlatformWindows::WINDOW_STYLE_WINDOWED;
	SetWindowLong(_hWnd, GWL_STYLE, style);

	aInt32 flags = SWP_SHOWWINDOW | SWP_FRAMECHANGED;

	// Different Window Size
	if (winWidth != df.width || winHeight != df.height)
	{
		Int32 scrWidth = 0;
		Int32 scrHeight = 0;

		// Get Current Screen Res
		getScreenResolution(scrWidth, scrHeight);

		// Center Window
		px = (scrWidth - df.width) / 2;
		py = (scrHeight - df.height) / 2;
	}
	else // Ignore Sizing
	{
		flags |= SWP_NOMOVE | SWP_NOSIZE;
	}
	// This function will cause the WM_WINDOWPOSCHANGED notification
	// to fire. Which in turn will call, resize(), and changeDisplaySettings() again!
	// Dimension check above *should* prevent an infinite loop... but it's still calling the function twice!
	// There needs to be some logic for the notification to stop it from recalling resize().

	// Currently.... the notification is NOT being handled by WM_WINDOWPOSCHANGED.
	// It is being handled by WM_SIZING & WM_EXITSIZEMOVE, which have their own share of issues!
	SetWindowPos(_hWnd, HWND_TOP, px, py, df.width, df.height, flags);

	return true;
}

/*

*/
Boolean PlatformWindows::changeDisplaySettingBorderless(const DisplayFormat & df)
{
	// Change Native Screen Resolution
	if (!changeScreenResolution(df.width, df.height))
		return false;

	// Adjust the window size
	log_debug("Adjust Window Size:", df.width, df.height);

	// Change window style to Borderless
	aLong style = PlatformWindows::WINDOW_STYLE_FULLSCREEN;
	SetWindowLong(_hWnd, GWL_STYLE, style);

	// Set Window Position
	SetWindowPos(_hWnd, HWND_TOP, 0, 0, df.width, df.height, SWP_FRAMECHANGED | SWP_SHOWWINDOW);

	return true;
}

/*

*/
Boolean PlatformWindows::changeDisplaySettingFullscreen(const DisplayFormat & df)
{
	// Fullscreen mode not supported.
	// May not be a difference b/w Fullscreen & Borderless in OpenGL
	return true;
}




/*
changeScreenResolution():

Change Native Screen Resolution.
Might add support for BPP changes, but for now assuming 32bit support is fairly safe...
Not like its going to be running on a Win95 box or anything (I Hope)
*/
Boolean PlatformWindows::changeScreenResolution(const Int32 width, const Int32 height)
{
	Int32 screenWidth = 0;
	Int32 screenHeight = 0;

	// Attempting to change to resolution.... to the same resolution!
	getScreenResolution(screenWidth, screenHeight);

	if (screenWidth == width && screenHeight == height)
	{
		log_warn("Change Screen Resolution. Same Resolution");
		return true;
	}

	// Change Screen Resolution!
	DEVMODE dm;

	memset(&dm, 0, sizeof(DEVMODE));
	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = width;
	dm.dmPelsHeight = height;
	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;


	// Not sure if this matters or not :P
	Boolean exclusive = false;
	Int32 flags = exclusive ? CDS_FULLSCREEN : 0;

	// Test Screen Resolution
	if (ChangeDisplaySettings(&dm, flags | CDS_TEST) != DISP_CHANGE_SUCCESSFUL)
	{
		log_err("Failed Screen Resolution Test");

		return false;
	}

	// Change Screen Resolution
	if (ChangeDisplaySettings(&dm, flags) != DISP_CHANGE_SUCCESSFUL)
	{
		log_err("Failed Changing Screen Resolution");

		return false;
	}

	return true;
}


/*
Restore Original Screen Resolution
*/
Boolean PlatformWindows::restoreScreenResolution()
{
	Int32 width = 0;
	Int32 height = 0;

	// Get Current Screen Resolution
	if (!getScreenResolution(width, height))
		return false;

	// Is it currently the same as the original resolution ?
	if (width == _nativeWidth && height == _nativeHeight)
		return false;

	log_debug("Restoring Screen Resolution");

	// Restore Screen Resolution
	return changeScreenResolution(_nativeWidth, _nativeHeight);;
}

#endif


/*

*/
void WindowsGUI::show()
{
	// Show Window
	//| SW_SHOWNOACTIVATE
	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);

}





/*

*/
void WindowsGUI::keyDown(Int8 key)
{
//	if (_keyboard)
	//	_keyboard->keyDown(key);
}

/*

*/
void WindowsGUI::keyUp(Int8 key)
{
//	if (_keyboard)
	//	_keyboard->keyUp(key);
}

/*

*/
void WindowsGUI::mouseDown(Int8 button, Int32 x, Int32 y)
{
//	if (_mouse)
	//	_mouse->mouseDown(button, x, y);
}

/*

*/
void WindowsGUI::mouseUp(Int8 button, Int32 x, Int32 y)
{
//	if (_mouse)
	//	_mouse->mouseUp(button, x, y);
}

/*

*/
void WindowsGUI::mouseMove(Int32 x, Int32 y)
{
//	if (_mouse)
	//	_mouse->mouseMove(x, y);
}

/*

*/
void WindowsGUI::mouseWheel(Int32 delta)
{
//	if (_mouse)
	//	_mouse->mouseWheel(delta);
}

void WindowsGUI::resize(Int32 width, Int32 height)
{

}



/*
Window Procedure.

Seriously. Need a cleaner way of writing this horrible function :P
*/
LRESULT WindowsGUI::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = -1;


	notify(result, hWnd, uMsg, wParam, lParam);



	/*
	Might be cleaner to setup a map.

	WM_ACTION <-> Callback
	*/
	switch (uMsg)
	{
		/*
		OS Actions.
		Window Activity.
		*/
	case WM_CREATE:
		/* This will never be received! - Creation happens before the class pointer is assigned to the window */
		log_debug("Windows Event = WM_CREATE");
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		log_debug("Windows Event = WM_DESTROY");
		break;

		//case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
		if (LOWORD(wParam))
		{
			// Activate
			log_debug("Windows Event = WM_ACTIVATEAPP (true)");
			activate();
		}
		else
		{
			// Deactivate
			log_debug("Windows Event = WM_ACTIVATEAPP (false)");
			deactivate();
		}
		break;

	case WM_CLOSE:
		log_debug("Windows Event = WM_CLOSE");
		close();
		break;

	case WM_SETFOCUS:
		log_debug("Windows Event = WM_SETFOCUS");

		break;

	case WM_KILLFOCUS:
		log_debug("Windows Event = WM_KILLFOCUS");

		break;

	case WM_SIZE:
	{
		// This is fired during Minimum/Maximum style events!
		log_debug("Windows Event = WM_SIZE");
		break;
	}

	case WM_SIZING:
	{
		// This is fired, when the user is resizing the window.
		// However it is called, before the window size is recalcuated.
		// Therefore the rectangle dimensions passed through, as parameters are unreliable to use.
		// Causes a size mismatch, when Platform::changeDisplaySettings(...) gets called
		// as it scans the current window size to determine if its the same... if it isn't, it resizes the window.

		// HACK:
		// Currently grabbing the last dimensions for the window and using those to call resize.
		// Cake and eat it too... even though the cake is technically a teeny bit stale :P


		// Retrieve the DRAG Rectangle. Do NOT remove the following line
		// The DRAG Rectangle is slightly different to the Window Dimensions, retrieved below.
		//RECT * lp = (RECT*)lParam;

		// Get the dimensions of the window, in it's last calculated position
		Int32 winWidth = 0;
		Int32 winHeight = 0;

		getWindowSize(winWidth, winHeight);

		// Resize.
		resize(winWidth, winHeight);

		// Set Result
		result = TRUE;
		break;
	}

	case WM_EXITSIZEMOVE:
	{
		// This is being used in conjuction with WM_SIZING
		// However it is only called at the very end, and WM_SIZING has a hack to make it work for now
		log_debug("Windows Event = WM_EXITSIZEMOVE");
		Int32 winWidth = 0;
		Int32 winHeight = 0;

		getWindowSize(winWidth, winHeight);

		resize(winWidth, winHeight);
		break;
	}

	case WM_WINDOWPOSCHANGED:
	{
		// This event is fired twice ?

		log_debug("Windows Event = WM_WINDOWPOSCHANGED");

		// This is being used in conjuction with WM_SIZING
		// However it is only called at the very end, and WM_SIZING has a hack to make it work for now
		Int32 winWidth = 0;
		Int32 winHeight = 0;

		getWindowSize(winWidth, winHeight);

		resize(winWidth, winHeight);
		break;
	}

	case WM_WINDOWPOSCHANGING:

		// This event is fired twice ?

		log_debug("Windows Event = WM_WINDOWPOSCHANGING");
		break;

		/* Default Actions */
	default:
		if (result == -1)
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}


	return result;
}