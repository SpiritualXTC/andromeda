#ifndef _ANDROMEDA_GAME_CAMERA_STATIC_H_
#define _ANDROMEDA_GAME_CAMERA_STATIC_H_

#include "camera.h"

namespace andromeda
{
	/*

	*/
	class CameraStatic : public CameraDefault
	{
	public:
		CameraStatic() {}
		virtual ~CameraStatic() {}


		/*
			Temporary
		*/
		void calculate() override;
	};
}

#endif
