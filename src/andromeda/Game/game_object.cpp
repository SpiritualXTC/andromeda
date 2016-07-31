#include <andromeda/Game/game_object.h>

#include <andromeda/Game/component.h>

using namespace andromeda;

Int32 GameObject::GAME_OBJECT_COUNTER = 0;
const std::string GameObject::GAME_OBJECT_GENERIC_NAME = "obj_";




/*

*/
GameObject::GameObject(const std::string & name)
	: _name(name)
{

}


/*

*/
void GameObject::onRenderActivate(IRenderableManager * manager)
{
	assert(manager);

	// First View Reference ?
	if (_renderReferenceCounter == 0)
	{
		// Iterate through all components
		for (const auto & p : components())
		{
			p.second->onRenderActivate();
		}
	}
	
	// Iterate through all components
	for (const auto & p : components())
	{
		p.second->onRenderActivate(manager);
	}

	// Increment View Reference Counter
	_renderReferenceCounter++;
}


/*

*/
void GameObject::onRenderDeactivate(IRenderableManager * manager)
{
	assert(manager);

	// Decrement View Reference Counter
	_renderReferenceCounter--;

	// Last View Reference
	if (_renderReferenceCounter == 0)
	{
		// Iterate through all components
		for (const auto & p : components())
		{
			p.second->onRenderDeactivate();
		}
	}

	// Iterate through all components
	for (const auto & p : components())
	{
		p.second->onRenderDeactivate(manager);
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