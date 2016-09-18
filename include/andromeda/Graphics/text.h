#pragma once

#include <memory>
#include <string>
#include <list>

#include <andromeda/stddef.h>

#include <andromeda/Graphics/material.h>

namespace andromeda
{
	class FontGraphics;
	class FontAtlas;

	class ITexture;

	class Geometry;
	class Material;
	

	/*
		Text Renderer

		
	*/
	class Text
	{
	public:
		Text(const std::shared_ptr<FontGraphics> & font, const std::wstring & text);
		virtual ~Text();

		Boolean setText(const std::wstring & text);

		void render();

	private:

		// This needs a material...

		// Geometry
		std::shared_ptr<Geometry> _geometry;
		std::shared_ptr<ITexture> _texture;

		// Pointer to the Font
		std::weak_ptr<FontGraphics> _font;

		

		// String :: Set this up so an interface/listener setup can be used to make semi-dynamic text and this class automatically 
		// reflect changes to the string.
		std::wstring _text;
	};









	class TextSection
	{
	public:

		// Returns the "Advance" of the entire section of section
		virtual Float drawText() = 0;
	};



#
	class TextSectionStatic : public TextSection
	{
	public:


		Float drawText() override { return _advance; }

	private:
		// Width of the Geometry
		Float _width = 0.0f;		

		// Advance required for the next section : This includes the width + a slight offset from the last characters advance
		Float _advance = 0.0f;		
		std::shared_ptr<Geometry> _geometry;
	};




	template <typename T>
	class TextSectionReference : public TextSectionStatic
	{
	public:
		TextSectionReference(const T & t)
			: _ref(t)
			, _value(t)
		{

		}
		
		Float drawText() override
		{ 
			// Update Geometry
			if (_ref != _value)
			{ 
				//Convert to String. Update Geometry 
			}

			return TextSectionStatic::drawText();
		}

	private:
		const T & _ref;

		T _value;
	};




	/*
		Advanced Text Rendering

		This will be used for both dynamic and static text

		Unlike the above class (Text) ... sections should be divided by dynamic sections & into lines.
	*/
	class TextEx
	{
	public:
		TextEx(const std::shared_ptr<FontGraphics> & font);


		void render(){}

	private:
		// Material
		Material _material;

		std::weak_ptr<FontGraphics> _font;

		// Auxhiliary Texture
		std::shared_ptr<ITexture> _texture;

		// Sections of Text
		std::list<std::shared_ptr<TextSection>> _sections;
	};
}