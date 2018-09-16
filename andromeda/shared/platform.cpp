#include "platform.h"

#include <core/Engine/engine.h>

#ifdef BOOST_OS_WINDOWS
#include <windows/windows_platform.h>
#endif

using namespace andromeda;

Platform::Platform(std::shared_ptr<Engine> engine)
	: IPlatform(engine)
{
#ifdef BOOST_OS_WINDOWS
	_impl = std::make_shared<windows::WindowsPlatform>(engine, this);
#endif
	assert(_impl);
}

Platform::~Platform()
{

}

void Platform::notifyQuit()
{
	QuitEvent qe;
	qe.cancel = false;

	notify(qe);

	if (!qe.cancel)
		getEngine()->quit();
}