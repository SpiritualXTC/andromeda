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

		Black	0 = 0000	[x00]	8 = 1000	[x08]
		Blue	1 = 0001	[x01]	9 = 1001	[x09]
		Green	2 = 0010	[x02]	A = 1010	[x0A]
		Cyan	3 = 0011	[x03]	B = 1011	[x0B]
		Red		4 = 0100	[x04]	C = 1100	[x0C]
		Magenta	5 = 0101	[x05]	D = 1101	[x0D]
		Yellow	6 = 0110	[x06]	E = 1110	[x0E]	
		White	7 = 0111	[x07]	F = 1111	[x0F]
	*/

	// Make all common output streams, sync with the std streams.
	std::ios::sync_with_stdio();

	// Color Map
	_colors[andromeda::Log::Error] = 0x0C;			// B. Red
	_colors[andromeda::Log::Warning] = 0x0E;		// B. Yellow
	_colors[andromeda::Log::Information] = 0x0F;	// B. White
	_colors[andromeda::Log::Debug] = 0x0D;			// B. Magenta
	_colors[andromeda::Log::Verbose] = 0x07;		// D. White [Grey]
	_colors[andromeda::Log::Event] = 0x0A;			// B. Green
	_colors[andromeda::Log::Trace] = 0x0B;			// B. Cyan




	// Bind the Logging Event!
	_eventHandle = andromeda::bind<andromeda::LogMessage>(andromeda::Log::Message, std::bind(&Console::log, this, std::placeholders::_1));
}


/*

*/
Console::~Console()
{
	std::string msg = "Console :: <destroy>()";
	print(msg, andromeda::Log::Warning);


	andromeda::unbind<andromeda::LogMessage>(andromeda::Log::Message, _eventHandle);
}

/*

*/
aBoolean Console::log(andromeda::LogMessage & message)
{
	if (message.level == andromeda::Log::Trace)
	{
		// Dump this to file!
	//	return true;
	}
	else if (message.level == andromeda::Log::Push)
	{
		_indent.push_back(' ');

		return true;
	}
	else if (message.level == andromeda::Log::Pop)
	{
		if (!_indent.empty())
			_indent.pop_back();	

		return true;
	}
	else if (message.level == andromeda::Log::Break)
	{
		// Dump a line break
		std::string empty = "";
		print(empty, andromeda::Log::Information);
		return true;
	}

	// Change Color
	aInt16 color = _colors[message.level];
	SetConsoleTextAttribute(_stdout, color);

	// Output message
	DWORD write;
	BOOL b = TRUE;
	b &= WriteConsoleA(_stdout, _indent.c_str(), _indent.length(), &write, nullptr);
	b &= WriteConsoleA(_stdout, message.message.c_str() , message.message.length(), &write, nullptr);
	
	// Output Line break
	b &= WriteConsoleA(_stdout, "\n", 1, &write, nullptr);

	return true;
}


/*

*/
aBoolean Console::print(std::string & message, andromeda::Log::LogLevel level)
{
	// Change Color
	aInt16 color = _colors[level];
	SetConsoleTextAttribute(_stdout, color);

	// Output message
	DWORD write;
	BOOL b = WriteConsoleA(_stdout, message.c_str(), message.length(), &write, nullptr);

	// Output Line break
	WriteConsoleA(_stdout, "\n", 1, &write, nullptr);

	return true;
}