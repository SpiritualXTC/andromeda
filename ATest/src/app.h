#ifndef _APP_H_
#define _APP_H_

#include <memory>

#include <andromeda/stddef.h>


// Forward Declarations
namespace andromeda
{
	class Engine;

	struct CloseEventArgs;
	struct ResizeEventArgs;
	struct KeyEventArgs;
}



/*

*/
class App
{
public:
	App(std::unique_ptr<andromeda::Engine> engine);
	virtual ~App();


	void run();

protected:
	aBoolean close(andromeda::CloseEventArgs & e);
	aBoolean resize(andromeda::ResizeEventArgs & e);

	aBoolean keyUp(andromeda::KeyEventArgs & e);
	aBoolean keyDown(andromeda::KeyEventArgs & e);
	aBoolean keyRepeat(andromeda::KeyEventArgs & e);

private:
	std::unique_ptr<andromeda::Engine> _engine;
};

#endif

