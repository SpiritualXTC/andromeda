#pragma once

#include <common/observer.h>

namespace andromeda
{

	struct MouseButtonEventArgs
	{
		Int16 button;
		Int32 x;
		Int32 y;
	};

	struct MouseMoveEventArgs
	{
		Int16 state;
		Int32 x;
		Int32 y;
		Int32 deltaX;
		Int32 deltaY;
	};

	struct MouseWheelEventArgs
	{
		Int16 delta;
	};

	union MouseEventArgs
	{
		MouseButtonEventArgs buttonEvent;
		MouseMoveEventArgs moveEvent;
		MouseWheelEventArgs wheelEvent;
	};

	enum MouseEventType
	{
		MouseDown,
		MouseUp,
		MouseMove,
		MouseWheel,
	};

	typedef Observable<MouseEventType, const MouseEventArgs&> MouseObservable;

	class MouseListener : public MouseObservable::Observer
	{
	public:
		MouseListener() {}
		virtual ~MouseListener() {}

	protected:
		virtual Boolean mouseDown(const MouseButtonEventArgs& e) = 0;
		virtual Boolean mouseUp(const MouseButtonEventArgs& e) = 0;

		virtual Boolean mouseMove(const MouseMoveEventArgs& e) = 0;
		virtual Boolean mouseWheel(const MouseWheelEventArgs& e) = 0;

	private:
		void notify(MouseEventType, const MouseEventArgs&) override;
	};
}