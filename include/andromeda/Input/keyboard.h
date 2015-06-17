#ifndef _ANDROMEDA_INPUT_KEYBOARD_H_
#define _ANDROMEDA_INPUT_KEYBOARD_H_

#include "input.h"

namespace andromeda
{

	/*
		Data Struct for all keyboard events
	*/
	struct KeyEventArgs
	{
		Int8 key;
	};
	


	/*
		Keyboard Class
	*/
	class Keyboard : public Input<Keyboard>
	{
	private:
		static const Int32 KEYS = 256;
	public:
		enum _KeyEvent
		{
			KeyDown,
			KeyUp,
			KeyRepeat,
		};

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


		void keyDown(Int8 key);
		void keyUp(Int8 key);

		// Polling Functions
		const inline Boolean isDown(Int8 key) const { return _keys[key] & Keyboard::KeyBitState; }



		void update() override;

	protected:
		void dispatchKeyDown(Int8 keyIndex);
		void dispatchKeyUp(Int8 keyIndex);
		void dispatchKeyRepeat(Int8 keyIndex);


	private:
		Int8 _keys[KEYS];


	};
}

#endif