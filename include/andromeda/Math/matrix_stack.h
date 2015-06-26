#ifndef _ANDROMEDA_MATH_MATRIX_STACK_H_
#define _ANDROMEDA_MATH_MATRIX_STACK_H_

#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../andromeda.h"

namespace andromeda
{
	/*
	
	*/
	class MatrixStack
	{
	public:
		MatrixStack()
		{
			_top = glm::mat4(1.0f);
		}
		MatrixStack(const glm::mat4 & matrix)
		{
			_top = matrix;
		}		
		virtual ~MatrixStack()
		{

		}

	



		/*

		*/
		inline void translate(Float x, Float y, Float z)
		{
			translate(glm::vec3(x, y, z));
		}

		void translate(const glm::vec3 & translation)
		{
			_top = glm::translate(_top, translation);
		}


		/*

		*/
		inline void rotateX(Float radians)
		{
			rotate(radians, glm::vec3(1, 0, 0));
		}
		inline void rotateY(Float radians)
		{
			rotate(radians, glm::vec3(0, 1, 0));
		}
		inline void rotateZ(Float radians)
		{
			rotate(radians, glm::vec3(0, 0, 1));
		}

		void rotate(Float radians, const glm::vec3 & axis)
		{
			_top = glm::rotate(_top, radians, axis);
		}


		/*

		*/
		inline void scale(Float f)
		{
			scale(glm::vec3(f, f, f));
		}

		inline void scale(Float sx, Float sy, Float sz)
		{
			scale(glm::vec3(sx, sy, sz));
		}


		void scale(const glm::vec3 & scale)
		{
			_top = glm::scale(_top, scale);
		}


		/*

		*/
		void multiply(const glm::mat4 & matrix)
		{
			_top *= matrix;
		}


		/*

		*/
		void push()
		{
			// Preserve Matrix
			_matrices.push(_top);
		}

		void pop()
		{
			// Get New Top
			_top = _matrices.top();
			_matrices.pop();
		}


		void reset()
		{
			_top = _matrices.top();
		}


		MatrixStack & operator *= (const glm::mat4 & matrix)
		{
			_top *= matrix;
			return *this;
		}

		MatrixStack & operator += (const glm::mat4 & matrix)
		{
			push();
			multiply(matrix);
		}

		MatrixStack & operator ++()
		{
			push();
		}

		MatrixStack & operator --()
		{
			pop();
		}


		inline const glm::mat4 & top() const { return _top; }




	private:

		glm::mat4 _top;
		std::stack<glm::mat4> _matrices;

	};
}


#endif