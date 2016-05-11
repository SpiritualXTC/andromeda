#ifndef _ANDROMEDA_GAME_CAMERA_TARGET_H_
#define _ANDROMEDA_GAME_CAMERA_TARGET_H_

#include <cassert>

#include "camera_static.h"

namespace andromeda
{
	/*
	
	*/
	class CameraTarget : public CameraDefault
	{
	public:

		/*
		
		*/
		CameraTarget(const std::shared_ptr<ITransform> transform)
			: _transform(transform)
		{
			assert(_transform);
		}

		/*
		
		*/
		virtual ~CameraTarget() {}


		/*
			Temporary
		*/
		void calculate() override;

	private:
		std::shared_ptr<ITransform> _transform;
	};

}


#endif
