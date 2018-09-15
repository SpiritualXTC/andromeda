#pragma once

#include <core/Engine/module.h>

#include "keyboard.h"

namespace andromeda
{
	/*
		TODO:
		Different Types of Keyboard Structures

		Indirect vs Direct vs Polling
			- Indirect dispatches the event during the next update cycle
			- Direct dispatches the event as soon as the OS sends it
			- Polling works with both, but requires access to the keybord object
	*/


	/*
		Keyboard Class

		The Keyboard is holding onto the events until it's loop.

		This is a generic Keyboard class. It doesn't interface with a keyboard device, only dispatches the events and stores states.
	*/
	class Keyboard : public IModule, public KeyboardObservable
	{
	private:
		static const Int32 KEYS = 256;
	public:

		enum _KeyState
		{
			KeyBitState = 0x01,		/* Bit position of the keys state */

			KeyBitDown = 0x10,		/* Bit position for KeyDown Event */
			KeyBitUp = 0x20,		/* Bit position for KeyUp Event */
			KeyBitRepeat = 0x40,	/* Bit position for KeyRepeat Event (Also sent with KeyDown) */


			KeyStateMask = 0x0F,	/* Mask defining the current state */
			KeyEventMask = 0xF0,	/* Mask defining events for the key */
		};

	public:
		Keyboard();
		virtual ~Keyboard();

		// IModule
		Boolean open() override { return true; }
		Boolean close() override { return true; }
		Boolean resume() override;
		Boolean pause() override;
		Boolean update() override;
		
		

		void keyDown(Int8 key);
		void keyUp(Int8 key);

		// Polling Functions
		const inline Boolean isDown(Int8 key) const { return _keys[key] & Keyboard::KeyBitState; }

	private:
		void dispatchKeyDown(Int8 keyIndex);
		void dispatchKeyUp(Int8 keyIndex);
		void dispatchKeyRepeat(Int8 keyIndex);

		Int8 _keys[KEYS];
	};
}
