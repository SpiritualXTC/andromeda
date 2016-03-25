#ifndef _ANDROMEDA_GAME_CAMERA_H_
#define _ANDROMEDA_GAME_CAMERA_H_

/*
	camera.h:

	It MIGHT be possible (and more beneficial) for Camera to extend Entity,
	and use the TransformComponent

	But for now, this will do :)
*/

#include <memory>

#include <andromeda/stddef.h>

#include <andromeda/glm.h>
#include <glm/gtc/matrix_transform.hpp>

#include "transform.h"

namespace andromeda
{
	class ITransform;

	/*
		Camera Interface
	*/
	class ICamera : public ITransform
	{
	public:
		ICamera(){}
		virtual ~ICamera(){}

		virtual const inline Float distance() const = 0;
		virtual inline void distance(Float f) = 0;

	private:

	};
}

#endif