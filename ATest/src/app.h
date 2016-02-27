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

	class RenderTarget;
	class ParticleSystem;
}



/*

*/
class App : public andromeda::Application, andromeda::KeyboardListener, andromeda::MouseListener
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


	void createEntity();

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
	std::shared_ptr<andromeda::View> _view;
	std::shared_ptr<andromeda::View> _dynView;

	std::shared_ptr<andromeda::RenderTarget> _target;
	std::shared_ptr<andromeda::ParticleSystem> _particles;


	std::list<std::shared_ptr<andromeda::Entity>> _entities;


	


	Game _game;
};

#endif

