#ifndef _ANDROMEDA_GAME_GAME_H_
#define _ANDROMEDA_GAME_GAME_H_

/*
	This entire file is fill with testing crap!
*/

#include "../Engine/module.h"

namespace andromeda
{
	// Forward Declarations



	/*
	
	*/
	class Application : public Module<Application>
	{
	public:
		Application();
		virtual ~Application();

		void update() override;

		virtual void update(Double ft) = 0;

	private:
	
	};
}

#endif