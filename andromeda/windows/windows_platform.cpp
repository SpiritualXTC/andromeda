#include "windows_platform.h"

#include <common/log.h>
#include <core/Engine/engine.h>
#include <core/Graphics/graphics.h>
#include <core/Input/generic_keyboard.h>
#include <core/Input/generic_mouse.h>

#include <opengl/opengl.h>

#include "windows_opengl.h"

#include <windowsx.h>

using namespace andromeda;
using namespace andromeda::windows;



WindowsPlatform::WindowsPlatform(std::shared_ptr<Engine> engine)
	: IPlatform(engine)
{
	log_debug("Windows :: Platform Initialisation");

	_gui = std::make_shared<WindowsGUI>();
	_mouse = std::make_shared<Mouse>();
	_keyboard = std::make_shared<Keyboard>();

	// TODO: Allow for Vulcan Bindings, Maybe even DirectX Bindings
	_context = std::make_shared<WindowsOpenGLContext>(_gui->getHDC());
	_graphics = std::make_shared<opengl::OpenGL>();

	_gui->addObserver(this);

	engine->insert<WindowsGUI>(_gui);
	engine->insert<Keyboard>(_keyboard);
	engine->insert<Mouse>(_mouse);
}

WindowsPlatform::~WindowsPlatform()
{
	log_debug("Windows :: Platform Destruction");
}


void WindowsPlatform::notify(LRESULT& result, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		//	keyDown((Int8)wParam);
		_keyboard->keyDown((Int8)wParam);
		break;

	case WM_KEYUP:
		_keyboard->keyUp((Int8)wParam);
		break;


	case WM_MOUSEMOVE:
		_mouse->mouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_LBUTTONDOWN:
		_mouse->mouseDown(Mouse::Left, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_LBUTTONUP:
		_mouse->mouseUp(Mouse::Left, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_RBUTTONDOWN:
		_mouse->mouseDown(Mouse::Right, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_RBUTTONUP:
		_mouse->mouseUp(Mouse::Right, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_MBUTTONDOWN:
		_mouse->mouseDown(Mouse::Middle, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_MBUTTONUP:
		_mouse->mouseUp(Mouse::Middle, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_XBUTTONDOWN:
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
			_mouse->mouseDown(Mouse::XButton0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		else  if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
			_mouse->mouseDown(Mouse::XButton1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_XBUTTONUP:
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
			_mouse->mouseUp(Mouse::XButton0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		else  if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
			_mouse->mouseUp(Mouse::XButton1, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	case WM_MOUSEHWHEEL:
		_mouse->mouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
		//A_LOGD("> Mouse WHeeeeeeeeeeeeeeeeeee.......l\n");
		// Dispatch Temporary Mouse Events!
		//dispatchMouseWheelEvent(GET_WHEEL_DELTA_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	default:
		return;
	}

	result = 0L;
}
