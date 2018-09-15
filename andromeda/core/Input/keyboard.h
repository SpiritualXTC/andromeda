#pragma once

#include <common/observer.h>

namespace andromeda
{
	// TODO: Keyboard Interface

	struct KeyEventArgs
	{
		Int8 key;
		// TODO: Add additional data to the key
		// TODO: Change to UINT8
	};

	enum KeyEventType
	{
		KeyDown,
		KeyUp,
		KeyRepeat
	};

	typedef Observable<KeyEventType, const KeyEventArgs&> KeyboardObservable;

	class KeyboardListener : public KeyboardObservable::Observer
	{
	public:
		KeyboardListener() {}
		virtual ~KeyboardListener() {}

	protected:
		virtual Boolean keyDown(const KeyEventArgs & e) = 0;
		virtual Boolean keyUp(const KeyEventArgs & e) = 0;
		virtual Boolean keyRepeat(const KeyEventArgs & e) = 0;

	private:
		void notify(KeyEventType, const KeyEventArgs&) override;
	};
}