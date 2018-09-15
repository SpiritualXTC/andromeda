#include "class.h"

using namespace andromeda;

ClassId andromeda::generate()
{
	static ClassId counter = 0;

	return ++counter;
}