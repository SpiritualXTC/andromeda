

#include <iostream>
#include <boost/shared_ptr.hpp>

#if defined(WIN32)
#include <Windows.h>
#include <conio.h>
#endif

#include <common/log.h>
#include <common/class.h>

#include "app/app.h"

using namespace andromeda;



/*
	TODO: Setup primitive testing environment :)
*/

// Debug Console
#if defined(_DEBUG)
#define LOCK_CONSOLE
// Uncomment this to immediately quit on exit :)
//#undef LOCK_CONSOLE
#endif


class LogDump : public andromeda::Log::Observer
{
public:
	void notify(const andromeda::Log * const logger, const andromeda::LogMessage& msg) override
	{
		std::cout << msg.message << std::endl;
	}

private:
};





class Test1
{
};
class Test2
{
};
class Test3
{
};

class Test4 : virtual public Test3, virtual public Test2
{

};




void logTest()
{
	LogDump dump;

	Log::instance()->addObserver(&dump);
	Log::instance()->log(andromeda::Log::Verbose, "LogTest(): random text printed twice");

	// Dump is automatically removed
//	Log::instance()->removeObserver(&dump);
}



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

int main()
{
	// Set Exit Handler
	atexit(exit);






	andromeda::Log::instance();

	LogDump logger;
	Log::instance()->addObserver(&logger);
	Log::instance()->log(andromeda::Log::Verbose, "main(): random text");

	logTest();

	Log::instance()->log(andromeda::Log::Verbose, "main(): random text printed once");

	Test4 t;

	log_debug("Template Tests");
	log_debugp("ID = %d", IClass<Test1>::id());
	log_debugp("ID = %d", IClass<Test2>::id());
	log_debugp("ID = %d", IClass<Test3>::id());
	log_debugp("ID = %d", IClass<Test4>::id());
	log_debugp("ID = %d", IClass<int>::id());
	log_debugp("ID = %d", IClass<Test3>::id());
	


	std::shared_ptr<App> app = std::make_shared<App>(nullptr);
	
	// TODO: Set System Level Event Handlers
	app->run();

	// Force Shutdown
	app.reset();

	log_infop("Press any key to Continue...");
	Log::instance()->removeObserver(&logger);

	Log::instance()->log(andromeda::Log::Verbose, "main(): text that should never appear");

	return 0;
}