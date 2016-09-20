#pragma once

#include <andromeda/Graphics/material.h>

#include "render_component.h"



/*
	This class is in progress, and is completely INCORRECT! well its incorrect in the way text is rendered :P
*/
namespace andromeda
{
	class ITransform;

	class FontGraphics;
	class Text;
	class Geometry;

	class GraphicsState;





	/*
		Testing the new abstract fonts....
	*/
	class TextRenderComponent : public RenderComponent
	{
	public:
		TextRenderComponent(std::shared_ptr<FontGraphics> font, std::shared_ptr<ITransform> transform);

		void render(GraphicsState & rs) override;


		Material & getMaterial() { return _material; }

		const Material & getMaterial() const { return _material; }


	private:
		// Material
		Material _material;


		std::shared_ptr<FontGraphics> _font;
		std::shared_ptr<ITransform> _transform;

		std::wstring _string;



		std::shared_ptr<Text> _text;
	};
}