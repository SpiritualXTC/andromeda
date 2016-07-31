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
	log_errp("SCREEN RESIZE BY WEIRD SPOT %1%x%2%", e.displayWidth, e.displayHeight);

	_width = e.displayWidth;
	_height = e.displayHeight;

	notify(this);

	return true;
}
