#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <unordered_map>

#include <Windows.h>

#include <andromeda/stddef.h>
#include <andromeda/Utilities/log.h>

class Console
{
public:
	Console();
	virtual ~Console();

	aBoolean log(andromeda::LogMessage & message);
	aBoolean print(std::string & string, andromeda::Log::LogLevel level = andromeda::Log::Verbose);

private:
	HANDLE _stdout = nullptr;
	HANDLE _stderr = nullptr;
	HANDLE _stdin = nullptr;

	andromeda::Int32 _eventHandle;


	std::string _indent;


	std::unordered_map<aInt32, aInt16> _colors;
};


#endif