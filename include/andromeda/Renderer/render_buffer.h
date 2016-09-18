#pragma once

/*
	This class is for handling the rendering of objects that are rendered INDIRECTLY.

	Such as:
	- Transparent triangles with sorting.
	- Particles -- At least CPU particles, GPU particles may work differently
	- Instanced Drawing -- Maybe, instanced drawing may require a completely different process again.

	The Process will typically be:
	- Clear Buffer
	- Update all associated objects and append vertices/indices to of the appropriate data into the buffer
	- Render Buffer
*/

namespace andromeda
{
	class RenderBuffer
	{
	public:
		RenderBuffer();
		virtual ~RenderBuffer();

	private:
	};
}
