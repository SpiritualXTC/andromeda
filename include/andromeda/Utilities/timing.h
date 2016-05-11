#ifndef _ANDROMEDA_UTILITIES_TIMING_H_
#define _ANDROMEDA_UTILITIES_TIMING_H_

#include "../stddef.h"

#include <chrono>

#include <andromeda/Engine/module.h>
#include <andromeda/Utilities/log.h>


namespace andromeda
{
	//template <class CHRONO>
	class Timing : public Module<Timing>
	{
	public:
		typedef std::chrono::high_resolution_clock CHRONO;

		Timing() : Module(Module::Critical, Module::Highest) {}
		virtual ~Timing() {}

		// IModule
		void onPause() override {}
		void onResume() override
		{
			_last = CHRONO::now();
		}

		void onStop() override {}


		void update() override
		{
			CHRONO::time_point time = CHRONO::now();

			_frametime = (time - _last).count() / (Double)CHRONO::period::den;

			_last = time;

			_frame++;
			_timing += _frametime;
			if (_timing > 1.0)
			{
				log_debug("FPS:", _frame);

				_fps = _frame;

				_frame = 0;
				_timing -= 1.0;
			}
		}



		const inline Int32 fps() const { return _fps; }
		const inline Double frametime() const { return _frametime; }

	private:
		Int32 _fps = 0;
		Double _frametime = 0.0;


		Int32 _frame = 0;
		Double _timing = 0.0;

		CHRONO::time_point _last;

	};






}

#endif