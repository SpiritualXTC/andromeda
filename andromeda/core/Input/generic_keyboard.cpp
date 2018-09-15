#include "generic_keyboard.h"

using namespace andromeda;


Keyboard::Keyboard()
{
	for (Int32 i = 0; i < KEYS; ++i)
		_keys[i] = 0;
}


Keyboard::~Keyboard()
{

}


Boolean Keyboard::resume()
{
	for (Int32 i = 0; i < KEYS; ++i)
		_keys[i] = 0;

	return true;
}

Boolean Keyboard::pause()
{
	for (Int32 i = 0; i < KEYS; ++i)
		_keys[i] = 0;

	return true;
}


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


Boolean Keyboard::update()
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

	return true;
}


void Keyboard::dispatchKeyDown(Int8 keyIndex)
{
	KeyEventArgs e;
	e.key = keyIndex;

	notify(KeyEventType::KeyDown, e);
}


void Keyboard::dispatchKeyUp(Int8 keyIndex)
{
	KeyEventArgs e;
	e.key = keyIndex;

	notify(KeyEventType::KeyUp, e);
}


void Keyboard::dispatchKeyRepeat(Int8 keyIndex)
{
	KeyEventArgs e;
	e.key = keyIndex;

	notify(KeyEventType::KeyRepeat, e);
}















