#include <andromeda/Input/mouse.h>

#include <andromeda/Events/event_manager.h>

using namespace andromeda;


/*

*/
MouseListener::MouseListener()
{
	_hMouseDown = andromeda::bind<MouseButtonEventArgs>(Mouse::MouseDown, std::bind(&MouseListener::mouseDown, this, std::placeholders::_1));
	_hMouseUp = andromeda::bind<MouseButtonEventArgs>(Mouse::MouseUp, std::bind(&MouseListener::mouseUp, this, std::placeholders::_1));

	_hMouseMove = andromeda::bind<MouseMoveEventArgs>(Mouse::MouseMove, std::bind(&MouseListener::mouseMove, this, std::placeholders::_1));
	_hMouseWheel = andromeda::bind<MouseWheelEventArgs>(Mouse::MouseWheel, std::bind(&MouseListener::mouseWheel, this, std::placeholders::_1));
}


/*

*/
MouseListener::~MouseListener()
{
	if (_hMouseWheel != -1)
		unbind<MouseWheelEventArgs>(Mouse::MouseWheel, _hMouseWheel);

	if (_hMouseMove != -1)
		unbind<MouseMoveEventArgs>(Mouse::MouseMove, _hMouseMove);

	if (_hMouseUp != -1)
		unbind<MouseButtonEventArgs>(Mouse::MouseUp, _hMouseUp);

	if (_hMouseDown != -1)
		unbind<MouseButtonEventArgs>(Mouse::MouseDown, _hMouseDown);
}
