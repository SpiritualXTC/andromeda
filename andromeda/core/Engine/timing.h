#pragma once

#include <chrono>


#include <common/types.h>
#include "module.h"


/*
	TODO:
	Decide between

	std::chrono
	and 
	boost::chrono

	or use PIMPLE
*/

namespace andromeda
{
	class Timing : public IModule
	{
	public:
		typedef std::chrono::high_resolution_clock CHRONO;

		Timing();
		virtual ~Timing();

		// IModule
		Boolean pause() override;
		Boolean resume() override;


		Boolean open() override { return true; }
		Boolean close() override { return true; }

		Boolean update() override;



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
