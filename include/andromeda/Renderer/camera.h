#pragma once

/*
	camera.h:

	It MIGHT be possible (and more beneficial) for Camera to extend Entity,
	and use the TransformComponent

	But for now, this will do :)
*/

#include <memory>

#include <andromeda/stddef.h>
#include <andromeda/glm.h>

#include <andromeda/Math/plane.h>
#include <andromeda/Utilities/observer.h>


#include "transform.h"

#include <andromeda/Math/projection_matrix.h>
#include <andromeda/Math/view_matrix.h>


namespace andromeda
{

	/*
		This is the NEW Camera Class

		A Camera is made up Projection, View and Visibility Region

		The PPROJECTION controls the Perspective of the Camera AND "primitive" view matrices and the creation of the Visibility Region
		The VIEW controls the world orientation of the camera

		TODO:
		Also needs to support the matrix stacking... maybe not :)
	*/
	/*
		TODO:
		This recreates memory :: A listener or observer will be able to solve this issue :)

		Both the View/Projection matrix needs to be "observed" by the Camera.
		Any changes sets a flag --
		The flag is polled in the update() function to check for changes
		Any changes resets the flag and updates the matrices

		This will allow the matrices to be altered without using the camera class :)
	*/

	class Camera : public IObserver<IProjectionMatrix>, public IObserver<IViewMatrix>, public std::enable_shared_from_this<Camera>
	{
	private:
		static const Int32 PLANE_COUNT = 6;
	public:
		Camera();
		virtual ~Camera();

		Float getWidth() const { return _width; }
		Float getHeight() const { return _height; }


		/*
			Gets the Projection Matrix
		*/
		const inline glm::mat4 & getProjectionMatrix() const { return _projectionMatrix; }

		/*
			Gets the View Matrix :: This is the Constant View Matrix
		*/
		const inline glm::mat4 & getViewMatrix() const { return _viewMatrix; }
		
		/*
			Gets the Projection Object
		*/
		const inline std::shared_ptr<IProjectionMatrix> & getProjection() const { return _projection; }

		/*
			Gets the View Object
		*/
		const inline std::shared_ptr<IViewMatrix> & getView() const { return _view; }

		/*
			Set Projection Matrix
		*/
		void setProjection(std::shared_ptr<IProjectionMatrix> p);

		/*
			Set View Matrix
		*/
		void setView(std::shared_ptr<IViewMatrix> v);





		/*
			Sets a Perspective Matrix [Projection]
		*/
		std::shared_ptr<PerspectiveMatrix> setPerspectiveFov(Float fov, Float zN, Float zF);

		/*
			Sets an Orthogonal Matrix [Projection]
		*/
		std::shared_ptr<OrthogonalMatrix> setOrthogonal(Float mul, Float zN, Float zF);


		// Sets an Orthogonal Screen Matrix [Projection]
		std::shared_ptr<ScreenMatrix> setOrthogonalScreen(Float zN, Float zF);


		/*
			Sets up a simple view matrix
		*/
		std::shared_ptr<ViewMatrix> setView(Float distance);





		/*
			Updates the Camera
		*/
	//	void update();
		void resize(Float width, Float height);


		/*
			Determine whether Point/Shape/Object is inside the visibility region
		*/
		Boolean isVisible(const glm::vec3 & centre, Float radius) const;



	protected:
		void notify(const IProjectionMatrix * const pm) override;
		void notify(const IViewMatrix * const vm) override;

		void calculate();

	private:
		Float _width = 1.0f;
		Float _height = 1.0f;

		// Cached Matrices
		glm::mat4 _projectionMatrix{ 1.0f };
		glm::mat4 _viewMatrix{ 1.0f };

		// Projection Matrix
		std::shared_ptr<IProjectionMatrix> _projection;

		// Viewing Matrix
		std::shared_ptr<IViewMatrix> _view;

		// Viewing Frustrum
		Plane3f _planes[PLANE_COUNT];
	};


}
