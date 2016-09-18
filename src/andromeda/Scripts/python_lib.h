#pragma once

#include <andromeda/stddef.h>

#include <andromeda/Utilities/library.h>

/*
	Initialises / Destroys the Python Interpreter
*/

#include <boost/python.hpp>

namespace andromeda
{
	namespace python
	{
		/*
			Python Library
		*/
		class PythonLib : public Library<PythonLib>
		{
		public:
			PythonLib();
			virtual ~PythonLib();


			// TEMPORARY IMPL
			PyThreadState * getState() { return _state; }

		private:
			PyThreadState * _state = nullptr;
		};


		/*
		
		*/
		class PythonLock
		{
		public:
			PythonLock(PyThreadState * state);
			virtual ~PythonLock();

		private:
			PyGILState_STATE _state;
		};
	}
}