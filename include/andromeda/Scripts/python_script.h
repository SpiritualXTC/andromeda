#pragma once

/*
	An Abstraction layer would be handy here :)

	IF only so <boost/python.hpp> doesn't expose the entire python library to anything that includes this file
*/


#include <andromeda/stddef.h>

// Boost
#include <boost/python.hpp>



namespace bp = boost::python;

namespace andromeda
{
	namespace python
	{
		class PythonLib;

		class PythonScript
		{
		public:
			PythonScript();
			virtual ~PythonScript();

		private:
			// Leave this as being the first property ... 
			// Makes it call the destructor last ... 
			// Deal with a fix later :)
			std::shared_ptr<PythonLib> _lib;



			bp::object _namespace;
			bp::object _module;
		};
	}
}
