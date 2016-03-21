#ifndef _ANDROMEDA_RENDERER_PROJECTION_H_
#define _ANDROMEDA_RENDERER_PROJECTION_H_

#include <andromeda/glm.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <andromeda/stddef.h>

namespace andromeda
{
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
	class ProjectionOrtho : public IProjection
	{
	public:
		ProjectionOrtho()
		{

		}
		virtual ~ProjectionOrtho()
		{

		}

		void calculate(const Float width, const Float height)
		{
			Float aspect = width / height;
			
			_matrix = glm::ortho(aspect, -aspect, -1.0f, 1.0f, 0.1f, 100.0f);
		}

		inline glm::mat4 & matrix() override {return _matrix;}

	private:
		glm::mat4 _matrix;
	};


	/*
		Basic Fov Perspective Matrix

		NEEDS TESTING
	*/
	class ProjectionPerspective : public IProjection
	{
	public:
		ProjectionPerspective()
		{

		}
		virtual ~ProjectionPerspective()
		{

		}

		void calculate(const Float width, const Float height)
		{
			_matrix = glm::perspectiveFov(glm::pi<Float>() / 4.0f, width, height, 0.0001f, 100.0f);
		}

		inline glm::mat4 & matrix() override { return _matrix; }

	private:
		glm::mat4 _matrix;
	};
}

#endif
