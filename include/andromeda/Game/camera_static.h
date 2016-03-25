#ifndef _ANDROMEDA_GAME_CAMERA_STATIC_H_
#define _ANDROMEDA_GAME_CAMERA_STATIC_H_

#include "camera.h"

namespace andromeda
{
	/*

	*/
	class CameraStatic : public ICamera
	{
	public:
		CameraStatic() {}
		virtual ~CameraStatic() {}

		const inline glm::mat4 & matrix() const { return _view; }


		/*
			Temporary
		*/
		void calculate() override;


		/*
			Position
		*/
		const inline Float x() const override { return _position.x; }
		const inline Float y() const override { return _position.y; }
		const inline Float z() const override { return _position.z; }

		void x(Float) override;
		void y(Float) override;
		void z(Float) override;



		/*
			Translate the Camera
		*/
		void translate(Float x, Float y, Float z);

		/*
			Translate the Camera
		*/
		void translate(const glm::vec3 & position);

		/*
			Rotate the Camera
		*/
		void yaw(Float) override;
		void pitch(Float) override;
		void roll(Float) override;

		const inline Float pitch() const override { return _rotation.x; }
		const inline Float yaw() const override { return _rotation.y; }
		const inline Float roll() const override { return _rotation.z; }




		/* Getters */
		const inline glm::vec3 & position() const { return _position; }
		const inline Float distance() const override { return _distance; }

		/* Setters */
		inline void position(Float x, Float y, Float z) { _position = glm::vec3(x, y, z); }
		inline void distance(Float f) override { _distance = f; }



		/*
			Is the camera currently locked?
			Locked camera cannot be adjusted by translation/rotation/zoom functions
			They still track targets and follow paths.
		*/
		const inline Boolean isLocked() { return _locked; }

		/*
			Locks the Camera
		*/
		inline void lock() { _locked = true; }

		/*
			Unlocks the Camera
		*/
		inline void unlock() { _locked = false; }

	private:
		// Locks camera movement
		Boolean _locked = false;

		Float _distance = 2.0f;
		glm::vec3 _position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 _rotation{ 0.0f };

		// View Matrix
		glm::mat4 _view;
	};
}

#endif
