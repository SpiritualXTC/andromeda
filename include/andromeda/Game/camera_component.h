#ifndef _ANDROMEDA_GAME_CAMERA_COMPONENT_H_
#define _ANDROMEDA_GAME_CAMERA_COMPONENT_H_

#include "component.h"

namespace andromeda
{
	/*
		For a later Experiment, that will allow a camera target to maintain its own camera
		idenpendantly of its transform

		Different Derived classes can work differently

		Examples: 
			FreeLook		: Includes Objects Translation, uses its own rotation													[Debug Camera]
			Static			: Uses Objects Translation and Rotation data, but has none of its own									[Survellience Camera, remote Viewing]
			Dynamic			: Uses Objects Translation and Rotation Data, and has it's own rotation data added for a final matrix.	[3rd Person]
		
		Hybrid Examples
			FPSCamera		: Includes Objects Translation and Y-Axis rotation, but has it's own Pitch								[1st Person]



		Interesting Scenerio for Split Screen....
		And GameObject that can be viewed by BOTH screens, but controlled by one while the other is remote.
			Would require seperate CameraComponents 
			
			
		.... Or the Camera modified are child classes and this just acts as a wrapper
	*/
	class CameraComponent : public Component<CameraComponent>
	{
	public:

	};
}

#endif
