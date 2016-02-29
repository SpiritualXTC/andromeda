#ifndef _ANDROMEDA_GAME_CAMERA_H_
#define _ANDROMEDA_GAME_CAMERA_H_

/*
camera.h

	It MIGHT be possible (and more beneficial) for Camera to extend Entity,
	and use the TransformComponent

	But for now, this will do :)
*/

#include <memory>

#include <andromeda/stddef.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace andromeda
{
	class ITransform;



	/*
	
	*/
	class Camera
	{
	public:
		Camera();
		Camera(std::weak_ptr<ITransform> target);
		~Camera();

		//const glm::mat4 & matrix() const { return _view; }

		const glm::mat4 & calcMatrix();


		/*
		
		*/
		inline void setTarget(std::weak_ptr<ITransform> target)
		{
			_target = target;
		}

	


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
		void yaw(Float);
		void pitch(Float);
		void roll(Float);

		const inline Float pitch() const { return _rotation.x; }
		const inline Float yaw() const { return _rotation.y; }
		const inline Float roll() const { return _rotation.z; }




		/* Getters */
		const inline glm::vec3 & position() const { return _position; }
		const inline Float distance() const { return _distance; }

		const inline Boolean hasTarget() const { return ! _target.expired(); }
	


		/* Setters */
		inline void position(Float x, Float y, Float z) { _position = glm::vec3(x, y, z); }
		inline void distance(Float f) { _distance = f; }



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

		// Pointer to the target being tracked by the camera!
		std::weak_ptr<ITransform> _target;
	};

}

#endif