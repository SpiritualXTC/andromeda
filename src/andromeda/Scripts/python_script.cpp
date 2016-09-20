#include <andromeda/Scripts/python_script.h>


#include <andromeda/Scripts/python_lib.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::python;



#if 0
struct PyTest
{
	void test_python()
	{
		log_err("c++ function called by python embedded in c++");
	}
};
#endif

/*

*/
PythonScript::PythonScript()
{
	// Initialise the PythonLibrary :: If its not.
	_lib = PythonLib::loadLibrary();


	log_verbose("Python Script Initialised");




	PythonLock lock(_lib->getState());
	_module = bp::import("__main__");

	_namespace = _module.attr("__dict__");

//	ns["test"] = bp::class_<PyTest, boost::shared_ptr<PyTest>>("PyTest")
//		.def("test", &PyTest::test_python);
}


/*

*/
PythonScript::~PythonScript()
{
	PythonLock lock(_lib->getState());

	log_verbose("Python Script Destroyed");
}
