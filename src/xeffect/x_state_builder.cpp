#include "x_state_builder.h"


#include <boost/exception/exception.hpp>
#include <boost/property_tree/ptree.hpp>

#include <andromeda/Utilities/log.h>

#include "x_node.h"
#include "x_state.h"
#include "x_type_conversion.h"
#include "x_variable_map.h"

using namespace andromeda;
using namespace andromeda::xeffect;


/*

*/
XStateBuilder::XStateBuilder(const std::string & name, const XNode & node)
	: _name(name)
	, _node(node)
{
	
}


/*

*/
XStateBuilder::~XStateBuilder()
{

}



/*

*/
std::shared_ptr<XStateGroup> XStateBuilder::build()
{
	// Create State Machine
	std::shared_ptr<XStateGroup> statemachine = std::make_shared<XStateGroup>(_name);
	XVariableMap vm;	// Empty Variable Map :: TODO, *MIGHT* be worth passing the true variable map for the states

	log_infop("State Builder :: '%1%'", _name);
	log_tree();

	// Iterate through each state
	for (const auto & n : _node.getNode())
	{
		std::string element = boost::to_lower_copy(n.first);

		XNode node(n.second, vm);
		
		// Build the state
		try
		{
			std::shared_ptr<IState> state = buildState(element, node);

			if (state)
			{
				// Add state
				statemachine->addState(state);

				// Value Testing
			//	state->log();
			}
		}
		catch (std::exception & e)
		{
			log_errp("EXCEPTION: %1%", e.what());
		}

	}



	return statemachine;
}


/*

*/
std::shared_ptr<IState> XStateBuilder::buildState(const std::string & element, const XNode & node)
{
	std::shared_ptr<IState> state;

	if (element == "cull")
	{
		state = buildCulling(node);
	}
	else if (element == "polygon")
	{
		state = buildPolygon(node);
	}
	else if (element == "blending")
	{
		state = buildBlending(node);
	}
	else if (element == "depth")
	{
		state = buildDepth(node);
	}
	else if (element == "stencil")
	{
		state = buildStencil(node);
	}
	
	return state;
}


/*

*/
std::shared_ptr<IState> XStateBuilder::buildCulling(const XNode & node)
{
	// Get Value
	boost::optional<std::string> value = node.getValue();

	// Validate
	if (!value.is_initialized())
		return nullptr;

	// Convert
	CullMode cull = XTypeConversion::convCullMode(value.get(), CullMode::None);

	// Create
	return std::make_shared<XStateCulling>(cull);
}


/*

*/
std::shared_ptr<IState> XStateBuilder::buildPolygon(const XNode & node)
{
	std::shared_ptr<XStatePolygon> state = std::make_shared<XStatePolygon>();

	// Polygon Mode [Attribute or Value]
	boost::optional<std::string> polygonMode = node.getAttribute("mode");
	if (!polygonMode.is_initialized())
		polygonMode = node.getValue();

	if (polygonMode.is_initialized())
		state->setPolygonMode(XTypeConversion::convPolygonMode(polygonMode.get(), PolygonMode::Fill));


	// Face Mode
	boost::optional<std::string> faceMode = node.getAttribute("face");
	if (faceMode.is_initialized())
		state->setFaceMode(XTypeConversion::convFaceMode(faceMode.get(), FaceMode::FrontAndBack));

	return state;
}


/*

*/
std::shared_ptr<IState> XStateBuilder::buildBlending(const XNode & node)
{
	std::shared_ptr<XStateBlending> state = std::make_shared<XStateBlending>();

	// Blending Enabled
	boost::optional<std::string> enable = node.getAttribute("enable");
	if (enable.is_initialized())
	{
		state->setEnabled(XTypeConversion::convBoolean(enable.get(), true));
	}

	// Color
	if (node.hasChildNode("color"))
	{
		XNode color = node.getChildNode("color");

		boost::optional<Float> r = color.getAttribute<Float>("red");
		boost::optional<Float> g = color.getAttribute<Float>("green");
		boost::optional<Float> b = color.getAttribute<Float>("blue");
		boost::optional<Float> a = color.getAttribute<Float>("alpha");

		if (r.is_initialized())
			state->setRed(r.get());
		if (g.is_initialized())
			state->setGreen(g.get());
		if (b.is_initialized())
			state->setBlue(b.get());
		if (a.is_initialized())
			state->setAlpha(a.get());
	}


	// Equation
	boost::optional<std::string> equation = node.getAttribute("equation");
	if (equation.is_initialized())
	{
		state->setEquation(XTypeConversion::convBlendEquation(equation.get(), BlendEquation::Add));
	}
	else if (node.hasChildNode("equation"))
	{
		XNode eq = node.getChildNode("equation");
		boost::optional<std::string> rgb = eq.getAttribute("rgb");
		boost::optional<std::string> alpha = eq.getAttribute("alpha");

		if (rgb.is_initialized())
			state->setRGBEquation(XTypeConversion::convBlendEquation(rgb.get(), BlendEquation::Add));
		if (alpha.is_initialized())
			state->setAlphaEquation(XTypeConversion::convBlendEquation(alpha.get(), BlendEquation::Add));
	}

	// Source Function
	boost::optional<std::string> source = node.getAttribute("source");
	if (source.is_initialized())
	{
		state->setSourceFunction(XTypeConversion::convBlendFunction(source.get(), BlendFunction::One));
	}
	else if (node.hasChildNode("source"))
	{
		XNode fn = node.getChildNode("source");
		boost::optional<std::string> rgb = fn.getAttribute("rgb");
		boost::optional<std::string> alpha = fn.getAttribute("alpha");

		if (rgb.is_initialized())
			state->setRGBSourceFunction(XTypeConversion::convBlendFunction(rgb.get(), BlendFunction::One));
		if (alpha.is_initialized())
			state->setAlphaSourceFunction(XTypeConversion::convBlendFunction(alpha.get(), BlendFunction::One));
	}

	// Destination Function
	boost::optional<std::string> destination = node.getAttribute("destination");
	if (destination.is_initialized())
	{
		state->setDestinationFunction(XTypeConversion::convBlendFunction(destination.get(), BlendFunction::Zero));
	}
	else if (node.hasChildNode("destination"))
	{
		XNode fn = node.getChildNode("destination");
		boost::optional<std::string> rgb = fn.getAttribute("rgb");
		boost::optional<std::string> alpha = fn.getAttribute("alpha");

		if (rgb.is_initialized())
			state->setRGBDestinationFunction(XTypeConversion::convBlendFunction(rgb.get(), BlendFunction::Zero));
		if (alpha.is_initialized())
			state->setAlphaDestinationFunction(XTypeConversion::convBlendFunction(alpha.get(), BlendFunction::Zero));
	}

	return state;
}


