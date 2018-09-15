#include "graphics.h"

#include <shared/context.h>
#include <core/Graphics/view.h>


using namespace andromeda;

std::mutex Graphics::_m;
std::shared_ptr<IGraphicsFactory> Graphics::_factory;

Graphics::Graphics(std::shared_ptr<IContext> context, std::shared_ptr<IGraphics> graphics)
	: _context(context)
	, _impl(graphics)
{
	assert(SetFactory(graphics->getFactory()));


	// TEMP: Create a dummy View
	std::shared_ptr<View> v = std::make_shared<View>("dummy");
	_views.insert({v->getName(), v});
}

Graphics::~Graphics()
{

}


Boolean Graphics::update()
{
	Boolean b = true;

	b &= clear(ClearMask::Color | ClearMask::Depth | ClearMask::Stencil);

	// Render all the Views
	for (auto view : _views)
	{
		b &= view.second->render();
	}

	b &= _context->swap();

	return b;
}

