#pragma once

#if _DEBUG
#include <iostream>

// TODO: Add some additional stuff to the output, such as file or debug, etc
#define debug(m) (std::cout << ">" << (m) << std::endl)
#else

// Empty Macros. Compiler will optimise out :)

#define debug(m) ()

#endif
