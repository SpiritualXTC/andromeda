#include <andromeda/Graphics/font_atlas.h>

#include <cassert>

// Boost
#include <boost/algorithm/string.hpp>

// Andromeda
#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/texture.h>
#include <andromeda/Graphics/text.h>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>
#include <andromeda/Geometry/geometry_desc.h>


#include <andromeda/Utilities/font.h>


#include <andromeda/Utilities/image.h>
#include <andromeda/Utilities/log.h>




#include <andromeda/opengl.h>	//TEMP





/*
	This is a basic implementation :)

	TODO:
	Switch to a Volumetric Texture (Multiple Layers, to support more characters if it looks like it might be needed
*/


using namespace andromeda;

/*

*/
FontAtlas::FontAtlas(const std::shared_ptr<Font> & ft, UInt32 fontSize)
	: FontGraphics(ft, fontSize)
{
	// Resize the Image
	_image.resize(IMAGE_WIDTH, IMAGE_HEIGHT);

	// TODO: Setup an "Error" Character (Should be the First Character) :)
	// Inverting the '?' mark character might be OK.

	// Loads the "basic" ASCII character set :: It Doesn't cos 32-48 is extremely basic! lololol
	loadCharacter(32, 48);

	// Create the Geometry
	createBuffers();

	// Updates the Texture
	updateBuffers();
}



/*

*/
Boolean FontAtlas::splitText(const std::wstring & text, std::vector<std::wstring> & lines)
{
	// Remove Array Characters and split
	boost::split(lines, text, boost::is_any_of("\n"));

	return true;
}



/*

*/
void FontAtlas::createBuffers()
{
	// Create Vertex Buffer
	_vb = andromeda::graphics()->createVertexBuffer();

	/*
		TODO:
		Move Geometry Declarations to the OpenGL Sub Library
		Remove the GL-centric enums.
	*/
	_desc = std::make_shared<GeometryDescription>(GL_TRIANGLE_STRIP, 4, 6, GL_UNSIGNED_INT);

	_desc->addDeclaration(3, GL_FLOAT, sizeof(Float) * 3, GeometryLocation::Position);
	_desc->addDeclaration(2, GL_FLOAT, sizeof(Float) * 2, GeometryLocation::Texture0);

	// Create the Texture
	_texture = graphics()->createTexture(IMAGE_WIDTH, IMAGE_HEIGHT);
}


/*
	addGeometry():

	Adds geometry to the standard vertex buffer used by the FontAtlas
*/
void FontAtlas::addGeometry(const _Character & ch)
{
	addGeometry(ch, _vertices, 0.0f, 0.0f);
}


/*
	addGeometry():

	Adds geometry to any vertex buffer
*/
void FontAtlas::addGeometry(const _Character & ch, std::vector<Float> & verts, Float offX, Float offY)
{
	Float tu0 = ch.offset.x / (Float)IMAGE_WIDTH;
	Float tv0 = ch.offset.y / (Float)IMAGE_HEIGHT;

	Float tu1 = (ch.offset.x + ch.dimensions.x) / (Float)IMAGE_WIDTH;
	Float tv1 = (ch.offset.y + ch.dimensions.y) / (Float)IMAGE_HEIGHT;


	Float w = ch.metrics.width / FONT_SCALE;
	Float h = ch.metrics.height / FONT_SCALE;
	Float x0 = ch.metrics.hori.bearingX / FONT_SCALE;
	Float y0 = ch.metrics.hori.bearingY / FONT_SCALE;
	Float x1 = x0 + w;
	Float y1 = y0 - h;

	glm::vec3 pos[] = {
		{ x0, y0, 0.0f },
		{ x0, y1, 0.0f },
		{ x1, y0, 0.0f },
		{ x1, y1, 0.0f }
	};

	glm::vec2 tex[] = {
		{ tu0, tv0 },
		{ tu0, tv1 },
		{ tu1, tv0 },
		{ tu1, tv1 }
	};


	for (UInt32 i = 0; i < 4; ++i)
	{
		// Position
		verts.insert(verts.end(), { pos[i].x + offX, pos[i].y + offY, pos[i].z });

		// Texture
		verts.insert(verts.end(), { tex[i].x, tex[i].y });
	}
}


