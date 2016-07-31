#include <andromeda/Graphics/font.h>

#include <cassert>

// Freetype Library
#include <freetype/ftoutln.h>

// Boost
#include <boost/algorithm/string.hpp>

// Andromeda
#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_polygon.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Graphics/texture.h>
#include <andromeda/Math/matrix_stack.h>

#include <andromeda/Resources/font_resource.h>

#include <andromeda/Utilities/log.h>



#define GLYPH_METRIC_SCALE_FACTOR (64.0f)
#define GLYPH_VECTOR_SCALE_FACTOR (6400.0f)


// REmove meh
#include <SOIL/SOIL.h>

using namespace andromeda;




/*
	IFONT
*/
IFont::IFont(const std::shared_ptr<FontFace> & ft, UInt32 fontSize)
	: _font(ft)
	, _fontSize(fontSize)
{
	assert(_font);



	_font->setFontSize(12);

	// Get Fixed Metrics from Font
	_lineSpacing = _font->getLineSpacing();
	_fontWidth = _font->getFontWidth();
	_fontHeight = _font->getFontHeight();


	log_debugp("Font Metrics:");
	log_tree();
	log_verbosep("Font Size = 12");
	log_verbosep("Line Spacing = %1%", _lineSpacing);
	log_verbosep("Font Width = %1%", _fontWidth);
	log_verbosep("Font Height = %1%", _fontHeight);





	_font->setFontSize(_fontSize);

	// Get Fixed Metrics from Font
	_lineSpacing = _font->getLineSpacing();
	_fontWidth = _font->getFontWidth();
	_fontHeight = _font->getFontHeight();

	log_verbosep("Font Size = %1%", fontSize);
	log_verbosep("Line Spacing = %1%", _lineSpacing);
	log_verbosep("Font Width = %1%", _fontWidth);
	log_verbosep("Font Height = %1%", _fontHeight);
}







/*

*/
UInt32 IFont::mapIndex(UInt32 charCode)
{
	/*
		TODO: Optimize!
		This could (maybe) work just as well, using direct access
	*/

	const auto & it = _map.find(charCode);

	if (it == _map.end())
	{
		if (loadCharacter(charCode))
			return mapIndex(charCode);
		else
			return IFont::FONT_INVALID_CHARACTER;
	}

	return it->second;
}


/*

*/
Boolean IFont::loadCharacter(UInt32 charCode)
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

*/
Boolean IFont::loadCharacter(UInt32 charCode_begin, UInt32 charCode_end)
{
	Boolean b = true;
	for (UInt32 i = charCode_begin; i <= charCode_end; ++i)
		b &= loadCharacter(i);

	return b;
}


/*

*/
Boolean IFont::splitText(const std::wstring & text, std::vector<std::wstring> & lines)
{
	// Remove Array Characters and split
	boost::split(lines, text, boost::is_any_of("\n"));

	return true;
}


