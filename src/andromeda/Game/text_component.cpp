#include <andromeda/Game/text_component.h>

#include <andromeda/Graphics/font_graphics.h>
#include <andromeda/Graphics/text.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Geometry/geometry.h>

#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/transform.h>
#include <andromeda/Renderer/render_state.h>


#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>

#include <codecvt>

using namespace andromeda;


#if 0
/*

*/
TextRenderComponent::TextRenderComponent(std::shared_ptr<Font> font, std::shared_ptr<ITransform> transform)
	: RenderComponent("text")
	, _font(font)
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
void TextRenderComponent::render(RenderState & rs)
{
	// Set Matrix
	rs.setModelMatrix(_transform->matrix());

	// Draw String
	//_font->drawText(shader, _string, ms);
}

#endif








/*

*/
TextRenderComponent::TextRenderComponent(std::shared_ptr<FontGraphics> font, std::shared_ptr<ITransform> transform)
	: RenderComponent("text")
	, _font(font)
	, _transform(transform)
{

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::string s = andromeda::LoadFile("../res/star_wars.txt");
	_string = converter.from_bytes(s);;


	_text = std::make_shared<Text>(_font, _string);

}



/*

*/
void TextRenderComponent::render(RenderState & rs)
{
	assert(_font);

	// Set Model Matrix
	rs.setModelMatrix(_transform->matrix());

	// Get Textures
	const std::shared_ptr<ITexture> & diffuseTex = _material.getDiffuseTexture();

	// Bind Texture
	if (diffuseTex)
		diffuseTex->bind();

	// Set Material
	rs.setMaterial(_material);
	
	// Render Text
	_text->render();

	// Unbind Texture
	if (diffuseTex)
		diffuseTex->unbind();
}