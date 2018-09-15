#include "generic_mouse.h"

using namespace andromeda;


/*

*/
Mouse::Mouse()
{
	for (Int32 i = 0; i < Mouse::BUTTONS; ++i)
		_buttons[i] = 0;
}


/*

*/
Mouse::~Mouse()
{

}



Boolean Mouse::resume()
{
	for (Int32 i = 0; i < Mouse::BUTTONS; ++i)
		_buttons[i] = 0;

	return true;
}

Boolean Mouse::pause()
{
	for (Int32 i = 0; i < Mouse::BUTTONS; ++i)
		_buttons[i] = 0;

	return true;
}


/*

*/
Boolean Mouse::update()
{
	/*
		Per/Frame Mouse Update Code Goes Here!
	*/
	return true;
}






/*

*/
void Mouse::mouseDown(Int8 button, Int32 x, Int32 y)
{
	_buttons[button] = true;

	_state |= 1 << button;

	dispatchMouseDown(button, x, y);
}

/*

*/
void Mouse::mouseUp(Int8 button, Int32 x, Int32 y)
{
	_buttons[button] = false;

	_state &= ~(1 << button);

	dispatchMouseUp(button, x, y);
}

/*

*/
void Mouse::mouseMove(Int32 x, Int32 y)
{
	// Dispatch
	dispatchMouseMove(x, y);

	// Set as Last Position
	_mouseX = x;
	_mouseY = y;
}

/*

*/
void Mouse::mouseWheel(Int32 delta)
{
	dispatchMouseWheel(delta);
}


/*

*/
void Mouse::dispatchMouseDown(Int8 button, Int32 x, Int32 y)
{
	MouseEventArgs e;
	e.buttonEvent.button = button;
	e.buttonEvent.x = x;
	e.buttonEvent.y = y;

	notify(MouseEventType::MouseDown, e);
}

/*

*/
void Mouse::dispatchMouseUp(Int8 button, Int32 x, Int32 y)
{
	MouseEventArgs e;
	e.buttonEvent.button = button;
	e.buttonEvent.x = x;
	e.buttonEvent.y = y;

	notify(MouseEventType::MouseDown, e);
}

/*

*/
void Mouse::dispatchMouseMove(Int32 x, Int32 y)
{
	MouseEventArgs e;

	e.moveEvent.state = _state;

	e.moveEvent.x = x;
	e.moveEvent.y = y;

	e.moveEvent.deltaX = x - _mouseX;
	e.moveEvent.deltaY = y - _mouseY;

	notify(MouseEventType::MouseMove, e);
}

/*

*/
void Mouse::dispatchMouseWheel(Int32 delta)
{
	MouseWheelEventArgs e;
	e.delta = delta;

//	dispatch<MouseWheelEventArgs>(Mouse::MouseWheel, e);
}





