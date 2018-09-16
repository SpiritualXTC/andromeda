#include "platform.h"

#ifdef BOOST_OS_WINDOWS
#include <windows/windows_platform.h>
#endif

using namespace andromeda;

Platform::Platform(std::shared_ptr<Engine> engine)
	: IPlatform(engine)
{
#ifdef BOOST_OS_WINDOWS
	_impl = std::make_shared<windows::WindowsPlatform>(engine);
#endif
	assert(_impl);
}

Platform::~Platform()
{

}