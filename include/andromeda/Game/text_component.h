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

	class RenderState;

#if 0
	class TextRenderComponent : public RenderComponent
	{
	public:
		TextRenderComponent(std::shared_ptr<Font> font, std::shared_ptr<ITransform> transform);

		void render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms) override;
		void render(RenderState & rs) override;


	private:
		std::shared_ptr<Font> _font;
		std::shared_ptr<ITransform> _transform;

		std::string _string;
	};
#endif




	/*
		Testing the new abstract fonts....
	*/
	class TextRenderComponent : public RenderComponent
	{
	public:
		TextRenderComponent(std::shared_ptr<FontGraphics> font, std::shared_ptr<ITransform> transform);

		void render(RenderState & rs) override;


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