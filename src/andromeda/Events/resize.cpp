#include <andromeda/Events/resize.h>


#include <andromeda/Engine/system.h>

#include <andromeda/Events/event_manager.h>


using namespace andromeda;

/*

*/
ResizeListener::ResizeListener()
{
	_hResize = andromeda::bind<ResizeEventArgs>(System::Resize, std::bind(&ResizeListener::onResize, this, std::placeholders::_1));
}

/*

*/
ResizeListener::~ResizeListener()
{
	if (_hResize != -1)
		unbind<ResizeEventArgs>(System::Resize, _hResize);
}