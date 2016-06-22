#include "x_state.h"

#include <cassert>

#include <andromeda/andromeda.h>
#include <andromeda/graphics.h>

#include <andromeda/Utilities/log.h>

using namespace andromeda;
using namespace andromeda::xeffect;


/*

*/
XStateGroup::XStateGroup(const std::string & name)
	: _name(name)
{
	
}


/*

*/
XStateGroup::~XStateGroup()
{

}


/*

*/
void XStateGroup::addState(const std::shared_ptr<IState> & state)
{
	assert(state);

	_states.push_back(state);
}



/*

*/
void XStateGroup::apply() const
{
	for (const auto & it : _states)
		it->apply();
}


void XStateGroup::log() const
{
	log_tree();

	for (const auto & it : _states)
		it->log();
}



/*
	TODO:
	This could be done over multiple source files but.... meh (For Now)
*/




/*
	Culling 
*/
XStateCulling::XStateCulling(CullMode cull)
	: _culling(cull)
{
	
}

void XStateCulling::apply() const
{
	graphics()->setCulling(_culling);
}

void XStateCulling::log() const
{
	log_infop("Culling State");
	log_infop("Culling = %1%", (Int32)_culling);
}


/*
	Polygon Mode
*/
XStatePolygon::XStatePolygon()
{

}

void XStatePolygon::apply() const
{
	graphics()->setPolygonMode(_face, _polygon);
}

void XStatePolygon::log() const
{
	log_infop("Polygon Mode State");
	log_infop("Polygon = %1%", (Int32)_polygon);
	log_infop("Face = %1%", (Int32)_face);
}


/*
	Alpha Blending
*/
XStateBlending::XStateBlending()
{

}

void XStateBlending::apply() const
{
	graphics()->setBlendEnabled(_enabled);
	graphics()->setBlendColor(_color.red, _color.green, _color.blue, _color.alpha);
	graphics()->setBlendEquation(_rgbEquation, _alphaEquation);
	graphics()->setBlendFunction(_rgbSource, _rgbDestination, _alphaSource, _alphaDestination);
}

void XStateBlending::log() const
{
	log_infop("Blending State");
	log_infop("Enabled = %1%", _enabled);
	log_infop("Color = {%1%, %2%, %3%, %4%}", _color.red, _color.green, _color.blue, _color.alpha);
	log_infop("Equation: RGB = %1%, Alpha = %2%", (Int32)_rgbEquation, (Int32)_alphaEquation);
	log_infop("Source: RGB = %1%, Alpha = %2%", (Int32)_rgbSource, (Int32)_alphaSource);
	log_infop("Destination: RGB = %1%, Alpha = %2%", (Int32)_rgbDestination, (Int32)_alphaDestination);
}


/*
	Depth
*/
XStateDepth::XStateDepth()
{

}


void XStateDepth::apply() const
{
	graphics()->setDepthEnable(_enabled);
	graphics()->setDepthFunction(_function);
	graphics()->setDepthWriteEnable(_writeEnabled);
	graphics()->setDepthRange(_zNear, _zFar);
}

void XStateDepth::log() const
{
	log_infop("Depth State");
	log_infop("Enabled = %1%", _enabled);
	log_infop("Write Enabled = %1%", _writeEnabled);
	log_infop("Function = %1%", (Int32)_function);
	log_infop("Range = {%1%, %2%}", _zNear, _zFar);
}

/*
	Stencil
*/
XStateStencil::XStateStencil()
{

}

void XStateStencil::apply() const
{
	graphics()->setStencilEnable(_enabled);
	graphics()->setStencilFunction(_function, _ref, _funcMask, _face);
	graphics()->setStencilMask(_mask, _face);
	graphics()->setStencilOperation(_stencilFail, _depthFail, _depthPass, _face);
}

void XStateStencil::log() const
{
	log_infop("Stencil State");
	log_infop("Enabled = %1%", _enabled);
	log_infop("Face = %1%", (Int32)_face);
	log_infop("Function = %1% {%2%, %3%}", (Int32)_function, _funcMask, _ref);
	log_infop("Mask = %1%", _mask);
	log_infop("Operation = {%1%, %2%, %3%}", (Int32)_stencilFail, (Int32)_depthFail, (Int32)_depthPass);
}