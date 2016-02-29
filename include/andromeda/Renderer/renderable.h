#ifndef _ANDROMEDA_GRAPHICS_RENDERABLE_H_
#define _ANDROMEDA_GRAPHICS_RENDERABLE_H_

#include "../stddef.h"

#include <glm/glm.hpp>

namespace andromeda
{
	// Forward Declarations
	class Shader;


	/*
	
	*/
	class IRenderable
	{
	private:
		static Int32 RENDERABLE_ID;


	public:
		/*
		
		*/
		IRenderable()
		{
			_id = ++IRenderable::RENDERABLE_ID;
		}

		/*
		
		*/
		virtual ~IRenderable(){}

		/*
			Render!
		*/
		virtual void render(const Shader * const shader, const glm::mat4 & modelView) = 0;

		/*
			Get Unique ID of the Renderable
		*/
		inline const Int32 id() { return _id; }

	private:
		Int32 _id = 0;
	};

}

#endif