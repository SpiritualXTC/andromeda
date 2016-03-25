#include <andromeda/Game/game_object.h>

#include <andromeda/Game/component.h>

using namespace andromeda;

const std::string GameObject::GAME_OBJECT_GENERIC_NAME = "obj_";


/*

*/
GameObject::GameObject(const std::string & name)
	: _name(name)
{

}


/*

*/
void GameObject::onViewActivate(View * view)
{
	assert(view);

	// First View Reference ?
	if (_viewReferenceCounter == 0)
	{
		int c = 0;
		// Iterate through all components
		for (const auto & p : components())
		{
			p.second->onViewActivate();
			c++;
		}
	}
	

	int c = 0;
	// Iterate through all components
	for (const auto & p : components())
	{

		c++;

		p.second->onViewActivate(view);
	}

	// Increment View Reference Counter
	_viewReferenceCounter++;
}


/*

*/
void GameObject::onViewDeactivate(View * view)
{
	// Decrement View Reference Counter
	_viewReferenceCounter--;

	// Last View Reference
	if (_viewReferenceCounter == 0)
	{
		// Iterate through all components
		for (const auto & p : components())
		{
			p.second->onViewDeactivate();
		}
	}


	// Iterate through all components
	for (const auto & p : components())
	{
		p.second->onViewDeactivate(view);
	}
}


/*
	Updates all the components
*/
void GameObject::update(const Float timeStep)
{
	// 2 Update functions may be useful, one does a full update - the other a partial update
	// Full Update only occur IFF _viewReferenceCount > 1
	// EG: 
	//	AABB will need to be updated every frame... for physics & Collision Detection
	//	However animation matrices only need to be recalculated if the object is going to be drawn

	for (const auto & p : components())
		p.second->update(timeStep);
}