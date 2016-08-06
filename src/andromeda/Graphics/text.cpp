#include <andromeda/Graphics/text.h>

#include <cassert>

#include <andromeda/Graphics/font.h>

using namespace andromeda;



/*

*/
Text::Text(const std::shared_ptr<IFont> & font, const std::string & text)
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
Boolean Text::setText(const std::string & text)
{
	if (_font.expired())
		return false;

	// Assign Text
	_text = text;

	std::shared_ptr<IFont> font = _font.lock();

}




/*

*/
void Text::render()
{


}