#ifndef _ANDROMEDA_INPUT_MOUSE_H_
#define _ANDROMEDA_INPUT_MOUSE_H_

#include "input.h"

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
		Int32 delta;
	};


	/*
	
	*/
	class MouseListener
	{
	public:
		MouseListener();
		virtual ~MouseListener();

	protected:
		virtual Boolean mouseDown(MouseButtonEventArgs & e) = 0;
		virtual Boolean mouseUp(MouseButtonEventArgs & e) = 0;

		virtual Boolean mouseMove(MouseMoveEventArgs & e) = 0;
		virtual Boolean mouseWheel(MouseWheelEventArgs & e) = 0;

	private:
		Int32 _hMouseDown = -1;
		Int32 _hMouseUp = -1;
		Int32 _hMouseMove = -1;
		Int32 _hMouseWheel = -1;
	};



	/*
		The Mouse is Instantly Sending Events out. (Currently)

		This is a generic Mouse class. It doesn't interface with a Mouse device, only dispatches the events and stores states.
	*/
	class Mouse : public Input<Mouse>
	{
	private:
		static const Int32 BUTTONS = 8;

	public:
		enum _MouseButton
		{
			Left,
			Right,
			Middle,
			XButton0,
			XButton1,
		};

		enum _MouseBitButtons
		{
			LeftBit = 0x01,
			RightBit = 0x02,
			MiddleBit = 0x04,
			XButton0Bit = 0x08,
			XButton1Bit = 0x10,
		};


		enum _MouseEvent
		{
			MouseDown,
			MouseUp,
			MouseMove,
			MouseWheel,
		};

	public:
		Mouse();
		virtual ~Mouse();


		void update() override;
		void onResume() override;


		void mouseDown(Int8 button, Int32 x, Int32 y);
		void mouseUp(Int8 button, Int32 x, Int32 y);
		void mouseMove(Int32 x, Int32 y);
		void mouseWheel(Int32 delta);

	private:
		void dispatchMouseDown(Int8 button, Int32 x, Int32 y);
		void dispatchMouseUp(Int8 button, Int32 x, Int32 y);
		void dispatchMouseMove(Int32 x, Int32 y);
		void dispatchMouseWheel(Int32 delta);

		Int32 _mouseX = 0;
		Int32 _mouseY = 0;

		Int32 _buttons[BUTTONS];
		Int32 _state = 0;
	};
}

#endif