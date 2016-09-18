
#include <fstream>
#include <iostream>

#include <Windows.h>
#include <conio.h>



#include <andromeda/andromeda.h>
#include <andromeda/andromeda_init.h>

#include <andromeda/graphics.h>
#include <andromeda/IO/file_queue.h>
#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>


#include "app.h"
#include "console.h"

// Libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")	// glErrorString(...) uses this library :: tesselation probably does as well.
#pragma comment(lib, "glew32.lib")	// glew32s.lib for the static library - which for unknown reasons has decided to stop linking correctly! Go Figure!
#pragma comment(lib, "soil.lib")

#pragma comment(lib, "assimp-vc130-mtd.lib")
#pragma comment(lib, "freetype240MT_D.lib")

#pragma comment(lib, "andromeda.lib")





// Boost Auto Links its libraries?? 




// Debug Console
#if defined(_DEBUG)
#define LOCK_CONSOLE
// Uncomment this to immediately quit on exit :)
//#undef LOCK_CONSOLE
#endif


/*
	Quit Handler
*/
void exit()
{
#if defined(LOCK_CONSOLE)
	// Everything else will be out of scope by now :P
	// Including the fucking logger & console.
	//std::cout << "\n\nPress any Key to Continue:";
	_getch();
#endif
}



/*
	Prints a Header
*/
void printHeader(std::shared_ptr<Console> console)
{
	std::string contents = andromeda::LoadFile("../res/andromeda.txt");

	console->print(contents);
}


#include <boost/regex.hpp>



void test(const glm::vec2 & v0, const glm::vec2 & v1, const glm::vec2 & c)
{
	glm::vec2 s0 = v1 - v0;
	glm::vec2 s1 = c - v0;

	aFloat dot = glm::dot(s0, s1);
	aFloat cross = s0.x * s1.y - s0.y * s1.x;

	log_debugp("V0 = (%1%, %2%)", v0.x, v0.y);
	log_debugp("V1 = (%1%, %2%)", v1.x, v1.y);
	log_debugp("C  = (%1%, %2%)", c.x, c.y);
	log_debugp("Dot = %1%", dot);
	log_debugp("Cross = %1%", cross);
}







#include <andromeda/Resources2/resource_factory.h>


/*
	The new resource engine :: Testing Phase
*/
void configResourcesV2(andromeda::ResourceFactory * rf)
{
	log_debugp("New Resource Engine");
	
	// Create Builders :: This needs to be done by the engine, however the resource management could be extended to include
	// custom resource types, these will need to be managed by the application
	


	/*
		TODO:
		Resource Setup will need to happen by the application.

		The ResourceFactory is going to have a system for preloading a set of resources, 
		with a callback when they are all done.

		andromeda::Application 
		can extend this interface -- this will allow global resources to be loaded in straight away with a loading screen -- automatically

		"Scenes" could also extend the interface
	*/



	// Load Resource XML :: This call needs to be done by the application
	rf->loadResources("../res", "resources.xml");

	// Load Packaged Files! (Loop through all .pak/.zip/.whatever files in ../res/)
}




#include <andromeda/Game/game_object.h>
#include <andromeda/Renderer/scene_graph_hierarchy.h>

void itSG(andromeda::SceneGraphNode * sg)
{
	using namespace andromeda;
	
	log_tree();
	
	for (auto & it : *sg)
	{
		const std::shared_ptr<andromeda::GameObject>  & go = it->getObject();

		if (go)
			log_verbosep("Object = %1%", go->getName());
		else
			log_verbosep("Object is probably root");

		itSG(it.get());
	}
}


void testSG()
{
	// Test the SceneGraph
	log_warn("Scene Graph Test");
	log_verbose("---------------------------------------------");

	andromeda::SceneGraphHierarchy sgh;

	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go1"));
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go2"));
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go3"));
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go4"));
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go5"));


	itSG(&sgh);
	log_verbose("---------------------------------------------");

	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go1"));	// should fail.
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go21"), "go2");
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go22"), "go2");
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go31"), "go3");
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go32"), "go3");

	itSG(&sgh);
	log_verbose("---------------------------------------------");

	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go321"), "go32");
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go322"), "go32");

	itSG(&sgh);
	log_verbose("---------------------------------------------");	

	sgh.removeGameObject("go32");
	sgh.removeGameObject("go21");
	
	itSG(&sgh);
	log_verbose("---------------------------------------------");

	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go32"), "go3");
	sgh.addGameObject(std::make_shared<andromeda::GameObject>("go21"), "go2");

	itSG(&sgh);
	log_verbose("---------------------------------------------");



	log_warn("End Scene Graph Tests");
}




#include <andromeda/Scripts/python_script.h>
/*
	do actual python tests
*/
void doTestPython()
{
	andromeda::python::PythonScript ps;

}


/*
	test python:
	using the aux function due to destructer logic :P
*/
void testPython()
{
	log_warn("Python Scripting Test");
	log_verbose("---------------------------------------------");

#if 0
	doTestPython();
#endif


	
	log_verbose("---------------------------------------------");
	log_warn("Python Scripting Test");
}



/*

*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Set Exit Handler
	atexit(exit);

	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);


	// Create Log
	andromeda::Log::instance();

#if defined(_DEBUG) && defined(_WIN32)
	// Create the Console Output
	std::shared_ptr<Console> console = std::make_shared<Console>();

	// Print the Header to Console
	printHeader(console);
#endif
	

	// Create Engine
	log_debug("main() :: Initialising Engine");

	// Initialise the Engine
	andromeda::initialise(hInstance);


	// Resource Management
	configResourcesV2(andromeda::resourceFactory().get());



	// Test the File Queue
	//andromeda::FileQueue fq;
	//fq.start();



	// Create Application!
	std::shared_ptr<andromeda::Application> app = std::make_shared<App>();


	// TODO: Remove Meh
	testSG();
	testPython();


	// Run Engine
	andromeda::run(app);
	
	log_debug("main() :: Destroying Engine");

	// Destroy the Engine
	andromeda::destroy();

	log_debug("main() :: Fin");

#if 0
	fq.loadFile("test1.png", true, nullptr, nullptr);
	fq.loadFile("test2.png", true, nullptr, nullptr);
	fq.loadFile("test3.png", true, nullptr, nullptr);
	fq.loadFile("test4.png", true, nullptr, nullptr);
	fq.loadFile("test5.png", true, nullptr, nullptr);
	fq.loadFile("test6.png", true, nullptr, nullptr);
	fq.loadFile("test7.png", true, nullptr, nullptr);

	// TEMP
	std::this_thread::sleep_for(std::chrono::seconds(1));

	fq.stop();
#endif

	return 0;
}