/*

*/
void IFont::drawText(const std::shared_ptr<andromeda::IShader> shader, const std::wstring & text, andromeda::MatrixStack & ms)
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
void IFont::drawString(const std::shared_ptr<andromeda::IShader> shader, const std::wstring & string, andromeda::MatrixStack & ms)
{
	/*
		TODO:
		Clean this up in drawText, using multiple functions :)
	*/

	// If multiline rendering
	// Split the string into array divided by \n, \r, representing lines of text
	// Push Matrix
	// LOOP: call drawText() without the multiline flag ... after each call, multiply the matrix in the NEGATIVE y-direction by the character height
	// Pop Matrix
	// Do not Continue Function!

#if 0
	if (string.find_first_of('\n') != std::string::npos)
	{
		std::vector<std::string> lines;





		for (const auto & s : lines)
		{
			drawString(shader, s, ms);


			// Update Matrix
			glm::mat4 m(1.0f);	// This needs to be based on the font-width & additional spacing

								// Translate Matrix
								// This is the fonts "lineGap" 
								//m = glm::translate(m, glm::vec3(0.0f, -_lineGap, 0.0f));
			m = glm::translate(m, glm::vec3(0.0f, -1.0f, 0.0f));

			ms.multiply(m);
		}

		return;
	}
#endif


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






























/*
	FONTVECTOR
*/





/*

*/
Int32 moveTo(const FT_Vector* to, void* user)
{
	assert(user);
	geometry::Polygon * polygon = (geometry::Polygon*)user;
	
//	log_infop("MOVE: (%1%, %2%)", to->x, to->y);

	glm::vec3 v = glm::vec3(to->x / GLYPH_VECTOR_SCALE_FACTOR, to->y / GLYPH_VECTOR_SCALE_FACTOR, 0.0f);
	polygon->moveTo(v);


	return 0;
}


/*

*/
Int32 lineTo(const FT_Vector*  to, void* user)
{
	assert(user);
	geometry::Polygon * polygon = (geometry::Polygon*)user;

//	log_infop("LINE: To = (%1%, %2%)", to->x, to->y);

	// Add a Line
	glm::vec3 v = glm::vec3(to->x / GLYPH_VECTOR_SCALE_FACTOR, to->y / GLYPH_VECTOR_SCALE_FACTOR, 0.0f);
	polygon->lineTo(v);

	return 0;
}

/*

*/
Int32 conicTo(const FT_Vector * control, const FT_Vector * to, void * user)
{
	assert(user);
	geometry::Polygon * polygon = (geometry::Polygon*)user;

//	log_infop("CONIC: To = (%1%, %2%), Control = (%3%, %4%)", to->x, to->y, control->x, control->y);

	// Add Bezier, with single control point
	// For now just add a line
	glm::vec3 v = glm::vec3(to->x / GLYPH_VECTOR_SCALE_FACTOR, to->y / GLYPH_VECTOR_SCALE_FACTOR, 0.0f);
	glm::vec3 c = glm::vec3(control->x / GLYPH_VECTOR_SCALE_FACTOR, control->y / GLYPH_VECTOR_SCALE_FACTOR, 0.0f);
	polygon->bezierTo(c, v);

	return 0;
}

/*

*/
Int32 cubicTo(const FT_Vector * control1, const FT_Vector * control2, const FT_Vector * to, void * user)
{
	assert(user);
	geometry::Polygon * polygon = (geometry::Polygon*)user;

//	log_infop("CUBIC: To = (%1%, %2%), Control1 = (%3%, %4%), Control2 = (%5%, %6%)", to->x, to->y, control1->x, control1->y, control2->x, control2->y);

	// Add Bezier, with multiple control points
	// For now just add a line

	// The Polygon / Contour Classes currently do not support mutli-control point beziers.
	// However when they do... it will be to split cubic curves into quadratic curves.
	glm::vec3 v = glm::vec3(to->x / GLYPH_VECTOR_SCALE_FACTOR, to->y / GLYPH_VECTOR_SCALE_FACTOR, 0.0f);
	polygon->lineTo(v);

	return 0;
}









/*

*/
Font::Font(const std::string & font, Int32 size)
{
	// Create the Texture
//	_texture = std::make_unique<Texture>(BMP_WIDTH, BMP_HEIGHT);

#if 0
	// Initialise the Bitmap to Black
	for (Int32 h = 0; h < BMP_HEIGHT; ++h)
	{
		for (Int32 w = 0; w < BMP_WIDTH; ++w)
			_bitmap[h][w] = 0;
	}
#endif

	// Load the Bezier Texture
	_texture = andromeda::LoadResource<Texture>("bezier.png");

	// Load the Font
	loadFont(font, size);
}


/*

*/
Font::~Font()
{
	

}


/*

*/
Boolean Font::loadFont(const std::string & font, Int32 size)
{
	FT_Library lib;

	log_infop("Loading Font %1%", font);


	// Init Library
	FT_Error libError = FT_Init_FreeType(&lib);

	if (libError)
		log_err("Error Initialising FreeType Library");


	// Load Font 
	FT_Face face;
	FT_Error fntError = FT_New_Face(lib, font.c_str(), 0, &face);
	if (fntError)
		log_err("Error Loading Font");

	// Set Pixel Size
	FT_Set_Pixel_Sizes(face, size, size);

	_lineGap = face->size->metrics.height / GLYPH_VECTOR_SCALE_FACTOR;	// Why Vector??


	log_debugp("Fixed Sizes: %1%", face->num_fixed_sizes);
	for (Int32 i = 0; i < face->num_fixed_sizes; ++i)
	{
		log_debugp("%1% = %2%x%3%", i, face->available_sizes[i].width, face->available_sizes[i].height);
	}

	log_debugp("BBox: (%1%, %2%), (%3%, %4%)", face->bbox.xMin >> 6, face->bbox.yMin >> 6, face->bbox.xMax >> 6, face->bbox.yMax >> 6);

	log_debugp("LineGap = %1%", _lineGap);

//	log_debugp("Max Advances: %1%x%2%", face->available_sizes >> 6, face->max_advance_height >> 6);
//	log_debugp("Height = %1%", face->height >> 6);

	

	// Load Initial Set of Characters
	for (UInt32 i = 32; i < 128; ++i)
	{
		loadChar(face, i);
	}

	//loadChar(face, '8');

	//loadChar(face, 0x4E83);

	// Kill Font
	FT_Done_Face(face);

	// Kill Library
	FT_Done_FreeType(lib);

//	SOIL_save_image("test.bmp", SOIL_SAVE_TYPE_BMP, BMP_WIDTH, BMP_HEIGHT, 4, (const unsigned char*)&_bitmap[0][0]);



	return true;
}


/*

*/
Boolean Font::loadChar(const FT_Face & fontFace, ULong charCode)
{
	// Load the Glyph
	FT_Load_Glyph(fontFace, FT_Get_Char_Index(fontFace, charCode), FT_LOAD_DEFAULT);


	// TEMP
	// Dump Data to Textfile

	FT_Outline * outline = &fontFace->glyph->outline;

	// Setup Outline Decomposer
	FT_Outline_Funcs funcs;
	funcs.delta = 0;
	funcs.shift = 0;
	funcs.conic_to = conicTo;
	funcs.cubic_to = cubicTo;
	funcs.move_to = moveTo;
	funcs.line_to = lineTo;


	geometry::Polygon polygon;

	
//	log_infop("Glyph '%1%'", (Char)charCode);


	// Calculate Metrics
	_Character c(charCode);
	c.glyph.advance = (fontFace->glyph->metrics.horiAdvance >> 6) / GLYPH_METRIC_SCALE_FACTOR;
	c.glyph.bearing = glm::fvec2(fontFace->glyph->metrics.horiBearingX >> 6, fontFace->glyph->metrics.horiBearingY >> 6) / GLYPH_METRIC_SCALE_FACTOR;
	c.glyph.dimension = glm::fvec2(fontFace->glyph->metrics.width >> 6, fontFace->glyph->metrics.height >> 6) / GLYPH_METRIC_SCALE_FACTOR;

	// Dump Glyph Information
	//log_infop("- Dimension: %1%x%2%", c.glyph.dimension.x, c.glyph.dimension.y);
	//log_infop("- Bearing: %1%x%2%", c.glyph.dimension.x, c.glyph.dimension.y);
	//log_infop("- Advance: %1%", c.glyph.advance);



	// Decompose
	FT_Outline_Decompose(outline, &funcs, &polygon);

	// Set Geometry
	c.geometry = polygon.build(geometry::GeometryGenerate::Texture);

	// Build a Polygon
	_characters.insert({ charCode,  c});



	


	/*
		Bitmap
	*/
#if 0
	// Render the Glyph as a bitmap
	FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL);

	// Pointer to the Bitmap
	FT_Bitmap* pBitmap = &fontFace->glyph->bitmap;


//	log_infop("Glyph '%1%' Metrics", (Char)charCode);


	// Determine if the Font has vertical metrics
	FT_Long hasVerticalMetrics = FT_HAS_VERTICAL(fontFace);

	// >> 6 divides the values by 64

	_Glyph glyph(charCode);
	
	glyph.advance = fontFace->glyph->metrics.horiAdvance >> 6;
	
	glyph.bearing = glm::ivec2(fontFace->glyph->metrics.horiBearingX >> 6, fontFace->glyph->metrics.horiBearingY >> 6);

	glyph.dimension = glm::ivec2(fontFace->glyph->metrics.width >> 6, fontFace->glyph->metrics.height >> 6);

	// Dump Glyph Information
//	log_infop("- Dimension: %1%x%2%", glyph.dimension.x, glyph.dimension.y);
//	log_infop("- Bearing: %1%x%2%", glyph.dimension.x, glyph.dimension.y);
//	log_infop("- Advance: %1%", glyph.advance);

	// Dump Bitmap Information
//	log_infop("- Bitmap Dimensions: %1%x%2%", pBitmap->width, pBitmap->rows);

	// Copy the Bitmap to the Texture, with the appropriate offsets
	Int32 cols = 16;
	Int32 rows = 16;

	Int32 sprWidth = BMP_WIDTH / cols;
	Int32 sprHeight = BMP_HEIGHT / rows;

	Int32 xCell = (charCode % cols);
	Int32 yCell = (charCode / rows);

	Int32 xOff = xCell * sprWidth;
	Int32 yOff = yCell * sprHeight;


//	log_infop("- Grid Cell: %1%x%2%", xCell, yCell);
//	log_infop("- Bitmap Offset: %1%x%2%", xOff, yOff);


	for (Int32 h = 0; h < glyph.dimension.y; ++h)
	{
		Int32 y = h + yOff;
		for (Int32 w = 0; w < glyph.dimension.x; ++w)
		{
			Int32 x = w + xOff;

			Int32 index = h * glyph.dimension.x + w;
			UInt8 value = pBitmap->buffer[index];
			_bitmap[y][x] = 0xFF << 24 | value << 16 | value << 8 | value << 0;
		}
	}

#endif 


	return true;
}




