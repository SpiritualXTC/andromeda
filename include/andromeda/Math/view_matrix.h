#pragma once

#include "camera_matrix.h"

namespace andromeda
{


	/*

	*/
	class IViewMatrix : public CameraMatrix<IViewMatrix>
	{
	public:


	private:

	};



	/*

	*/
	class ViewMatrix : public IViewMatrix
	{
	public:
		enum _LockFlags
		{
			Unlock = 0x00,

			TranslateX = 0x0001,
			TranslateY = 0x0002,
			TranslateZ = 0x0004,
			Translation = 0x000F,

			RotatePitch = 0x0010,
			RotateYaw = 0x0020,
			RotateRoll = 0x0040,
			Rotation = 0x00F0,

			Distance = 0x0100,

			Lock = 0xFFFF,
		};

	public:
		ViewMatrix() {}
		virtual ~ViewMatrix() {}

		// Get the Matrix
		const inline glm::mat4 & matrix() const override { return _view; }


		/*
		Position
		*/
		inline Float x() const { return _position.x; }
		inline Float y() const { return _position.y; }
		inline Float z() const { return _position.z; }

		const inline glm::vec3 & position() const { return _position; }

		/*
		Rotation
		*/
		inline Float pitch() const { return _rotation.x; }
		inline Float yaw() const { return _rotation.y; }
		inline Float roll() const { return _rotation.z; }

		/*
		Distance
		*/
		inline Float distance() const { return _distance; }

		/*
		Is any part of the camera locked ??
		*/
		inline Boolean isLocked() const { return _lockFlags != Unlock; }

		/*
		Is any of the Specified Flags Locked ??
		*/
		inline Boolean isLocked(UInt32 flags) const { return (_lockFlags & flags) != Unlock; }




		/*
		Set Position
		*/
		inline ViewMatrix & x(Float f)
		{
			if (!isLocked(TranslateX))
				_position.x = f;

			return *this;
		}

		inline ViewMatrix & y(Float f)
		{
			if (!isLocked(TranslateY))
				_position.y = f;

			return *this;
		}
		inline ViewMatrix & z(Float f)
		{
			if (!isLocked(TranslateZ))
				_position.z = f;

			return *this;
		}

		inline ViewMatrix & position(Float fx, Float fy, Float fz)
		{
			if (!isLocked(TranslateX))
				_position.x = fx;

			if (!isLocked(TranslateY))
				_position.y = fy;

			if (!isLocked(TranslateZ))
				_position.z = fz;

			return *this;
		}



		/*
		Rotate the Camera
		*/
		inline ViewMatrix & yaw(Float yaw)
		{
			if (!isLocked(RotateYaw))
				_rotation.y = yaw;

			return *this;
		}
		inline ViewMatrix & pitch(Float pitch)
		{
			if (!isLocked(RotatePitch))
				_rotation.x = pitch;

			return *this;
		}
		inline ViewMatrix & roll(Float roll)
		{
			if (!isLocked(RotateRoll))
				_rotation.z = roll;

			return *this;
		}

		/*
		Distance
		*/
		inline ViewMatrix & distance(Float distance)
		{
			if (!isLocked(Distance))
				_distance = distance;

			return *this;
		}

		/*
		Locks the Camera
		*/
		inline ViewMatrix & lock() { _lockFlags = Lock; }

		/*
		Unlocks the Camera
		*/
		inline ViewMatrix & unlock() { _lockFlags = Unlock; }


		void calculate() override
		{
			glm::mat4 matrix(1.0f);

			// Distance camera is from view point
			matrix = glm::translate(matrix, glm::vec3(0, 0, -distance()));

			// Camera Rotation
			matrix = glm::rotate(matrix, -pitch(), glm::vec3(1.0f, 0.0f, 0.0f));
			matrix = glm::rotate(matrix, -yaw(), glm::vec3(0.0f, 1.0f, 0.0f));
			matrix = glm::rotate(matrix, -roll(), glm::vec3(0.0f, 0.0f, 1.0f));

			// Camera Translation
			_view = glm::translate(matrix, -position());
		}



	protected:
		glm::mat4 _view;							// View Matrix

	private:
		// Locks camera movement
		//Boolean _locked = false;
		UInt32 _lockFlags = 0;


		Float _distance = 1.0f;
		glm::vec3 _position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 _rotation{ 0.0f, 0.0f, 0.0f };
	};

}