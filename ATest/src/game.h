#ifndef _GAME_H_
#define _GAME_H_

#include <array>
#include <memory>
#include <list>

#include <andromeda/glm.h>

#include <andromeda/stddef.h>


#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Renderer/renderable.h>

#include <andromeda/Input/mouse.h>
#include <andromeda/Input/keyboard.h>

// Forward Declarations :: Engine
namespace andromeda
{
	class ISceneGraph;
	class Scene;
	class View;

	class GameObject;
	class Geometry;

	class Effect;

	class SceneManager;

	class LightDirectional;
}




// Forward Declarations :: Game
class Player;


/*

*/
class Game : public andromeda::MouseListener, public andromeda::KeyboardListener
{
public:
	Game();
	virtual ~Game();


	void update(aFloat ft);


protected:
	// MouseListener
	aBoolean mouseDown(andromeda::MouseButtonEventArgs & e) override { return true; };
	aBoolean mouseUp(andromeda::MouseButtonEventArgs & e) override { return true; };
	aBoolean mouseMove(andromeda::MouseMoveEventArgs & e) override;
	aBoolean mouseWheel(andromeda::MouseWheelEventArgs & e) override { return true; };

	aBoolean keyDown(andromeda::KeyEventArgs & e) override { return true; };
	aBoolean keyUp(andromeda::KeyEventArgs & e) override;
	aBoolean keyRepeat(andromeda::KeyEventArgs & e) override { return true; };

private:
	std::shared_ptr<andromeda::View> createView(aFloat x, aFloat y, aFloat w, aFloat h);
	std::shared_ptr<Player> createPlayer(aFloat x, aFloat y, aFloat w, aFloat h);

	std::shared_ptr<andromeda::GameObject> createCamera(const std::string & name);


	std::shared_ptr<andromeda::GameObject> createMesh(const std::string & name);


	// TEST
	void createText();

	std::shared_ptr<andromeda::Scene> _scene;					// Scene


	// TEMPORARY :: Need a way of pulling views from the Renderer
	std::list<std::shared_ptr<andromeda::View>> _views;			// List of main views

	std::list<std::shared_ptr<Player>> _players;





	// TEMP LIGHT
	std::shared_ptr<andromeda::LightDirectional> _light;
};

#endif