#include <andromeda/Input/keyboard.h>

#include <andromeda/Events/event_manager.h>

using namespace andromeda;

/*

*/
Keyboard::Keyboard()
{
	for (Int32 i = 0; i < KEYS; ++i)
		_keys[i] = 0;

	// Register Events
	registerEvent<KeyEventArgs>(Keyboard::KeyDown);
	registerEvent<KeyEventArgs>(Keyboard::KeyUp);
	registerEvent<KeyEventArgs>(Keyboard::KeyRepeat);

}


/*

*/
Keyboard::~Keyboard()
{

	// Unregister Events
	unregisterEvent<KeyEventArgs>(Keyboard::KeyRepeat);
	unregisterEvent<KeyEventArgs>(Keyboard::KeyUp);
	unregisterEvent<KeyEventArgs>(Keyboard::KeyDown);
}



/*

*/
void Keyboard::keyDown(Int8 key)
{
	// Reference to Key
	Int8 & k = _keys[key];

	
	if (k & Keyboard::KeyStateMask)
	{
		// Key is already down.
		// OS may fire repeated keydown events.
		// Keep it down. 
		// Set Repeat Event Flag.
		k = Keyboard::KeyBitState | Keyboard::KeyBitRepeat;
	}
	else
	{
		// Key is not down.
		// Set it to down. 
		// Set Press Event Bit. 
		// Set Repeat Event Bit.
		k = Keyboard::KeyBitState | Keyboard::KeyBitDown | Keyboard::KeyBitRepeat;
	}
}


/*

*/
void Keyboard::keyUp(Int8 key)
{
	Int8 & k = _keys[key];

	if (k & Keyboard::KeyStateMask)
	{
		// This should only be fired once, but doesn't hurt to do the check. 
		// Afterall. The key SHOULD be done for this event to be fired.
		// This will also prevent those cases were this application didn't have focus at the time of the key press

		k = Keyboard::KeyBitUp;
	}
}



/*

*/
void Keyboard::update()
{

	// Parse Keyboard Data. Execute Listeners

	for (Int32 i = 0; i < KEYS; ++i)
	{
		Int8 & k = _keys[i];

		// No event bits, are set... nothing needs to be done :)
		if (k & Keyboard::KeyEventMask)
		{
			// Keydown
			if (k & Keyboard::KeyBitDown)
				dispatchKeyDown(i);

			// Keyup
			if (k & Keyboard::KeyBitUp)
				dispatchKeyUp(i);

			// KeyRepeat
			if (k & Keyboard::KeyBitRepeat)
				dispatchKeyRepeat(i);

			// Strip Event Bits
			k &= (~Keyboard::KeyEventMask);
		}
	}

}



/*

*/
void Keyboard::dispatchKeyDown(Int8 keyIndex)
{
	KeyEventArgs e;
	e.key = keyIndex;

	dispatch<KeyEventArgs>(Keyboard::KeyDown, e);
}

/*

*/
void Keyboard::dispatchKeyUp(Int8 keyIndex)
{
	KeyEventArgs e;
	e.key = keyIndex;

	dispatch<KeyEventArgs>(Keyboard::KeyUp, e);
}

/*

*/
void Keyboard::dispatchKeyRepeat(Int8 keyIndex)
{
	KeyEventArgs e;
	e.key = keyIndex;

	dispatch<KeyEventArgs>(Keyboard::KeyRepeat, e);
}















