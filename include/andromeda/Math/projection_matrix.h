#pragma once


#include "camera_matrix.h"

namespace andromeda
{

	
	/*
		TODO: Add some more abstraction, especially to the projection matrix
	*/


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
		void update() override
		{
			update(width(), height());
		}

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

		// Set Zoom
		inline PerspectiveMatrix & zoom(Float z)
		{
			_zoom = z;

			return *this;
		}




		// Gets the FOV
		inline Float fov() const { return _fov; }

		// Get Near Clipping Plane
		inline Float zNear() const { return _near; }

		// Get Far Clipping Plane
		inline Float zFar() const { return _far; }


		// Gets the Zoom
		inline Float zoom() const { return _zoom; }

	protected:
		/*
			Calculates the Matrix
		*/
		void calculate() override
		{
			/*
			Float aspect = width() / height();

			Float fovy = glm::pi<Float>() / 4.0f;

			Float fovx = 2 * atan(tan(fovy * 0.5) * aspect);
			*/

			/*
				TODO: Googly Correct Fov calculations :)
			*/
			_projection = glm::perspectiveFov(fov(), width(), height(), zNear(), zFar());

		//	if (_zoom != 1.0f)
		//	{
				glm::mat4 m(1.0f);

				m = glm::scale(m, glm::vec3(zoom(), zoom(), 1.0f));

				_projection = _projection * m;
		//	}
		}
	private:
		// Clipping Planes
		Float _near = 0.1f;
		Float _far = 1000.0f;

		Float _fov = glm::pi<Float>() / 4.0f;

		Float _zoom = 1.0f;


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
		It's Orthogonal
	*/
	class ScreenMatrix : virtual public IProjectionMatrix
	{
	public:
		// Get the Matrix
		const glm::mat4 & matrix() const override { return _projection; }

		// Set Near Clipping Plane
		inline ScreenMatrix & zNear(Float zN)
		{
			_near = zN;

			return *this;
		}

		// Set Far Clipping Plane
		inline ScreenMatrix & zFar(Float zF)
		{
			_far = zF;

			return *this;
		}

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
			_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, zNear(), zFar());
		}
	private:
		// Clipping Planes
		Float _near = 0.1f;
		Float _far = 1000.0f;

		Float _size = 1.0f;


		glm::mat4 _projection;
	};

}