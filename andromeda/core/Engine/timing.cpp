#include "timing.h"

#include <common/log.h>

using namespace andromeda;


/*

*/
Timing::Timing()
{

}

/*

*/
Timing::~Timing()
{

}

Boolean Timing::pause()
{
	return false;
}

Boolean Timing::resume()
{
	_last = CHRONO::now();
	return true;
}

/*

*/
Boolean Timing::update()
{
	CHRONO::time_point time = CHRONO::now();

	_frametime = (time - _last).count() / (Double)CHRONO::period::den;

	_last = time;

	_frame++;
	_timing += _frametime;
	if (_timing > 1.0)
	{
		log_debugp("FPS: %1%", _frame);

		_fps = _frame;

		_frame = 0;
		_timing -= 1.0;
	}

	return true;
}