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