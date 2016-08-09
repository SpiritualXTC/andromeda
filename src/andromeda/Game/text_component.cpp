#include <andromeda/Game/text_component.h>

#include <andromeda/Graphics/font.h>
#include <andromeda/Graphics/text.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Geometry/geometry.h>

#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/transform.h>


#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>

#include <codecvt>

using namespace andromeda;

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
FontRenderComponent::FontRenderComponent(std::shared_ptr<IFont> font, std::shared_ptr<ITransform> transform)
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
void FontRenderComponent::render(const std::shared_ptr<andromeda::IShader> shader, andromeda::MatrixStack & ms)
{
	assert(_font);

	// Push Matrix
	ms.push();
	ms.multiply(_transform->matrix());

	// Update the Model View Matrix
	shader->setUniform("u_modelview", ms.top());


	// Get Material
	shader->setUniform("g_ambient", _material.getAmbient());
	shader->setUniform("g_diffuse", _material.getDiffuse());
	shader->setUniform("g_specular", _material.getSpecular());

	// Get Texture
	const std::shared_ptr<ITexture> & diffuseTex = _material.getDiffuseTexture();

	if (diffuseTex)
	{
		// TODO: See Mesh Class
		diffuseTex->bind();
		shader->setUniformTexture("g_diffuseTexture", 0);
	}

	// Render Text
	_text->render();


	if (diffuseTex)
	{
		diffuseTex->unbind();
	}


//	_font->drawText(shader, _string, ms);

	// Pop the matrix
	ms.pop();
}