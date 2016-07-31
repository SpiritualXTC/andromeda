#pragma once

#include "render_component.h"


/*
	This class is in progress, and is completely INCORRECT! well its incorrect in the way text is rendered :P
*/
namespace andromeda
{
	class ITransform;

	class IFont;
	class Font;
	class Geometry;

	class TextRenderComponent : public RenderComponent
	{
	public:
		TextRenderComponent(std::shared_ptr<Font> font, std::shared_ptr<ITransform> transform);

		void render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms) override;

	private:
		std::shared_ptr<Font> _font;
		std::shared_ptr<ITransform> _transform;

		std::string _string;
	};





	/*
		Testing the new abstract fonts....
	*/
	class FontRenderComponent : public RenderComponent
	{
	public:
		FontRenderComponent(std::shared_ptr<IFont> font, std::shared_ptr<ITransform> transform);

		void render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms) override;

	private:
		std::shared_ptr<IFont> _font;
		std::shared_ptr<ITransform> _transform;

		std::wstring _string;
	};
}