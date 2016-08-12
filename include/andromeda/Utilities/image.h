#pragma once

#include <memory>
#include <string>

#include <andromeda/stddef.h>

#include <cimg/CImg.h>

#include "Image/image_convert.h"

namespace andromeda
{
	// Forward Declaration
	class File;


	/*
		TODO:
		Add a format enum class
	*/


	enum class ImageFormat
	{
		RGBA,
		Grayscale,
	};






	/*
		Basic Image Information
	*/
	template <typename T>
	struct ImageData
	{
		UInt32 width = 0;
		UInt32 height = 0;
		UInt32 channels = 4;

		T * image = nullptr;
	};




	







	/*
		Data for an Image

		This really primitive for now :)
	*/
	class Image
	{
	public:
		static std::shared_ptr<Image> LoadImageFromFile(const std::string & filename);
		static std::shared_ptr<Image> LoadImageFromMemory(const File * file);

	public:
		Image()
		{
			_width = 0;
			_height = 0;
		}
		Image(Int32 w, Int32 h)
		{
			resize(w, h);
		}
		Image(Int32 w, Int32 h, UInt32 * ptr, UInt32 size)
		{
			resize(w, h, ptr, size);
		}

		

		virtual ~Image()
		{
			empty();
		}

		const Int32 width() const { return _width; }
		const Int32 height() const { return _height; }
	//	const UInt32 channels() const { return _channels; }

		const UInt32 * data() const { return _data; }

		Boolean empty()
		{
			// Deallocate
			if (_data)
				delete[] _data;
			_data = nullptr;

			return true;
		}

		/*
		
		*/
		Boolean resize(Int32 w, Int32 h)
		{
			assert(w > 0);
			assert(h > 0);

			// Clear Image
			empty();

			// Set Dimensions
			_width = w;
			_height = h;

			// Allocate
			_data = new UInt32[_width * _height];

			return !!_data;
		}


		/*
		
		*/
		Boolean resize(Int32 w, Int32 h, UInt32 * ptr, UInt32 size)
		{
			Boolean result = true;
			
			// Clear Image
			result = resize(w, h);
			
			// Copy
			for (UInt32 i = 0; i < size; ++i)
				_data[i] = ptr[i];

			return result;
		}



		/*
			TODO:
			Rename to blit
		*/
		template <typename _T>
		Boolean blit(Int32 offsetX, Int32 offsetY, const ImageData<_T> & image)
		{
			// "Draw" Image to Texture Data
			// This shouldn't be here :)
			for (Int32 y = 0; y < (Int32)image.height; ++y)
			{
				// Out of Range :: Pre
				if (y + offsetY < 0) continue;

				// Out of Range :: Post
				if (y + offsetY >= _height) break;

				for (Int32 x = 0; x < (Int32)image.width; ++x)
				{
					// Out of Range :: Pre
					if (x + offsetX < 0) continue;

					// Out of Range :: Post
					if (x + offsetX >= _width) break;

					UInt32 pixel_source = y * image.width + x;
					UInt32 pixel_dest = (y + offsetY) * _width + (x + offsetX);

					// Convert
					UInt32 value = image_format_convert<_T>(image.image[pixel_source]);

					// Assign Pixel
					_data[pixel_dest] = value;
				}
			}
			return true;
		}

	private:
		Int32 _width = 0;
		Int32 _height = 0;
		//UInt32 _channels = 4;

		UInt32 * _data = nullptr;
	};






}