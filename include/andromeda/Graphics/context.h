#ifndef _ANDROMEDA_GRAPHICS_CONTEXT_H_
#define _ANDROMEDA_GRAPHICS_CONTEXT_H_

#include <memory>

#include "../Engine/module.h"


/*
	This actually does need to be a module! it handles device recovery ><
*/

namespace andromeda
{
	class System;

	/*
		OpenGL Context Class
	*/
	class Context : public Module < Context >
	{
	public:
		friend class System;

	public:
		Context(std::weak_ptr<System> system);
		virtual ~Context();

		// IModule
		void onResume(){ }
		void onPause(){  }

		void update();

	protected:
		/*
			This is the only function that without a doubt needs to be here.
			Could be called by the update() function!
		*/
		virtual void swap() = 0;

	};
}

#endif