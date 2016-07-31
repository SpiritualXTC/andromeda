#pragma once




namespace andromeda
{
	/*
		TODO: These should return a template value :P
	*/
	template <typename T>
	inline UInt32 image_format_convert(T & value)
	{
		return t;
	}






	/*
		Convert Grayscale to ARGB
	*/
	template <>
	inline UInt32 image_format_convert<UInt8>(UInt8 & value)
	{
		return value << 24 | 0xFFFFFF;
		//return value << 24 | value << 16 | value << 8 | value << 0;
	}
}
