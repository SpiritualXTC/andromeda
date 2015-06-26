#include <andromeda/Input/mouse.h>

#include <andromeda/Events/event_manager.h>

using namespace andromeda;


/*

*/
Mouse::Mouse()
{
	for (Int32 i = 0; i < Mouse::BUTTONS; ++i)
		_buttons[i] = 0;


	// Register Events
	registerEvent<MouseButtonEventArgs>(Mouse::MouseDown);
	registerEvent<MouseButtonEventArgs>(Mouse::MouseUp);
	registerEvent<MouseMoveEventArgs>(Mouse::MouseMove);
	registerEvent<MouseWheelEventArgs>(Mouse::MouseWheel);
}


/*

*/
Mouse::~Mouse()
{
	// Unregister Events
	unregisterEvent<MouseWheelEventArgs>(Mouse::MouseWheel);
	unregisterEvent<MouseMoveEventArgs>(Mouse::MouseMove);
	unregisterEvent<MouseButtonEventArgs>(Mouse::MouseUp);
	unregisterEvent<MouseButtonEventArgs>(Mouse::MouseDown);
}



/*

*/
void Mouse::onResume()
{
	for (Int32 i = 0; i < Mouse::BUTTONS; ++i)
		_buttons[i] = 0;
}



/*

*/
void Mouse::update()
{
	/*
		Per/Frame Mouse Update Code Goes Here!
	*/
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
	MouseButtonEventArgs e;
	e.button = button;
	e.x = x;
	e.y = y;

	dispatch<MouseButtonEventArgs>(Mouse::MouseDown, e);
}

/*

*/
void Mouse::dispatchMouseUp(Int8 button, Int32 x, Int32 y)
{
	MouseButtonEventArgs e;
	e.button = button;
	e.x = x;
	e.y = y;

	dispatch<MouseButtonEventArgs>(Mouse::MouseUp, e);
}

/*

*/
void Mouse::dispatchMouseMove(Int32 x, Int32 y)
{
	MouseMoveEventArgs e;

	e.state = _state;

	e.x = x;
	e.y = y;

	e.deltaX = x - _mouseX;
	e.deltaY = y - _mouseY;

	dispatch<MouseMoveEventArgs>(Mouse::MouseMove, e);
}

/*

*/
void Mouse::dispatchMouseWheel(Int32 delta)
{
	MouseWheelEventArgs e;
	e.delta = delta;

	dispatch<MouseWheelEventArgs>(Mouse::MouseWheel, e);
}





