#pragma once

#include <core/Engine/module.h>

#include "mouse.h"

/*
	TODO:
		Mouse can be absolute or relative
*/

namespace andromeda
{



	/*
		The Mouse is Instantly Sending Events out. (Currently)

		This is a generic Mouse class. It doesn't interface with a Mouse device, only dispatches the events and stores states.
	*/
	class Mouse : public IModule, public MouseObservable
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

#if 0
		enum _MouseEvent
		{
			MouseDown,
			MouseUp,
			MouseMove,
			MouseWheel,
		};
#endif


	public:
		Mouse();
		virtual ~Mouse();



		// IModule
		Boolean open() override { return true; }
		Boolean close() override { return true; }
		Boolean resume() override;
		Boolean pause() override;
		Boolean update() override;


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
