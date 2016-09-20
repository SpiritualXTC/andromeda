#pragma once
#include <memory>

#include <andromeda/stddef.h>

namespace andromeda
{
	// Forward Declarations
	class GraphicsState;


	/*
		Specifies the object can be rendered
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

		// Render the Object
		virtual void render(GraphicsState & state) = 0;

		//Get Unique ID of the Renderable
		inline const Int32 id() const { return _id; }

	private:
		Int32 _id = 0;
	};
}

