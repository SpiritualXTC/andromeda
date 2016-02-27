#include "console.h"

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#include <andromeda/Events/event_manager.h>


#include <sstream>

/*

*/
Console::Console()
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;


	


	// Allocate the Console
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = 500;// MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);



	// Redirect Unbuffered StdOut to Console
	_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
//	int stdOutConHandle = _open_osfhandle((long)_stdout, _O_TEXT);
	FILE* fout = NULL;// _fdopen(stdOutConHandle, "w");


	DWORD write;
	BOOL b = WriteConsole(_stdout, L"chars", 5, &write, nullptr);
	if (!b)
	{
		DWORD err = GetLastError();

		std::cout << "breakpoint" << std::endl;
	}


//	setvbuf(stdout, NULL, _IONBF, 1);
//	*stdout = *fout;

	if (!SetStdHandle(STD_OUTPUT_HANDLE, stdout))
	{
		DWORD err = GetLastError();

		std::cout << "breakpoint" << std::endl;
	}
	

	// Redirect Unbuffered StdIn to Console
	_stdin = GetStdHandle(STD_INPUT_HANDLE);
	int stdInConHandle = _open_osfhandle((long)_stdin, _O_TEXT);
	FILE * fin = _fdopen(stdInConHandle, "r");
	setvbuf(stdin, NULL, _IONBF, 128);
	*stdin = *fin;

	

	// Redirect UnBuffered StdErr to Console
	_stderr = GetStdHandle(STD_ERROR_HANDLE);
	int stdErrConHandle = _open_osfhandle((long)_stderr, _O_TEXT);
	FILE * ferr = _fdopen(stdErrConHandle, "w");
	setvbuf(stderr, NULL, _IONBF, 1);
	*stderr = *ferr;


	// FAILS!
	if (_stderr == INVALID_HANDLE_VALUE
		|| _stdin == INVALID_HANDLE_VALUE
		|| _stdout == INVALID_HANDLE_VALUE)
	{
		std::cout << "breakpoint" << std::endl;
	}

	if (ferr == INVALID_HANDLE_VALUE
		|| fin == INVALID_HANDLE_VALUE
		|| fout == INVALID_HANDLE_VALUE)
	{
		std::cout << "breakpoint" << std::endl;
	}

	if (ferr == NULL
		|| fin == NULL
		|| fout == NULL)
	{
		std::cout << "breakpoint" << std::endl;
	}

	/*
		Color Chart

				DARK				BRIGHT

		Black	0 = 0000			8 = 1000
		Blue	1 = 0001			9 = 1001
		Green	2 = 0010			A = 1010
		Cyan	3 = 0011			B = 1011
		Red		4 = 0100			C = 1100
		Magenta	5 = 0101			D = 1101
		Yellow	6 = 0110			E = 1110
		White	7 = 0111			F = 1111
	*/

	// Make all common output streams, sync with the std streams.
	std::ios::sync_with_stdio();




	// Color Map
	_colors[andromeda::Log::Error] = 0x0C;
	_colors[andromeda::Log::Warning] = 0x0E;
	_colors[andromeda::Log::Information] = 0x0F;
	_colors[andromeda::Log::Debug] = 0x0D;
	_colors[andromeda::Log::Verbose] = 0x07;
	_colors[andromeda::Log::Event] = 0x0A;

	// Bind the Logging Event!
	andromeda::bind<andromeda::LogMessage>(andromeda::Log::Message, std::bind(&Console::log, this, std::placeholders::_1));
}


/*

*/
Console::~Console()
{
	
}

/*

*/
aBoolean Console::log(andromeda::LogMessage & message)
{
	if (message.level == andromeda::Log::Trace)
	{
		// Dump this to file!
		return true;
	}

	aInt16 color = _colors[message.level];

	SetConsoleTextAttribute(_stdout, color);
//	std::cout << message.message << std::endl;

	DWORD write;
	BOOL b = WriteConsoleA(_stdout, message.message.c_str() , message.message.length(), &write, nullptr);
	
	WriteConsoleA(_stdout, "\n", 1, &write, nullptr);

	return true;
}