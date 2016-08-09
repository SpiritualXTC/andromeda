#pragma once

#include <memory>
#include <string>

#include <andromeda/stddef.h>

#include <andromeda/Graphics/material.h>

namespace andromeda
{
	class IFont;
	class ITexture;

	class Geometry;
	class Material;
	

	/*
		Precache for static text
	*/
	class Text
	{
	public:
		Text(const std::shared_ptr<IFont> & font, const std::wstring & text);
		virtual ~Text();

		Boolean setText(const std::wstring & text);

		void render();

	private:

		// Geometry
		std::shared_ptr<Geometry> _geometry;
		std::shared_ptr<ITexture> _texture;

		// Pointer to the Font
		std::weak_ptr<IFont> _font;

		

		// String :: Set this up so an interface/listener setup can be used to make semi-dynamic text and this class automatically 
		// reflect changes to the string.
		std::wstring _text;
	};
}