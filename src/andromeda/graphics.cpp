#include <andromeda/graphics.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;

/*

*/
Graphics::Graphics()
{

}

/*

*/
Graphics::~Graphics()
{

}

/*

*/
Boolean Graphics::onResize(ResizeEventArgs & e)
{
	log_debugp("Graphics :: onResize() :: %1%x%2%", e.displayWidth, e.displayHeight);

	// Set Display Dimensions
	_displayWidth = e.displayWidth;
	_displayHeight = e.displayHeight;

	return true;
}