/*
	loadChar():

	Loads the character into teh FontAtlas
*/
UInt32 FontAtlas::loadChar(const GlyphMetric & metric)
{
	const std::shared_ptr<Font> & ff = getFont();

	// Get Image 
	ImageData<UInt8> charImage;
	ff->getCharacterBitmap(metric.charCode, charImage);

	UInt32 index = _characters.size();

	// Setup Character
	_Character c;

#if 0
	// Assign Metrics
	//metric.hori.advance * XYZ;
	c.metrics.advance = (Float)metric.hori.advance;
	c.metrics.bearingX = (Float)metric.hori.bearingX;
	c.metrics.bearingY = (Float)metric.hori.bearingY;
	c.metrics.width = (Float)metric.width;
	c.metrics.height = (Float)metric.height;
#else
	c.metrics = metric;
#endif

	// Set Character Dimensions [Pixels]
	c.dimensions = glm::ivec2(charImage.width, charImage.height);

	// Set the Vertex Offset for the Character
	c.vertexOffset = 4 * _characters.size();

	// Get Next Texture Coordinate
	getNextTextureCoordinate(c.dimensions, c.offset);

#if 0
	log_infop("Character: %1% - '%2%'", metric.charCode, (Char)metric.charCode);
	log_tree();
	log_infop("Advance = %1%", metric.hori.advance);
	log_infop("Bearing = %1%x%2%", c.metrics.bearingX, c.metrics.bearingY);
	log_infop("Char Dimension = %1%x%2%", c.metrics.width, c.metrics.height);

	log_infop("Texture Dimension = %1%x%2%", c.dimensions.x, c.dimensions.y);
	log_infop("Texture Offset = %1%x%2%", c.offset.x, c.offset.y);
#endif

	// Update the Image
	_image.blit(c.offset.x, c.offset.y, charImage);

	// Update the Geometry
	addGeometry(c);

	// Add to Character List
	_characters.push_back(c);

	// Update Texture
	updateBuffers();

	return index;
}


/*

*/
Boolean FontAtlas::getNextTextureCoordinate(const glm::ivec2 & dimensions, glm::ivec2 & texCoord)
{
	// Calculate Texture Offset [This uses a basic "fitting" method]
	// Which is more or less, look at the last added character... can i still fit after it? yes or no?
	// Keep it Simple Stupid :)
	if (_characters.size() != 0)
	{
		const _Character & last = _characters.back();

		// Is their remaining space to fit this character on the texture ???
		if (last.offset.x + last.dimensions.x + dimensions.x < IMAGE_WIDTH)
		{
			// Offset for this character is immediately after the last character - shares the same Y-Offset
			texCoord = glm::ivec2(last.offset.x + last.dimensions.x, last.offset.y);
		}
		else
		{
			// TODO: Determine how far to drop the character.
			// For now just use the line spacing
			// Might be _font->getHeight() * FONT_SCALE	:: Test later
			Int32 drop = getLineSpacing();
			texCoord = glm::ivec2(0, drop);
		}
	}
	else
		texCoord = glm::ivec2(0, 0);

	return true;
}






/*

*/
void FontAtlas::updateBuffers()
{
	// Don't attempt to update texture unless it exists
	// This allows the first set of characters to be cached
	// without updating the texture every time a character is created
	if (_texture)
		_texture->data((UInt8*)_image.data());

	if (_vb)
		_vb->data((void*)_vertices.data(), _vertices.size() * sizeof(Float));
}




/*

*/
Boolean FontAtlas::begin()
{
	// Bind VB/IB
	if (_vb)
		_vb->bind();

	if (_desc)
		_desc->begin();

	// Bind Texture
	if (_texture)
		_texture->bind(0);

	return true;
}


