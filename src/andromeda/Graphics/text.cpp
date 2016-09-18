#include <andromeda/Graphics/text.h>

#include <cassert>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Graphics/font_graphics.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Geometry/geometry_cube.h>

using namespace andromeda;



/*

*/
Text::Text(const std::shared_ptr<FontGraphics> & font, const std::wstring & text)
	: _font(font)
{
	assert(font);

	// Sets the Text
	setText(text);
}


/*

*/
Text::~Text()
{


}



/*

*/
Boolean Text::setText(const std::wstring & text)
{
	if (_font.expired())
		return false;

	// Assign Text
	_text = text;

	std::shared_ptr<FontGraphics> font = _font.lock();

	// Generate Text
	_geometry = font->generateText(text);

	// Get Texture
	_texture = font->getTexture();

	// Flush Variable List

	return true;
}




/*

*/
void Text::render()
{
	// TODO: set texture [This should be binding 1, but multiple textures can't be used yet]
	_texture->bind(0);

	// render Geometry
	_geometry->render();

	//
	_texture->unbind(0);
}



















/*-------------------------------------------*/
TextEx::TextEx(const std::shared_ptr<FontGraphics> & font)
{

}