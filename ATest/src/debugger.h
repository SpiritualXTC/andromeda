#ifndef _DEBUGGER_H_
#define _DEBUGGER_H_

#include <unordered_map>
#include <thread>

#include <Windows.h>

#include <andromeda/stddef.h>
#include <andromeda/Utilities/log.h>
#include <andromeda/Utilities/singleton.h>

class Debugger : public andromeda::Singleton<Debugger>
{
private:
	static const std::wstring CLASS_NAME;
	static const std::wstring WINDOW_TITLE;

	static LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM);

public:
	static void CALLBACK loop(void*);
public:
	Debugger();
	virtual ~Debugger();

	aBoolean log(andromeda::LogMessage & message);


protected:


	inline const HWND getWnd() const { return _hWnd; }

	void registerClass();
	void createGUI();

private:
	
	

	
	void start();
	void stop();
	
	

	HWND _hWnd = nullptr;

	std::thread _thread;

	std::unordered_map<aInt32, aInt16> _colors;
};

#endif

