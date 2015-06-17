#include "test_event.h"


#include <Windows.h>


#include <andromeda/Engine/engine.h>
#include <andromeda/Events/event.h>
#include <andromeda/Events/event_manager.h>




struct EventTest
{
	std::string message;
};


aBoolean event_test1(EventTest & e)
{
	MessageBox(nullptr, e.message.c_str(), "Event Test 1", MB_OK);
	return true;
}

aBoolean event_test2(EventTest & e)
{
	MessageBox(nullptr, e.message.c_str(), "Event Test 2", MB_OK);
	return true;
}




class ITestListener
{
public:
	virtual aBoolean cb(EventTest & e) = 0;
};

class TestListener : public ITestListener
{
public:
	aBoolean cb(EventTest & e)
	{
		MessageBox(nullptr, e.message.c_str(), "Virtual Class Function", MB_OK);
		return true;
	}
};







void testEvent(andromeda::Engine * engine)
{

	/*
		Well holy fuck the event system works :D

		The EventManager is NOT a system module anymore, but a singleton!
	*/

	aInt32 eventId = 10;

	andromeda::EventManager * em = andromeda::EventManager::instance();//engine->getSystem<andromeda::EventManager>();
	em->registerEvent<EventTest>(eventId);

	em->bind<EventTest>(eventId, event_test1);

	aInt32 id = em->bind<EventTest>(eventId, event_test2);
	em->bind<EventTest>(eventId, [](EventTest& e){MessageBox(nullptr, e.message.c_str(), "Lambda Event", MB_OK); return true; });

	

	//ITestListener * itl = new TestListener();

	TestListener tl;
	em->bind<EventTest>(eventId, std::bind(&TestListener::cb, &tl, std::placeholders::_1));

	

	EventTest test;
	test.message = "This is a message!";
	em->dispatch<EventTest>(eventId, test);

	test.message = "Deleting some crap";
	em->unbind<EventTest>(eventId, id);
	em->dispatch<EventTest>(eventId, test);
}