/*

*/
Boolean FontAtlas::end()
{
	// Unbind Texture
	if (_texture)
		_texture->unbind(0);

	// Unbind Desc
	if (_desc)
		_desc->end();

	// Unbind VB/IB
	if (_vb)
		_vb->unbind();

	return true;
}













/*
	Some of this code could be moved to IFont (the parent class)
*/
std::shared_ptr<Geometry> FontAtlas::generateText(const std::wstring & string)
{
	/*
		TODO: Version 2.

		Split text by dividing static and dynamic parts apart (Boost format %argIndex%)

		Each Static Section needs to be parsed here, each one starting from (0, 0)
			When drawing the section will be offset based on previous sections
		Each Dynamic Section needs to have a converter from T to string, and each character drawn individually *


		* This is the simplest route for dynamic text -- however change tracking could be implemented on the variables value
		  If it changes, then update a geometry object as though it was static, this way dynamic text can be treated the same as static, including some level of optimsation
		  However some dynamic text is bound to change EVERY frame in which case it may be better to just draw it direct.
	*/


	std::vector<std::wstring> lines;

	std::vector<Float> vertices;
	std::vector<UInt32> indices;
	
	UInt32 index[] = { 0, 1, 2, 2, 1, 3 };

	log_warnp("Generate Static Text");
	log_tree();

	


	// Split text
	if (!splitText(string, lines))
		return false;


	Float offsetX = 0.0f;
	Float offsetY = 0.0f;
	UInt32 offsetIndex = 0;

	// Loop through Lines
	for (const auto & line : lines)
	{
		// Loop Through Characters
		for (const auto & ch : line)
		{
			UInt32 charIndex = mapIndex(ch);

			if (charIndex >= _characters.size())
				continue;

			_Character & c = _characters[charIndex];

			// Add Vertices
			addGeometry(c, vertices, offsetX, offsetY);
				
			// Add Indices
			for (UInt32 i = 0; i < 6; ++i)
			{
				UInt32 val = index[i] + offsetIndex;
				indices.push_back(val);
			}
			
			// Advance
			offsetX += c.metrics.hori.advance / FONT_SCALE;
			offsetIndex += 4;
		}

		// Reset X, Adjust Line Spacing
		offsetX = 0.0f;
		offsetY -= getLineSpacing() / FONT_SCALE;
	}

	log_debugp("Vertices Generated = %1%", vertices.size());
	log_debugp("Indices Generated = %1%", indices.size());


	// Create Buffers
	std::shared_ptr<VertexBuffer> vb = andromeda::graphics()->createVertexBuffer();
	std::shared_ptr<IndexBuffer> ib = andromeda::graphics()->createIndexBuffer();

	vb->data((void*)vertices.data(), vertices.size() * sizeof(Float));
	ib->data(indices.data(), indices.size() * sizeof(UInt32));

	// Create Declaration :: Doing here, as the 2nd set of texture coords could be built-in
	std::shared_ptr<GeometryDescription> desc = std::make_shared<GeometryDescription>(GL_TRIANGLES, vertices.size(), indices.size(), GL_UNSIGNED_INT);

	desc->addDeclaration(3, GL_FLOAT, sizeof(Float) * 3, GeometryLocation::Position);
	desc->addDeclaration(2, GL_FLOAT, sizeof(Float) * 2, GeometryLocation::Texture0);

	return std::make_shared<Geometry>(vb, desc, ib);;
}





#if 0
/*

*/
Float FontAtlas::drawCharacter(const std::shared_ptr<andromeda::IShader> shader, UInt32 charCode)
{
	UInt32 index = mapIndex(charCode);

	if (index >= _characters.size())
		return 0.0f;

	_Character & c = _characters[index];



	glDrawArrays(_desc->mode(), c.vertexOffset, _desc->vertices());



	return c.metrics.advance / FONT_SCALE;
}
#endif