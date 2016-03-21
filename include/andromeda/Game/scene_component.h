#ifndef _ANDROMEDA_GAME_SCENE_COMPONENT_H_
#define _ANDROMEDA_GAME_SCENE_COMPONENT_H_

#include "component.h"

#include <andromeda/Utilities/log.h>

namespace andromeda
{
	class View;

	/*
		Allows a game object to recieve events from a scene
	*/
	class SceneComponent : public Component<SceneComponent>
	{
	public:
		SceneComponent() { }
		virtual ~SceneComponent() {}




		/*
		Called when the game object has become active in a View
		*/
		inline void onViewActivate() override
		{
			log_info("Game Object Activated");
		}

		/*
		Called when a game object has deactivated in a View
		*/
		inline void onViewDeactivate() override
		{
			log_info("Game Object Deactivated");
		}




		/*
			Called when the game object has become active in a View
		*/
		inline void onViewActivate(View * view) override
		{
			log_info("Game Object Activated for View");
		}

		/*
			Called when a game object has deactivated in a View
		*/
		inline void onViewDeactivate(View * view) override
		{
			log_info("Game Object Deactivated for View");
		}

	private:

	};
}

#endif
