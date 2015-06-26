#ifndef _ANDROMEDA_GRAPHICS_RENDERABLE_H_
#define _ANDROMEDA_GRAPHICS_RENDERABLE_H_

#include "../stddef.h"

#include <glm/glm.hpp>

namespace andromeda
{
	// Forward Declarations
	class Shader;



	class IRenderable
	{
	private:
		static Int32 RENDERABLE_ID;


	public:
		IRenderable() : IRenderable(0){}	/* Should this be defaultable.... shouldn't even be here :) ??? */

		IRenderable(UInt32 group)
		{
			_id = ++IRenderable::RENDERABLE_ID;
			_group = group;
		}

		virtual ~IRenderable(){}

		virtual void render(const Int32 pass, const Shader * const shader, const glm::mat4 & modelView) = 0;

		inline const Int32 id() { return _id; }


		inline const Int32 group() { return _group; }

	private:
		Int32 _id = 0;
		Int32 _group = 0;
	};

}

#endif