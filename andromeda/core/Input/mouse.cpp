#include "mouse.h"

using namespace andromeda;

void MouseListener::notify(MouseEventType type, const MouseEventArgs& args)
{
	switch (type)
	{
	case MouseEventType::MouseDown:
		mouseDown(args.buttonEvent);
		break;
	case MouseEventType::MouseUp:
		mouseUp(args.buttonEvent);
		break;
	case MouseEventType::MouseMove:
		mouseMove(args.moveEvent);
		break;
	case MouseEventType::MouseWheel:
		mouseWheel(args.wheelEvent);
		break;
	}
}