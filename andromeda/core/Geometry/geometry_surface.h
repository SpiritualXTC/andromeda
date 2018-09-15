#pragma once





#include "geometry_generate.h"
#include "geometry_surface_function.h"


namespace andromeda
{
	namespace geometry
	{
		/*
		
		*/
		class Surface : virtual public GeometryGenerate
		{
		public:
			Surface() {}
			virtual ~Surface() {}

			UInt32 getVertexCount() const
			{
				return (_divisions0 + 1) * (_divisions1 + 1);
			}
			UInt32 getFaceCount() const
			{
				return _divisions0 * _divisions1 * 2;
			}



			Surface & setDivisions(Int32 div0, Int32 div1)
			{
				assert(div0 != 0 || div1 != 0);

				_divisions0 = div0;
				_divisions1 = div1;

				return *this;
			}

			Surface & setRange(Float r0, Float r1)
			{
				_minimum0 = -r0 / 2;
				_minimum1 = -r1 / 2;
				_maximum0 = r0 / 2;
				_maximum1 = r1 / 2;

				return *this;
			}
			Surface & setMinimum(Float min0, Float min1)
			{
				_minimum0 = min0;
				_minimum1 = min1;

				return *this;
			}
			Surface & setMaximum(Float max0, Float max1)
			{
				_maximum0 = max0;
				_maximum1 = max1;

				return *this;
			}

			Surface & setPositionFunction(SurfaceFunction * func)
			{
				_positionFunction = func;

				return *this;
			}

			Surface & setNormalFunction(SurfaceFunction * func)
			{
				_normalFunction = func;

				return *this;
			}
			

		protected:
			void buildPosition(glm::vec3 * pvertices, UInt32 count) override;
			void buildNormals(glm::vec3 * pvertices, UInt32 count) override;
			void buildTexCoords(glm::vec2 * pvertices, UInt32 count) override;
			void buildIndices(UInt32 * pindices, UInt32 count) override;

		private:

			void buildNormalSmoothing(glm::vec3 * pvertices, UInt32 count);

			UInt32 _divisions0 = 1;
			UInt32 _divisions1 = 1;

			Float _minimum0 = -1.0f;
			Float _minimum1 = -1.0f;

			Float _maximum0 = 1.0f;
			Float _maximum1 = 1.0f;

			SurfaceFunction * _positionFunction;
			SurfaceFunction * _normalFunction;
		};
	}


#if 0
	/*
		CreateSurface():

		Creates a surface using a templated generator, with custom data
	*/
	template <typename T>
	std::shared_ptr<Geometry> CreateSurface(Float minX, Float minY, Float maxX, Float maxY, Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const T *)> generator, const T * data);
	

	/*
		CreateSurface():

		Creates a surface using a templated generator, with custom data, using the default range [-1, 1]
	*/
	template <typename T>
	inline std::shared_ptr<Geometry> CreateSurface(Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const T *)> generator, const T * data)
	{
		return CreateSurface<T>(-1.0f, -1.0f, 1.0f, 1.0f, divX, divY, genMask, generator, data);
	}



	

	/*
		CreateSurface():

		Creates a surface using an untyped generator, with custom data.
	*/
	inline std::shared_ptr<Geometry> CreateSurface(Float minX, Float minY, Float maxX, Float maxY, Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const void *)> generator, const void * data)
	{
		return CreateSurface<void>(minX, minY, maxX, maxY, divX, divY, genMask, generator, data);
	}

	/*
		CreateSurface():

		Creates a surface using an untyped generator, with custom data, using the default range.
	*/
	inline std::shared_ptr<Geometry> CreateSurface(Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float, const void*)> generator, const void * data)
	{
		return CreateSurface<void>(-1.0f, -1.0f, 1.0f, 1.0f, divX, divY, genMask, generator, data);
	}



	/*
		CreateSurface():

		Creates a surface using a custom generator type.
	*/
	inline std::shared_ptr<Geometry> CreateSurface(Float minX, Float minY, Float maxX, Float maxY, Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float)> generator)
	{
		if (! generator)
			return CreateSurface<void>(minX, minY, maxX, maxY, divX, divY, genMask, nullptr, nullptr);

		return CreateSurface<void>(minX, minY, maxX, maxY, divX, divY, genMask, [&](Float x, Float y, const void *){return generator(x, y); }, nullptr);
	}


	/*
		CreateSurface():

		Creates a surface using a custom generator type, using the default range.
	*/
	inline std::shared_ptr<Geometry> CreateSurface(Int32 divX, Int32 divY, UInt32 genMask, std::function<glm::vec3(Float, Float)> generator)
	{
		if (!generator)
			return CreateSurface<void>(-1.0f, -1.0f, 1.0f, 1.0f, divX, divY, genMask, nullptr, nullptr);

		return CreateSurface<void>(-1.0f, -1.0f, 1.0f, 1.0f, divX, divY, genMask, [&](Float x, Float y, const void *){return generator(x, y); }, nullptr);
	}



	// Surface Helper Functions
	
	Boolean assignIndices(Int32 divX, Int32 divY, Int32 count, UInt32 * pindices);
	Boolean assignTexture(Int32 divX, Int32 divY, Int32 count, glm::vec2 * ptexture);


	Boolean normalSmoothing(glm::vec3 * pvertices, Int32 vertexCount, UInt32 * pindices, Int32 indexCount, glm::vec3 * pnormals);
#endif
}
