#ifndef _ANDROMEDA_UTILITIES_TIMING_H_
#define _ANDROMEDA_UTILITIES_TIMING_H_

#include "../stddef.h"

#include <chrono>

#include <andromeda/Engine/module.h>


/*
	TODO:
	Decide between

	std::chrono
	and 
	boost::chrono
*/

namespace andromeda
{
	class Timing : public Module<Timing>
	{
	public:
		typedef std::chrono::high_resolution_clock CHRONO;

		Timing();
		virtual ~Timing();

		// IModule
		void onPause() override {}
		void onResume() override
		{
			_last = CHRONO::now();
		}

		void onStop() override {}


		void update() override;



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