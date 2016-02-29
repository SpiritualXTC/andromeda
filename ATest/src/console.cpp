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

	// Redirect Unbuffered StdIn to Console
	_stdin = GetStdHandle(STD_INPUT_HANDLE);

	// Redirect UnBuffered StdErr to Console
	_stderr = GetStdHandle(STD_ERROR_HANDLE);

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

	// Change Color
	aInt16 color = _colors[message.level];
	SetConsoleTextAttribute(_stdout, color);

	// Output message
	DWORD write;
	BOOL b = WriteConsoleA(_stdout, message.message.c_str() , message.message.length(), &write, nullptr);
	
	// Output Line break
	WriteConsoleA(_stdout, "\n", 1, &write, nullptr);

	return true;
}


/*

*/
aBoolean Console::print(std::string & message)
{
	// Change Color
	aInt16 color = _colors[andromeda::Log::Verbose];
	SetConsoleTextAttribute(_stdout, color);

	// Output message
	DWORD write;
	BOOL b = WriteConsoleA(_stdout, message.c_str(), message.length(), &write, nullptr);

	// Output Line break
	WriteConsoleA(_stdout, "\n", 1, &write, nullptr);

	return true;
}