/*

*/
Float Font::calcWidth(const std::string & string)
{
	return -1.0f;
}



#if 0
/*
	Get the Geometry for a character...
	TEMPORARY
*/
std::shared_ptr<Geometry> Font::getGeometry(ULong character)
{
	const auto & it = _characters.find(character);
	return it == _characters.end() ? nullptr : it->second.geometry;
}
#endif



/*

*/
void Font::drawText(const std::shared_ptr<andromeda::IShader> shader, const std::string & string, andromeda::MatrixStack & ms)
{
	assert(shader);
	assert(_texture);






	// If multiline rendering
	// Split the string into array divided by \n, \r, representing lines of text
	// Push Matrix
	// LOOP: call drawText() without the multiline flag ... after each call, multiply the matrix in the NEGATIVE y-direction by the character height
	// Pop Matrix
	// Do not Continue Function!

	if (string.find_first_of('\n') != std::string::npos)
	{
		std::vector<std::string> lines;

		// Remove Array Characters and split
		boost::split(lines, string, boost::is_any_of("\n"));

	

		for (const auto & s : lines)
		{
			drawText(shader, s, ms);


			// Update Matrix
			glm::mat4 m(1.0f);	// This needs to be based on the font-width & additional spacing

								// Translate Matrix
								// This is the fonts "lineGap" 
			m = glm::translate(m, glm::vec3(0.0f, -_lineGap, 0.0f));

			ms.multiply(m);
		}

	

		return;
	}

	// Push New Matrix
	ms.push();


	// If Justify is enabled....
	// [See android font class using in JEngine/Backlash]
	// This needs to split the string into lines that will fit into a specified region.
	// IF a Split occurs. Call drawText() again with multiline rendering enabled. Do not Continue Function
	// ELSE calculate the character-spacing required to correctly fit the text :)





	_texture->bind();

	//shader->



	for (const auto & c : string)
	{
		// Update the Model View Matrix
		shader->setUniform("u_modelview", ms.top());

		// Draw Character
		Float advance = drawCharacter(c);

		// Update Matrix
		glm::mat4 m(1.0f);	// This needs to be based on the font-width & additional spacing

		// Translate Matrix
		// The is the Characters "advance"
		m = glm::translate(m, glm::vec3(advance, 0.0f, 0.0f));

		ms.multiply(m);
	}

	// Push Old Matrix
	ms.pop();
}


/*

*/
Float Font::drawCharacter(ULong character)
{
	// Find Character
	const auto & it = _characters.find(character);

	// Validate Character
	if (it == _characters.end())
		return 0.0f;

	// Get Geometry
	_Character & c = it->second;

	// Render It
	if (c.geometry)
		c.geometry->render();

	return c.glyph.advance;
}