#include <andromeda/Graphics/font_atlas.h>

//#include <andromeda/glm.h>

#include <andromeda/Graphics/buffer.h>
#include <andromeda/Graphics/texture.h>

#include <andromeda/Geometry/geometry.h>
#include <andromeda/Geometry/geometry_builder.h>
#include <andromeda/Geometry/geometry_desc.h>


#include <andromeda/Resources/font_resource.h>


#include <andromeda/Utilities/image.h>


#include <andromeda/Utilities/log.h>

#include <andromeda/andromeda.h>	//TEMP

/*
	This is a basic implementation :)

	TODO:
	Switch to a Volumetric Texture (Multiple Layers, to support more characters
*/


using namespace andromeda;

/*

*/
FontAtlas::FontAtlas(const std::shared_ptr<FontFace> & ft, UInt32 fontSize)
	: IFont(ft, fontSize)
{
	
	// Resize the Image
	_image.resize(IMAGE_WIDTH, IMAGE_HEIGHT);


	//
	//_texture = andromeda::LoadResource<andromeda::Texture>("pattern0.png");



	// Setup an "Error" Character (Should be the First Character) :)

	// Loads the "basic" ASCII character set
	loadCharacter(32, 48);



	// Create the Geometry
	createBuffers();

	// setup temporary geometry
//	addGeometry();

	// Updates the Texture
	updateBuffers();
}



/*

*/
void FontAtlas::createBuffers()
{
	// Create Vertex Buffer
	_vb = std::make_shared<VertexBuffer>();

	/*
		TODO:
		Remove the GL-centric enums.
	*/
	_desc = std::make_shared<GeometryDescription>(GL_TRIANGLE_STRIP, 4, 6, GL_UNSIGNED_INT);

	_desc->addDeclaration(3, GL_FLOAT, sizeof(Float) * 3, GeometryLocation::Position);
	_desc->addDeclaration(2, GL_FLOAT, sizeof(Float) * 2, GeometryLocation::Texture0);

	// Create the Texture
	_texture = std::make_shared<Texture>(IMAGE_WIDTH, IMAGE_HEIGHT);
}


/*
	TODO:
	This will needs to know:
	a) The Glyph Metrics (So Vertex and Texture Data can be calculated properly)
	b) The Location in the Texture (So Texture Data can be offset to the correct spot)
	c)
*/
void FontAtlas::addGeometry(const _Character & ch)
{
	/*
		Requires:
		Texture offset.
		Texture dimensions
	*/

	Float tu0 = ch.offset.x / (Float)IMAGE_WIDTH;
	Float tv0 = ch.offset.y / (Float)IMAGE_HEIGHT;

	Float tu1 = (ch.offset.x + ch.dimensions.x) / (Float)IMAGE_WIDTH;
	Float tv1 = (ch.offset.y + ch.dimensions.y) / (Float)IMAGE_HEIGHT;


	Float w = ch.metrics.width / FONT_SCALE;
	Float h = ch.metrics.height / FONT_SCALE;
	Float x0 = ch.metrics.bearingX / FONT_SCALE;
	Float y0 = ch.metrics.bearingY / FONT_SCALE;
	Float x1 = x0 + w;
	Float y1 = y0 - h;

	glm::vec3 verts[] = {
		{x0, y0, 0.0f},
		{x1, y0, 0.0f},
		{x0, y1, 0.0f},
		{x1, y1, 0.0f}
	};

	glm::vec2 tex[] = {
		{tu0, tv0},
		{tu1, tv0},
		{tu0, tv1},
		{tu1, tv1}
	};


	for (UInt32 i = 0; i < 4; ++i)
	{
		// Position
		//_vertices.push_back(verts[i].x);
		_vertices.insert(_vertices.end(), { verts[i].x, verts[i].y, verts[i].z });

		// Texture
		_vertices.insert(_vertices.end(), { tex[i].x, tex[i].y });
	}


}


/*

*/
UInt32 FontAtlas::loadChar(const GlyphMetric & metric)
{
	const std::shared_ptr<FontFace> & ff = getFontFace();

	// Get Image 
	ImageData<UInt8> charImage;
	ff->getCharacterBitmap(metric.charCode, charImage);

	UInt32 index = _characters.size();

	// Setup Character
	_Character c;

	// Assign Metrics
	//metric.hori.advance * XYZ;
	c.metrics.advance = metric.hori.advance;
	c.metrics.bearingX = metric.hori.bearingX;
	c.metrics.bearingY = metric.hori.bearingY;
	c.metrics.width = metric.width;
	c.metrics.height = metric.height;
	
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
	_image.draw(c.offset.x, c.offset.y, charImage);

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
	// Calculate Texture Offset [This needs to use a "fitting" method]
	// Which is more or less, look at the last added character... can i still fit after it? yes or no?
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
		_texture->bind();

	return true;
}


/*

*/
Boolean FontAtlas::end()
{
	// Unbind Texture
	if (_texture)
		_texture->unbind();

	// Unbind Desc
	if (_desc)
		_desc->end();

	// Unbind VB/IB
	if (_vb)
		_vb->unbind();

	return true;
}






/*

*/
Float FontAtlas::drawCharacter(const std::shared_ptr<andromeda::IShader> shader, UInt32 charCode)
{
	UInt32 index = mapIndex(charCode);

	if (index >= _characters.size())
		return 0.0f;

	_Character & c = _characters[index];

	// Set Sprite/Texture Coordinate Information for the Character
	// This wont need to be done :)


	/*
		TODO:
		This needs to be updated :)

		The Index part should essentially be:
		Number drawn = 4;
		Offset = 4 * index
	*/
	glDrawArrays(_desc->mode(), c.vertexOffset, _desc->vertices());

	

	return c.metrics.advance / FONT_SCALE;
}