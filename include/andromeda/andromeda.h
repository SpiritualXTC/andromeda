#ifndef _ANDROMEDA_ANDROMEDA_H_
#define _ANDROMEDA_ANDROMEDA_H_

#include <memory>

// Boost
#include <boost/predef.h>


// Andromeda
#include "stddef.h"



#if BOOST_OS_WINDOWS
#include <Windows.h>
#endif

namespace andromeda
{
	// Forward Declarations
	class Engine;


	/*
		Namespace Functionality :)
	*/



	/* Initialise */
#if BOOST_OS_WINDOWS
	std::unique_ptr<Engine> initialise(HINSTANCE hInstance);
#endif

}



#endif