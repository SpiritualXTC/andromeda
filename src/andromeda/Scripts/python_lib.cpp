#include "python_lib.h"

// Boost
#include <boost/python.hpp>

// Andromeda
#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::python;



/*

*/
PythonLib::PythonLib()
{
	log_verbose("Python Library Initialised");

	// Initialise Python
	Py_Initialize();

	_state = PyEval_SaveThread();
}


/*

*/
PythonLib::~PythonLib()
{
	PyEval_RestoreThread(_state);

	PyGILState_STATE gs = PyGILState_Ensure();

	// Finalize Python
	Py_Finalize();

//	PyGILState_Release(gs);

	log_verbose("Python Library Destroyed");
}




PythonLock::PythonLock(PyThreadState * state)
{
	PyEval_RestoreThread(state);

	_state = PyGILState_Ensure();
}

PythonLock::~PythonLock()
{
	PyGILState_Release(_state);
}


