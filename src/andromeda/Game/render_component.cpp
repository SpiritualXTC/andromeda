#include <andromeda/Game/render_component.h>

#include <andromeda/Renderer/scene_graph_cache.h>

using namespace andromeda;

/*

*/
RenderComponent::RenderComponent()
{

}

/*

*/
RenderComponent::RenderComponent(const std::string & renderGroup)
	: _renderGroup(renderGroup)
{

}



/*

*/
RenderComponent::~RenderComponent()
{

}


/*

*/
void RenderComponent::onRenderActivate(IRenderableManager * manager)
{
	manager->addRenderable(this, _renderGroup);
}

/*

*/
void RenderComponent::onRenderDeactivate(IRenderableManager * manager)
{
	manager->removeRenderable(this, _renderGroup);
}