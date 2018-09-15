#include "generic_keyboard.h"

#include <common/log.h>

using namespace andromeda;

void KeyboardListener::notify(KeyEventType type, const KeyEventArgs& args)
{
	log_debug("KEYBOARD EVENT NOTIFICATION");
	switch (type)
	{
	case KeyEventType::KeyDown:
		keyDown(args);
		break;
	case KeyEventType::KeyUp:
		keyUp(args);
		break;
	case KeyEventType::KeyRepeat:
		keyRepeat(args);
		break;
	}
}
