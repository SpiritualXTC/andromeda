#ifndef _ANDROMEDA_INPUT_MOUSE_H_
#define _ANDROMEDA_INPUT_MOUSE_H_

#include "input.h"

namespace andromeda
{
	class Mouse : public Input<Mouse>
	{
	public:
		Mouse();
		virtual ~Mouse();


		void update() override;

	private:

	};
}

#endif