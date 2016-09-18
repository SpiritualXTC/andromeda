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
			bp::object _namespace;
			bp::object _module;
			

			std::shared_ptr<PythonLib> _lib;
		};
	}
}
