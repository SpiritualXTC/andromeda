#include "display_windows.h"


#include <Windows.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::windows;




/*
	Moniter Callback function
*/
BOOL CALLBACK MonitorEnumProc(
	_In_ HMONITOR hMonitor,
	_In_ HDC      hdcMonitor,
	_In_ LPRECT   lprcMonitor,
	_In_ LPARAM   dwData
	)
{
	log_infop("Moniter Detected: %1%, %2%, %3%, %4%", lprcMonitor->left, lprcMonitor->top, lprcMonitor->right, lprcMonitor->bottom);

	// Increase Moniter Count
	(*(Int32*)dwData)++;

	return TRUE;
}








/*

*/
DisplayWindows::DisplayWindows(const DisplayParameters & dp)
	: Display(dp)
{
	// Get Current Screen Resolution :: Need to restore Screen Resolution upon quitting or reverting back to windowed mode
	getScreenResolution(_nativeWidth, _nativeHeight);

	// Copy Display Parameters
	DisplayParameters display = dp;

	// Zero Dimensions? Set to Native
	if (display.resolution.width == 0)
		display.resolution.width = _nativeWidth;

	if (display.resolution.height == 0)
		display.resolution.height = _nativeHeight;





	// Fullscreen and BorderlessWindowed MAY need to change screen resolution
	// Windowed mode does not need to change screen resolution

	DisplayMode mode = getDisplayMode();

	// Adjust Screen Resolution?
	if (mode != DisplayMode::Windowed)
	{
		// Fullscreen
		// BorderlessWindow
		// Change Screen Resolution to displayWidth x displayHeight

		// If it fails, set DisplayMode to Windowed

		Boolean result = changeScreenResolution(dp.resolution.width, dp.resolution.height);
		if (!result)
		{
			display.mode = DisplayMode::Windowed;
		}
	}


	// Adjust Window Size
	if (mode == DisplayMode::Windowed)
	{
		// Windowed Mode.
		// Window Needs to be smaller (or Equal) to the Screen Resolution

		// Adjust Width
		if (display.resolution.width > _nativeWidth)
			display.resolution.width = _nativeWidth;
	
		// Adjust Height
		if (display.resolution.height > _nativeHeight)
			display.resolution.height = _nativeHeight;
	}




	// Changes got made!
	if (getDisplayParameters() != display)
	{
		log_warnp("Display :: Windows :: <init>() :: Changes made during Display Initialisation");
	}



	// TEMP
//	getNumDisplays();
//	enumDisplayDevices();
//	enumDisplaySettings();
}


/*

*/
DisplayWindows::~DisplayWindows()
{

}







/*
	Get Number of connected Displays
*/
Int32 DisplayWindows::getNumDisplays()
{
	Int displays = 0;


	BOOL result = EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, (LPARAM)&displays);

	log_infop("%1% Moniters Detected: ", displays);

	return displays;
}









/*
	Get Current Screen Resolution
*/
Boolean DisplayWindows::getScreenResolution(Int32 & width, Int32 & height)
{
	DEVMODE mode;
	
	BOOL result = EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);
	
	if (result)
	{
		width = mode.dmPelsWidth;
		height = mode.dmPelsHeight;

		log_infop("Display :: Windows :: Current Resolution = %1%x%2%x%3% @ %4%", mode.dmPelsWidth, mode.dmPelsHeight, mode.dmBitsPerPel, mode.dmDisplayFrequency);
	}
	else
		log_warnp("Display :: Windows :: Unable to retrieve Screen Resolution");

	return !!result;
}





/*

*/
Boolean DisplayWindows::enumDisplayDevices()
{
	Int32 i = 0;

	DISPLAY_DEVICE display;

	display.cb = sizeof(DISPLAY_DEVICE);




	while (EnumDisplayDevices(NULL, i++, &display, 0))
	{
		// Ouptut Information

		std::wstring uni(display.DeviceString);
		std::string dev(uni.begin(), uni.end());

		
		if (display.StateFlags & DISPLAY_DEVICE_ACTIVE)
			log_infop("Device [%1%] = %2% :: %3%", i, dev, display.StateFlags);

		if (display.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
			log_infop("Primary Display");
	}


	return true;
}




/*
	Get Display Settings Available
*/
std::set<DisplayFormat> DisplayWindows::enumDisplaySettings()
{
	std::set<DisplayFormat> formats;

	DEVMODE mode;

	Int32 i = 0;

	Boolean exclusive = true;
	Int32 flags = exclusive ? CDS_FULLSCREEN : 0;

	// Loop through all Display Settings
	while (EnumDisplaySettings(NULL, i++, &mode))
	{
		// Test Support
		if (ChangeDisplaySettings(&mode, flags | CDS_TEST) == DISP_CHANGE_SUCCESSFUL)
		{
			DisplayFormat format;
		
			format.width = mode.dmPelsWidth;
			format.height = mode.dmPelsHeight;
			
			//			format.bitDepth = mode.dmBitsPerPel;

			log_infop("Resolution [%1%] = %2%x%3%x%4% @ %5%", i, mode.dmPelsWidth, mode.dmPelsHeight, mode.dmBitsPerPel, mode.dmDisplayFrequency);

			// Add the Display Mode
			formats.insert(format);
		}
	}

	log_debugp("Display :: Windows :: Enumerate Display Settings. %1% Display Formats Available", formats.size());


	return std::move(formats);
}




/*

*/
Boolean DisplayWindows::restoreScreenResolution()
{
	log_debugp("Display :: Windows :: Restoring Native Resolution");
	return changeScreenResolution(_nativeWidth, _nativeHeight);
}



/*

*/
Boolean DisplayWindows::changeScreenResolution(const Int32 width, const Int32 height)
{
	log_debugp("Display :: Windows :: Change Screen Resolution %1%x%2%", width, height);


	Int32 screenWidth = 0;
	Int32 screenHeight = 0;

	
	// Get Screen Resolution
	getScreenResolution(screenWidth, screenHeight);


	// Attempting to change to resolution.... to the same resolution!
	// TODO: This may need to account for difference b/w fullscreen and non-fullscreen "exclusive"
	if (screenWidth == width && screenHeight == height)
	{
		log_warnp("Display :: Windows :: Ignoring Resolution Change. Same Resolution");
		return true;
	}




	// Change Screen Resolution!
	DEVMODE dm;

	memset(&dm, 0, sizeof(DEVMODE));
	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = width;
	dm.dmPelsHeight = height;
	dm.dmDisplayFrequency = 60;

	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;

	// Not sure if this matters or not :: This appears to make the screen resolution restoration, automatic... 
	Boolean exclusive = true;
	Int32 flags = exclusive ? CDS_FULLSCREEN : 0;

	// Test Screen Resolution
	if (ChangeDisplaySettings(&dm, flags | CDS_TEST) != DISP_CHANGE_SUCCESSFUL)
	{
		log_err("Display :: Windows :: Failed Screen Resolution Test");

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