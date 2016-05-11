#ifndef _ANDROMEDA_RENDERER_CAMERA_BUILDER_H_
#define _ANDROMEDA_RENDERER_CAMERA_BUILDER_H_

#include <memory>

#include <andromeda/stddef.h>

namespace andromeda
{
	class ICamera;

	class GameObject;

	/*
		Create Camera Classes via a simple Helper.

		This is a BASIC AS FUCK builder for now, howeever should camera's become a lot more dynamic, this will come in handy.
		At the very least it, pulls code/headers from the View class and puts them here
	*/
	class CameraBuilder
	{
	public:
		CameraBuilder(){}
		virtual ~CameraBuilder() {}


		/*
			Creates a default Camera
		*/
		std::shared_ptr<ICamera> create();

		/*
			Creates a Targeting Camera
		*/
		std::shared_ptr<ICamera> create(const std::shared_ptr<GameObject> go);

	};

}

#endif
