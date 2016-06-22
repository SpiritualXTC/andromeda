#include <andromeda/Utilities/timing.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;


/*

*/
Timing::Timing()
	: Module(Module::Critical, Module::Highest) 
{

}

/*

*/
Timing::~Timing()
{

}


/*

*/
void Timing::update()
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
}