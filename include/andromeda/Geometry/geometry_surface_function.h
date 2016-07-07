#pragma once

#include <functional>

#include <andromeda/glm.h>
#include <andromeda/stddef.h>

namespace andromeda
{
	namespace geometry
	{

		/*
			Interface for generating a Surface
		*/
		class SurfaceFunction
		{
		public:
			SurfaceFunction() {}
			virtual ~SurfaceFunction() {}

			virtual glm::vec3 calc(Float n0, Float n1) = 0;
		};



		/*
			Class for generating a Surface Grid
		*/
		class SurfaceFunctionGrid : public virtual SurfaceFunction
		{
		public:
			SurfaceFunctionGrid(Float altitude = 0.0f)
				: _altitude(altitude)
			{

			}

			glm::vec3 calc(Float n0, Float n1) override
			{
				return glm::vec3(n0, _altitude, n1);
			}

		private:
			Float _altitude = 0.0f;
		};




		/*
		Class for generating a Surface using a Lambda Function to calculate the data
		*/
		template <typename T = void>
		class SurfaceFunctionLambda : public virtual SurfaceFunction
		{
		public:
			SurfaceFunctionLambda(std::function<glm::vec3(Float, Float, const T &)> generator, const T & data)
				: _generator(generator)
				, _data(data)
			{
				assert(generator);
			}


			glm::vec3 calc(Float n0, Float n1) override
			{
				return _generator(n0, n1, _data);
			}

		private:
			std::function<glm::vec3(Float, Float, const T &)> _generator;
			const T & _data;
		};

		/*
		Specialisation for parameter-less tempalte .... could do with a tidy up though
		*/
		template <>
		class SurfaceFunctionLambda<void> : public virtual SurfaceFunction
		{
		public:
			SurfaceFunctionLambda(std::function<glm::vec3(Float, Float)> generator)
				: _generator(generator)
			{
				assert(generator);
			}


			glm::vec3 calc(Float n0, Float n1) override
			{
				return _generator(n0, n1);
			}

		private:
			std::function<glm::vec3(Float, Float)> _generator;
		};

	}
}

