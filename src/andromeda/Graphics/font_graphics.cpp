#include <andromeda/Graphics/font_graphics.h>

#include <cassert>

// Freetype Library
#include <freetype/ftoutln.h>

// Boost
#include <boost/algorithm/string.hpp>

// Andromeda
#include <andromeda/resources.h>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_polygon.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>
#include <andromeda/Math/matrix_stack.h>

#include <andromeda/Utilities/font.h>

#include <andromeda/Utilities/log.h>


using namespace andromeda;




/*

*/
FontGraphics::FontGraphics(const std::shared_ptr<Font> & ft, UInt32 fontSize)
	: _font(ft)
	, _fontSize(fontSize)
{
	assert(_font);

	// Sets the Font Size
	_font->setFontSize(_fontSize);

	// Get Fixed Metrics from Font
	_lineSpacing = _font->getLineSpacing();

	log_verbosep("Font Size = %1%", fontSize);
	log_verbosep("Line Spacing = %1%", _lineSpacing);
}


/*
	mapIndex():

	Maps the character code to the index in the array.
*/
UInt32 FontGraphics::mapIndex(UInt32 charCode)
{
	/*
		TODO: Optimize!
		This could (maybe) work just as well, using direct access
		so long as the error character was used IFF, the character hadn't been assigned previously.
	*/

	const auto & it = _map.find(charCode);

	if (it == _map.end())
	{
		if (loadCharacter(charCode))
			return mapIndex(charCode);
		else
			return FontGraphics::FONT_INVALID_CHARACTER;
	}

	return it->second;
}


/*
	loadCharacter():

	Loads a single character
*/
Boolean FontGraphics::loadCharacter(UInt32 charCode)
{
	assert(_font);

	// Sets the Font Size
	_font->setFontSize(_fontSize);

	// Get the Metrics
	GlyphMetric gm;
	_font->getCharacterMetrics(charCode, gm);

	// Loads the Character
	UInt32 index = loadChar(gm);

	// Add Character to CharCode -> Index Mapping
	_map[charCode] = index;

	return true;
}


/*
	loadCharacter():

	Loads a range of characters
*/
Boolean FontGraphics::loadCharacter(UInt32 charCode_begin, UInt32 charCode_end)
{
	Boolean b = true;
	for (UInt32 i = charCode_begin; i <= charCode_end; ++i)
		b &= loadCharacter(i);

	return b;
}






#if 0
/*

*/
void FontGraphics::drawText(const std::shared_ptr<andromeda::IShader> shader, const std::wstring & text, andromeda::MatrixStack & ms)
{
	// Push New Matrix
	ms.push();

	// Begin Drawing
	begin();

	// Draw String
	if (text.find_first_of('\n') != std::string::npos)
	{
		std::vector<std::wstring> lines;

		splitText(text, lines);

		for (const auto & s : lines)
		{
			ms.push();
			drawString(shader, s, ms);

			ms.pop();

			/*
				TODO:
				Move the Font Scaler to the "interface"
			*/
			glm::mat4 m(1.0f);
			m = glm::translate(m, glm::vec3(0.0f, -getLineSpacing() / 64.0f, 0.0f));

			ms.multiply(m);
		}
	}
	else
		drawString(shader, text, ms);

	// End Drawing
	end();

	// Push Old Matrix
	ms.pop();
}


/*

*/
void FontGraphics::drawString(const std::shared_ptr<andromeda::IShader> shader, const std::wstring & string, andromeda::MatrixStack & ms)
{
	// If multiline rendering
	// Split the string into array divided by \n, \r, representing lines of text
	// Push Matrix
	// LOOP: call drawText() without the multiline flag ... after each call, multiply the matrix in the NEGATIVE y-direction by the character height
	// Pop Matrix
	// Do not Continue Function!



	// If Justify is enabled....
	// [See android font class using in JEngine/Backlash]
	// This needs to split the string into lines that will fit into a specified region.
	// IF a Split occurs. Call drawText() again with multiline rendering enabled. Do not Continue Function
	// ELSE calculate the character-spacing required to correctly fit the text :)



	// Draw the Characters
	for (const auto & c : string)
	{
		// Update the Model View Matrix
		shader->setUniform("u_modelview", ms.top());

		// Load this Character ???


		// Draw Character
		Float advance = drawCharacter(shader, c);	// Some character may be drawn in a manner that requires additional advance (Temporary)

		// Update Matrix
		glm::mat4 m(1.0f);	// This needs to be based on the font-advance & additional spacing

		// Translate Matrix :: "Advance" position
		m = glm::translate(m, glm::vec3(advance, 0.0f, 0.0f));

		// Multiply the new matrix in
		ms.multiply(m);
	}
}
#endif