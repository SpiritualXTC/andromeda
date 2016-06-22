#ifndef _ANDROMEDA_GRAPHICS_RENDERABLE_H_
#define _ANDROMEDA_GRAPHICS_RENDERABLE_H_

#include <memory>

#include <andromeda/stddef.h>

#include <andromeda/glm.h>

namespace andromeda
{
	// Forward Declarations
	class IShader;
	class MatrixStack;



	/*
		First Gen of the new Renderable Class
	*/
	class IRenderable
	{
	private:
		static Int32 RENDERABLE_ID;

	public:
		IRenderable() 
		{
			_id = ++IRenderable::RENDERABLE_ID;
		}
		virtual ~IRenderable() {}


		//virtual const glm::mat4 & matrix() const = 0;


		/*
			Render
		*/
		virtual void render(const std::shared_ptr<IShader> shader, MatrixStack & ms) = 0;



		/*
			Get Unique ID of the Renderable
		*/
		inline const Int32 id() const { return _id; }

	private:
		Int32 _id = 0;
	};
}

#endif