#ifndef _ANDROMEDA_GRAPHICS_CONTEXT_H_
#define _ANDROMEDA_GRAPHICS_CONTEXT_H_

#include <memory>

#include <andromeda/Engine/module.h>


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
		Context();
		virtual ~Context();

		// IModule
		void onResume() override { }
		void onPause() override { }
		void onStop() override { }


		void update() override;

	protected:
		/*
			This is the only function that without a doubt needs to be here.
			Could be called by the update() function!
		*/
		virtual void swap() = 0;

	};
}

typedef andromeda::Context aContext;

#endif