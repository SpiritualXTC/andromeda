#pragma once

#include <andromeda/glm.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <andromeda/stddef.h>

#include <andromeda/Utilities/observable.h>

namespace andromeda
{

	/*
		TODO:
		Rename this class
	*/
	template <typename T>
	class CameraMatrix : public Observable<T>
	{
	public:
		CameraMatrix() {}
		virtual ~CameraMatrix() {}

		// Get the Matrix
		virtual const inline glm::mat4 & matrix() const = 0;


		// Update the Matrix and send Notification to observers
		virtual void update()
		{
			calculate();
			notify();
		}

	protected:
		inline void notify()
		{
			Observable<T>::notify((T*)this);
		}

		// Calculate new Matrix
		virtual void calculate() = 0;

	private:


	};

}