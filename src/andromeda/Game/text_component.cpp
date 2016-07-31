#include <andromeda/Game/text_component.h>

#include <andromeda/Graphics/font.h>
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/transform.h>


#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>

#include <codecvt>

using namespace andromeda;

/*

*/
TextRenderComponent::TextRenderComponent(std::shared_ptr<Font> font, std::shared_ptr<ITransform> transform)
//	: RenderComponent("vector")
	: _font(font)
	, _transform(transform)
{
	_string = andromeda::LoadFile("../res/star_wars.txt");
}


/*

*/
void TextRenderComponent::render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms)
{
	assert(_font);

	// Push Matrix
	ms.push();
	ms.multiply(_transform->matrix());

	// Draw String
	//_font->drawText(shader, _string, ms);




	// Pop the matrix
	ms.pop();
}











/*

*/
FontRenderComponent::FontRenderComponent(std::shared_ptr<IFont> font, std::shared_ptr<ITransform> transform)
	: _font(font)
	, _transform(transform)
{

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::string s = andromeda::LoadFile("../res/star_wars.txt");
	_string = converter.from_bytes(s);;
}


/*

*/
void FontRenderComponent::render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms)
{
	assert(_font);

	// Push Matrix
	ms.push();
	ms.multiply(_transform->matrix());


	// Draw String
	_font->drawText(shader, _string, ms);

	// Pop the matrix
	ms.pop();
}