/*

*/
std::shared_ptr<IState> XStateBuilder::buildDepth(const XNode & node)
{
	std::shared_ptr<XStateDepth> state = std::make_shared<XStateDepth>();

	// Depth Test Enabled
	boost::optional<std::string> enable = node.getAttribute("enable");
	if (enable.is_initialized())
	{
		state->setEnabled(XTypeConversion::convBoolean(enable.get(), true));
	}

	// Depth Write Enabled
	boost::optional<std::string> write = node.getAttribute("write");
	if (write.is_initialized())
	{
		state->setWriteEnabled(XTypeConversion::convBoolean(write.get(), true));
	}

	// Function
	boost::optional<std::string> func = node.getAttribute("function");
	if (func.is_initialized())
	{
		state->setFunction(XTypeConversion::convFunction(func.get(), Function::Less));
	}
	
	// Special!
	if (node.hasChildNode("range"))
	{
		XNode range = node.getChildNode("range");

		boost::optional<Float> near = range.getAttribute<Float>("near");
		boost::optional<Float> far = range.getAttribute<Float>("far");

		if (near.is_initialized())
			state->setZNear(near.get());

		if (far.is_initialized())
			state->setZFar(far.get());
	}
	else
	{
		boost::optional<Float> near = node.getAttribute<Float>("near");
		boost::optional<Float> far = node.getAttribute<Float>("far");

		if (near.is_initialized())
			state->setZNear(near.get());

		if (far.is_initialized())
			state->setZFar(far.get());
	}

	return state;
}


/*

*/
std::shared_ptr<IState> XStateBuilder::buildStencil(const XNode & node)
{
	std::shared_ptr<XStateStencil> state = std::make_shared<XStateStencil>();

	// Stencil Test Enabled
	boost::optional<std::string> enable = node.getAttribute("enable");
	if (enable.is_initialized())
	{
		state->setEnabled(XTypeConversion::convBoolean(enable.get(), true));
	}

	// Face
	boost::optional<std::string> face = node.getAttribute("face");
	if (face.is_initialized())
	{
		state->setFaceMode(XTypeConversion::convFaceMode(face.get(), FaceMode::FrontAndBack));
	}

	// Function
	if (node.hasChildNode("function"))
	{
		XNode function = node.getChildNode("function");

		boost::optional<std::string> func = function.getAttribute("function");
		if (!func.is_initialized())
			func = function.getValue();
		
		if (func.is_initialized())
		{
			state->setFunction(XTypeConversion::convFunction(func.get(), Function::Always));
		}

		boost::optional<Int32> ref = function.getAttribute<Int32>("ref");
		if (ref.is_initialized())
			state->setFunctionReference(ref.get());

		boost::optional<UInt32> fmask = function.getAttribute<UInt32>("mask");
		if (fmask.is_initialized())
			state->setFunctionMask(fmask.get());
	}

	// Mask
	boost::optional<UInt32> mask = node.getAttribute<UInt32>("mask");
	if (mask.is_initialized())
		state->setMask(mask.get());

	// Operation
	if (node.hasChildNode("operation"))
	{
		XNode operation = node.getChildNode("operation");

		boost::optional<std::string> stenFail = operation.getAttribute("fail");
		boost::optional<std::string> depthFail = operation.getAttribute("depthfail");
		boost::optional<std::string> depthPass = operation.getAttribute("depthpass");

		if (stenFail.is_initialized())
			state->setStencilFailOperation(XTypeConversion::convStencilOperation(stenFail.get(), StencilOperation::Keep));

		if (depthFail.is_initialized())
			state->setDepthFailOperation(XTypeConversion::convStencilOperation(depthFail.get(), StencilOperation::Keep));

		if (depthPass.is_initialized())
			state->setDepthPassOperation(XTypeConversion::convStencilOperation(depthPass.get(), StencilOperation::Keep));
	}

	return state;
}