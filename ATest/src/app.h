#ifndef _APP_H_
#define _APP_H_

#include <memory>

#include <andromeda/stddef.h>

#include <andromeda/Engine/application.h>

#include <andromeda/Input/keyboard.h>
#include <andromeda/Input/mouse.h>

#include "game.h"

// Forward Declarations
namespace andromeda
{
	
	class Entity;
	class Engine;
	class View;

	struct CloseEventArgs;
	struct ResizeEventArgs;
	struct KeyEventArgs;

	class Texture;
	class RenderTarget;
	class RenderTarget2;
}



/*

*/
class App : public andromeda::Application, public andromeda::KeyboardListener, public andromeda::MouseListener
{
public:
	App();
	virtual ~App();

	/*
	
	*/
	void initialise();

	//void run();


	/*
	
	*/
	void update(aDouble ft) override;


	//void createEntity();

protected:
	aBoolean close(andromeda::CloseEventArgs & e);
	aBoolean resize(andromeda::ResizeEventArgs & e);


	// KeyboardListener
	aBoolean keyUp(andromeda::KeyEventArgs & e) override;
	aBoolean keyDown(andromeda::KeyEventArgs & e) override;
	aBoolean keyRepeat(andromeda::KeyEventArgs & e) override;

	// MouseListener
	aBoolean mouseDown(andromeda::MouseButtonEventArgs & e) override;
	aBoolean mouseUp(andromeda::MouseButtonEventArgs & e) override;
	aBoolean mouseMove(andromeda::MouseMoveEventArgs & e) override;
	aBoolean mouseWheel(andromeda::MouseWheelEventArgs & e) override;

	// IModule
	void onPause(){}
	void onResume(){}

private:
	//std::shared_ptr<andromeda::View> _view;
	//std::shared_ptr<andromeda::View> _dynView;


	//std::shared_ptr<andromeda::Texture> _texture;
	//std::shared_ptr<andromeda::RenderTarget2> _target;
	

	//std::list<std::shared_ptr<andromeda::Entity>> _entities;


	std::shared_ptr<Game> _game;
};

#endif

