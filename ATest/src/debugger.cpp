#include "debugger.h"

#include <stdio.h>
#include <thread>

#include <andromeda/Events/event_manager.h>


const std::wstring Debugger::CLASS_NAME = L"debugger";
const std::wstring Debugger::WINDOW_TITLE = L"Andromeda: Debugger";

/*

*/
LRESULT CALLBACK Debugger::Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;

	switch (uMsg)
	{
	case WM_CREATE:
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return lResult;
}


/*

*/
Debugger::Debugger()
{



	// Create GUI
//	createGUI();


	// Color Map
	_colors[andromeda::Log::Error] = 0x0C;
	_colors[andromeda::Log::Warning] = 0x0E;
	_colors[andromeda::Log::Information] = 0x0F;
	_colors[andromeda::Log::Debug] = 0x0D;
	_colors[andromeda::Log::Verbose] = 0x07;
	_colors[andromeda::Log::Event] = 0x0A;

	// Bind the Logging Event!
	andromeda::bind<andromeda::LogMessage>(andromeda::Log::Message, std::bind(&Debugger::log, this, std::placeholders::_1));





	start();
}

/*

*/
Debugger::~Debugger()
{
	stop();

	// Release Window & Handle
	if (_hWnd)
	{
		CloseWindow(_hWnd);
		DestroyWindow(_hWnd);
	}
	_hWnd = NULL;

	// Unregister Window
	UnregisterClass(Debugger::CLASS_NAME.c_str(), NULL);
}


void Debugger::registerClass()
{
	// Register a Window
	WNDCLASSEX wdc;
	memset((void*)&wdc, 0, sizeof(WNDCLASSEX));

	wdc.cbSize = sizeof(WNDCLASSEX);
	wdc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wdc.lpfnWndProc = &Debugger::Proc;
	wdc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wdc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wdc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wdc.lpszMenuName = nullptr;
	wdc.lpszClassName = Debugger::CLASS_NAME.c_str();
	wdc.hInstance = nullptr;
	wdc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassEx(&wdc);
}


void Debugger::createGUI()
{
	registerClass();

	// Create Window

	ULONG styleEx = WS_EX_APPWINDOW;
	ULONG style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
	

	_hWnd = CreateWindowEx(styleEx, Debugger::CLASS_NAME.c_str(), Debugger::WINDOW_TITLE.c_str(),
		style, 0, 0, 1200, 600,
		nullptr, nullptr, nullptr, nullptr);

	// Validate Window
	if (!_hWnd)
	{
		return;
	}

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);


}




/*
	start():

	Start the Thread
*/
void Debugger::start()
{
	_thread = std::thread(&Debugger::loop, nullptr);	
}


/*

*/
void Debugger::stop()
{
	// Detach from parent
	_thread.detach();
}


/*
	loop():

	Message Pump
*/
void Debugger::loop(void*)
{
	MSG msg;
	msg.message = 0;

	Debugger::instance()->createGUI();

	HWND hWnd = Debugger::instance()->getWnd();

	while (msg.message != WM_QUIT)
	{
		// Minimal Loop : When application isn't in focus it can idle
		// It does still need to process things. otherwise you will never get it back!
		if (GetMessage(&msg, hWnd, 0, 0))
		{
			// Translate and dispatch message
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		break;
	}
}





/*

*/
aBoolean Debugger::log(andromeda::LogMessage & message)
{
	if (message.level == andromeda::Log::Trace)
	{
		// Dump this to file!
		return true;
	}

	aInt16 color = _colors[message.level];

//	SetConsoleTextAttribute(_stdout, color);
//	std::cout << message.message << std::endl;

	// Append message to window

	return true;
}