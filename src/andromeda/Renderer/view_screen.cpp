#include <andromeda/Renderer/view.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;



/*

*/
ViewScreen::ViewScreen()
{

}

/*

*/
ViewScreen::~ViewScreen()
{
	
}


/*

*/
Boolean ViewScreen::onResize(ResizeEventArgs & e)
{
	_width = e.displayWidth;
	_height = e.displayHeight;

	notify(this);

	return true;
}
