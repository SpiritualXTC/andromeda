#pragma once

#include <memory>

#include <thread>

#include <core/andromeda.h>
#include <core/Input/keyboard.h>
#include <core/Input/mouse.h>

//Forward Declarations
class ITest;


class App : public andromeda::Andromeda, public andromeda::KeyboardListener, public andromeda::MouseListener
{
public:
	App(std::shared_ptr<ITest> testRunner);
	virtual ~App();

	// KeyboardListener
	aBoolean keyDown(const andromeda::KeyEventArgs& e) override;
	aBoolean keyUp(const andromeda::KeyEventArgs& e) override;
	aBoolean keyRepeat(const andromeda::KeyEventArgs& e) override;

	// Mouse Listener
	aBoolean mouseDown(const andromeda::MouseButtonEventArgs& e) override;
	aBoolean mouseUp(const andromeda::MouseButtonEventArgs& e) override;

	aBoolean mouseMove(const andromeda::MouseMoveEventArgs& e) override;
	aBoolean mouseWheel(const andromeda::MouseWheelEventArgs& e) override;

private:
	std::thread _thread;
};