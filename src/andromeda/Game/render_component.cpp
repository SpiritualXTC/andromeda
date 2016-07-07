#include <andromeda/Game/render_component.h>

#include <andromeda/Renderer/view.h>

using namespace andromeda;

/*

*/
RenderComponent::RenderComponent()
{

}


/*

*/
RenderComponent::~RenderComponent()
{

}


/*

*/
void RenderComponent::onViewActivate(View * view)
{
	view->addRenderable(this);
}

/*

*/
void RenderComponent::onViewDeactivate(View * view)
{
	view->removeRenderable(this);
}