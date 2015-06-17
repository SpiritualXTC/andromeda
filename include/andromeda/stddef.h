#ifndef _ANDROMEDA_STDDEF_H_
#define _ANDROMEDA_STDDEF_H_

/*
	Standard Include File for all of Andromeda
*/




// Boost
#include <boost/cstdint.hpp>


namespace andromeda
{
	/*
		Standard Types
	*/
	typedef short Short;
	typedef int Int;
	typedef long Long;

	typedef unsigned short UShort;
	typedef unsigned int UInt;
	typedef unsigned long ULong;



	typedef float Float, Float32;
	typedef double Double, Float64;

	typedef bool Bool, Boolean;
	typedef char Char;
	typedef unsigned char Byte;


	/*
		Fixed Width Integers
	*/
	typedef boost::int8_t Int8;
	typedef boost::int16_t Int16;
	typedef boost::int32_t Int32;
	typedef boost::int64_t Int64;

	typedef boost::uint8_t UInt8;
	typedef boost::uint16_t UInt16;
	typedef boost::uint32_t UInt32;
	typedef boost::uint64_t UInt64;



	/*
		Special Types
	*/
	typedef size_t Size;
	typedef errno_t Error;
}



/*
	Standard Types
*/
typedef andromeda::Boolean aBoolean, aBool;
typedef andromeda::Char aChar;
typedef andromeda::Byte aByte;

typedef andromeda::Float aFloat, aFloat32;
typedef andromeda::Double aDouble, aFloat64;

typedef andromeda::Short aShort;
typedef andromeda::Int aInt;
typedef andromeda::Long aLong;

typedef andromeda::UShort aUShort;
typedef andromeda::UInt aUInt;
typedef andromeda::ULong aULong;


/*
	Fixed Width Integers
*/
typedef andromeda::Int8 aInt8;
typedef andromeda::Int16 aInt16;
typedef andromeda::Int32 aInt32;
typedef andromeda::Int64 aInt64;

typedef andromeda::UInt8 aUInt8;
typedef andromeda::UInt16 aUInt16;
typedef andromeda::UInt32 aUInt32;
typedef andromeda::UInt64 aUInt64;


/*
	Special Types
*/
typedef andromeda::Size aSize;
typedef andromeda::Error aError;




#endif