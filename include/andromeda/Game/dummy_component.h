#ifndef _ANDROMEDA_GAME_DUMMY_COMPONENT_H_
#define _ANDROMEDA_GAME_DUMMY_COMPONENT_H_

#include "component.h"

namespace andromeda
{
	class DummyComponent : public Component<DummyComponent>
	{
	public:
		DummyComponent(){}
		virtual ~DummyComponent(){}


	private:
	};
}


#endif