#ifndef _ANDROMEDA_GAME_TRANSFORM_H_
#define _ANDROMEDA_GAME_TRANSFORM_H_

#include <andromeda/stddef.h>

#include <glm/glm.hpp>

namespace andromeda
{
	/*
	
	*/
	class ITransform
	{
	public:
		ITransform() {}
		virtual ~ITransform() {}

		//	virtual const glm::mat4 & matrix() = 0;
		virtual const glm::vec3 & position() const = 0;

		virtual const inline Float x() const = 0;
		virtual const inline Float y() const = 0;
		virtual const inline Float z() const = 0;

		virtual const inline Float pitch() const = 0;
		virtual const inline Float yaw() const = 0;
		virtual const inline Float roll() const = 0;

		// Temp
		//	virtual void sync() = 0;
	};

}

#endif
