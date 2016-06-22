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

namespace andromeda
{
	class ISceneGraph;
	class Scene;
	class View;

	class GameObject;
	class Geometry;

	class Effect;
	class Font;

	class Renderer;
}



/*

*/
class Game : public andromeda::MouseListener
{
public:
	Game(std::shared_ptr<andromeda::Renderer> renderer);
	virtual ~Game();


	void update(aFloat ft);


protected:
	// MouseListener
	aBoolean mouseDown(andromeda::MouseButtonEventArgs & e) override { return true; };
	aBoolean mouseUp(andromeda::MouseButtonEventArgs & e) override { return true; };
	aBoolean mouseMove(andromeda::MouseMoveEventArgs & e) override;
	aBoolean mouseWheel(andromeda::MouseWheelEventArgs & e) override { return true; };

private:
	//Ents<10000> _entities;

	void createView(aFloat x, aFloat y, aFloat w, aFloat h);

	std::shared_ptr<andromeda::GameObject> createGround();
	std::shared_ptr<andromeda::GameObject> createEntity(const std::string & name);
	std::shared_ptr<andromeda::GameObject> createCamera(const std::string & name);


	std::shared_ptr<andromeda::GameObject> createMesh(const std::string & name);


	
	std::weak_ptr<andromeda::Renderer> _renderer;	// Reference to the Renderer
	std::shared_ptr<andromeda::Scene> _scene;		// Scene


	// TEMPORARY :: Need a way of pulling views from the Renderer
	std::list<std::shared_ptr<andromeda::View>> _views;			// List of main views
	
	// TEMP FONT
	std::shared_ptr<andromeda::Font> _font;

};

#endif