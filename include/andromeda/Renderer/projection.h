#pragma once

/*
	TODO:

	Remove this file
*/

#include <andromeda/glm.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <andromeda/stddef.h>

#include <andromeda/Utilities/observable.h>

namespace andromeda
{
	template <typename T>
	class CameraMatrix : public Observable<T>
	{
	public:
		CameraMatrix() {}
		virtual ~CameraMatrix() {}

		// Get the Matrix
		virtual const inline glm::mat4 & matrix() const = 0;


		// Update the Matrix and send Notification to observers
		void update()
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




	/*

	*/
	class IViewMatrix : public CameraMatrix<IViewMatrix>
	{
	public:
		

	private:

	};










	/*
		TODO:
		Move this somewhere...
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
			if (! isLocked(TranslateZ))
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






	/*

	*/
	class IProjectionMatrix : public CameraMatrix<IProjectionMatrix>
	{
	public:

		inline Float width() const { return _width; }
		inline Float height() const { return _height; }

		inline Float aspectRatio() const { return _aspect; }

		/*

		*/
		void update(Float width, Float height)
		{
			_width = width;
			_height = height;

			_aspect = _width / _height;

			CameraMatrix<IProjectionMatrix>::update();
		}

	private:

		Float _width = 1.0f;
		Float _height = 1.0f;
		Float _aspect = 1.0f;
	};


	/*
		New Projection Matrix

		TODO: Convert to builder (Maybe)
	*/
#if 0
	class ProjectionMatrix : public CameraMatrix<ProjectionMatrix>
	{
	public:

		/*

		*/
		inline void setNear(Float fn) { _near = fn; }

		inline void setFar(Float ff) { _far = ff; }

		inline Float getWidth() const { return _width; }
		inline Float getHeight() const { return _height; }

		inline Float getAspectRatio() const { return _aspect; }

		inline Float getNear() const { return _near; }
		inline Float getFar() const { return _far; }


		/*
			Adjusts the Matrix
		*/
		void update(Float width, Float height)
		{
			_width = width;
			_height = height;

			_aspect = _width / _height;

			CameraMatrix<ProjectionMatrix>::update();
		}

	private:

		Float _width = 1.0f;
		Float _height = 1.0f;

		Float _aspect = 1.0f;

		// Clipping Planes
		Float _near = 0.1f;
		Float _far = 1000.0f;
	};
#endif


	/*
	
	*/
	class PerspectiveMatrix : virtual public IProjectionMatrix
	{
	public:

		const glm::mat4 & matrix() const override { return _projection; }

		// Set Field of Vision [Fov]
		inline PerspectiveMatrix & fov(Float fov)
		{
			_fov = fov;

			return *this;
		}

		// Set Near Clipping Plane
		inline PerspectiveMatrix & zNear(Float zN)
		{
			_near = zN;

			return *this;
		}

		// Set Far Clipping Plane
		inline PerspectiveMatrix & zFar(Float zF)
		{
			_far = zF;

			return *this;
		}





		// Gets the FOV
		inline Float fov() const { return _fov; }

		// Get Near Clipping Plane
		inline Float zNear() const { return _near; }

		// Get Far Clipping Plane
		inline Float zFar() const { return _far; }

	protected:
		/*
			Calculates the Matrix
		*/
		void calculate() override
		{
			_projection = glm::perspectiveFov(fov(), width(), height(), zNear(), zFar());
		}
	private:
		// Clipping Planes
		Float _near = 0.1f;
		Float _far = 1000.0f;

		Float _fov = glm::pi<Float>() / 4.0f;



		glm::mat4 _projection;
	};


	/*
	
	*/
	class OrthogonalMatrix : virtual public IProjectionMatrix
	{
	public:

		// Get the Matrix
		const glm::mat4 & matrix() const override { return _projection; }

		// Set Orthogonal Matrix Size :: The Size is a multiplier as the orthogonal matrix is bounded [-aspect, aspect, -1, 1]
		inline OrthogonalMatrix & multiplier(Float size) 
		{ 
			_size = size; 
			
			return *this;
		}

		// Set Near Clipping Plane
		inline OrthogonalMatrix & zNear(Float zN)
		{
			_near = zN;

			return *this;
		}

		// Set Far Clipping Plane
		inline OrthogonalMatrix & zFar(Float zF)
		{
			_far = zF;

			return *this;
		}




		// Get Orthogonal Matrix
		inline Float size() { return _size; }

		// Get Near Clipping Plane
		inline Float zNear() const { return _near; }

		// Get Far Clipping Plane
		inline Float zFar() const { return _far; }

	protected:
		/*
			Calculates the Matrix
		*/
		void calculate() override
		{
			Float x = aspectRatio() * size();
			Float y = size();

			_projection = glm::ortho(-x, x, -y, y, zNear(), zFar());
		}

	private:
		// Clipping Planes
		Float _near = 0.1f;
		Float _far = 1000.0f;

		Float _size = 1.0f;


		glm::mat4 _projection;
	};













	/*
		TODO:
		Remove Everything Below Meh
	*/
	class IProjection
	{
	public:

		virtual void calculate(const Float width, const Float height) = 0;
		virtual inline glm::mat4 & matrix() = 0;
	};


	/*
		Basic Orthoginal Projection

		NEEDS TESTING
	*/
	class ProjectionOrtho : public IProjection//, public virtual ProjectionMatrix
	{
	public:
		ProjectionOrtho()
		{

		}
		virtual ~ProjectionOrtho()
		{

		}

		// OLD INTERFACE
		void calculate(const Float width, const Float height)
		{
			Float aspect = width / height;
			
			_projection = glm::ortho(aspect, -aspect, -1.0f, 1.0f, 0.1f, 1000.0f);
		}

		inline glm::mat4 & matrix() override {return _projection;}






#if 0
		//NEW INTERFACE
		const glm::mat4 & getProjection() const override { return _projection; }
		const glm::mat4 & getView() const override { return _view; }

	protected:
		void calcProjection() override
		{
			Float x = getAspectRatio() / getZoom();
			Float y = 1.0f / getZoom();

			_projection = glm::ortho(-x, x, -y, y, getNear(), getFar());
		}

		void calcView() override
		{
			glm::mat4 m(1.0f);

			_view = glm::translate(m, glm::vec3(0, 0, -getDistance()));
		}
#endif
	private:
		glm::mat4 _projection;
		glm::mat4 _view;
	};


	/*
		Basic Fov Perspective Matrix
	*/
	class ProjectionPerspective : public IProjection//, public virtual ProjectionMatrix
	{
	public:
		ProjectionPerspective() { }
		virtual ~ProjectionPerspective() {}

		// OLD INTERFACE
		void calculate(const Float width, const Float height)
		{
			_projection = glm::perspectiveFov(glm::pi<Float>() / 4.0f, width, height, 0.1f, 1000.0f);
		}

		inline glm::mat4 & matrix() override { return _projection; }



#if 0
		// NEW INTERFACE
		const glm::mat4 & getProjection() const override { return _projection; }
		const glm::mat4 & getView() const override { return _view; }

	protected:
		void calcProjection() override
		{
			_projection = glm::perspectiveFov(glm::pi<Float>() / 4.0f, getWidth(), getHeight(), getNear(), getFar());
		}

		void calcView() override
		{
			glm::mat4 m(1.0f);

			_view = glm::translate(m, glm::vec3(0, 0, -getDistance()));
		}
#endif

	private:
		glm::mat4 _projection;
		glm::mat4 _view;
	};
}