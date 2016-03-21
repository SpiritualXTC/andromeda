#ifndef _ANDROMEDA_GAME_VIEW_COMPONENT_H_
#define _ANDROMEDA_GAME_VIEW_COMPONENT_H_




#include "component.h"

namespace andromeda
{

	/*
		A View Component Contains a Render Target
	*/
	class ViewComponent : public Component<ViewComponent>
	{
	public:
		ViewComponent() {}
		virtual ~ViewComponent() {}


	private:

	};
}

#endif
