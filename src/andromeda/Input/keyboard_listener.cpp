#include <andromeda/Input/keyboard.h>

#include <andromeda/Events/event_manager.h>

using namespace andromeda;


/*

*/
KeyboardListener::KeyboardListener()
{
	_hKeyDown = andromeda::bind<KeyEventArgs>(Keyboard::KeyDown, std::bind(&KeyboardListener::keyDown, this, std::placeholders::_1));
	_hKeyUp = andromeda::bind<KeyEventArgs>(Keyboard::KeyUp, std::bind(&KeyboardListener::keyUp, this, std::placeholders::_1));
	_hKeyRepeat = andromeda::bind<KeyEventArgs>(Keyboard::KeyRepeat, std::bind(&KeyboardListener::keyRepeat, this, std::placeholders::_1));
}

/*

*/
KeyboardListener::~KeyboardListener()
{
	if (_hKeyRepeat != -1)
		unbind<KeyEventArgs>(Keyboard::KeyRepeat, _hKeyRepeat);

	if (_hKeyUp != -1)
		unbind<KeyEventArgs>(Keyboard::KeyUp, _hKeyUp);

	if (_hKeyDown != -1)
		unbind<KeyEventArgs>(Keyboard::KeyDown, _hKeyDown);
}
