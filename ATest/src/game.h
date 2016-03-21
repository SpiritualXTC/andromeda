#ifndef _GAME_H_
#define _GAME_H_

#include <array>
#include <memory>
#include <list>

#include <andromeda/glm.h>

#include <andromeda/stddef.h>

#include <andromeda/Game/game_object.h>
#include <andromeda/Game/transform_component.h>	//TEMP
#include <andromeda/Game/render_component.h> //TEMP

#include <andromeda/Math/matrix_stack.h>
#include <andromeda/Graphics/effect.h>
#include <andromeda/Renderer/renderable.h>

#include <andromeda/Input/mouse.h>

namespace andromeda
{
	class ISceneGraph;
	class Scene;
	class View;

	class IRenderable;
	class Geometry;

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
	std::shared_ptr<andromeda::GameObject> createEntity(const std::string & name);


	std::weak_ptr<andromeda::Renderer> _renderer;


	//std::shared_ptr<andromeda::ISceneGraph> _sceneGraph;
	std::shared_ptr<andromeda::Scene> _scene;


#if 0
	void testInsert(std::shared_ptr<andromeda::GameObject> object);
	void testRemove(std::shared_ptr<andromeda::GameObject> object);
	void testExists(std::shared_ptr<andromeda::GameObject> object);
	void testRetrieve(std::shared_ptr<andromeda::GameObject> object);
#endif





	// TEMPORARY :: Need a way of pulling views from the Renderer
	std::list<std::shared_ptr<andromeda::View>> _views;	// List of main views
};

#endif