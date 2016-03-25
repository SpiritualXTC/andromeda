#ifndef _ANDROMEDA_GAME_TRANSFORM_H_
#define _ANDROMEDA_GAME_TRANSFORM_H_

#include <andromeda/stddef.h>

#include <andromeda/glm.h>

namespace andromeda
{
	/*
	
	*/
	class ITransform
	{
	public:
		ITransform() {}
		virtual ~ITransform() {}


		/* Temporary */
		virtual void calculate() = 0;





		/* Get Matrix */
		virtual const glm::mat4 & matrix() const = 0;

		/* Get Position */
		virtual const glm::vec3 & position() const = 0;

		
		
		/* Get X-Axis Position */
		virtual const inline Float x() const = 0;

		/* Get Y-Axis Position */
		virtual const inline Float y() const = 0;

		/* Get Z-Axis Position */
		virtual const inline Float z() const = 0;

		virtual inline void x(Float x) = 0;
		virtual inline void y(Float y) = 0;
		virtual inline void z(Float z) = 0;



		

		/* Get Pitch */
		virtual const inline Float pitch() const = 0;
		
		/* Get Yaw */
		virtual const inline Float yaw() const = 0;

		/* Get Roll */
		virtual const inline Float roll() const = 0;



		virtual inline void yaw(Float f) = 0;
		virtual inline void pitch(Float f) = 0;
		virtual inline void roll(Float f) = 0;

	};

}

#endif
