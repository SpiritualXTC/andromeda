#include "x_node.h"

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>

#include "x_variable_map.h"

using namespace andromeda;
using namespace andromeda::xeffect;

using namespace boost;
using namespace boost::property_tree;



/*
	Returns an empty property tree for defaults
*/
const ptree & empty_ptree()
{
	static ptree t;
	return t;
}


/*

*/
XNode::XNode(const boost::property_tree::ptree & node, XVariableMap & varMap)
	: _node(node)
	, _variables(varMap)
{
	// Get Name
	boost::optional<std::string> name = getAttribute("name");
	if (name.is_initialized())
	{
		_name = name.get();
	}
}


/*

*/
XNode::~XNode()
{

}


/*

*/
Boolean XNode::isEmpty() const
{
	return _node.empty();
}


/*

*/
XNode XNode::getChildNode(const std::string & name) const
{
	// Get Child
	boost::optional<const ptree &> n= _node.get_child_optional(name);

	// Return Node
	return XNode(n.is_initialized() ? n.get() : empty_ptree(), _variables);
}


/*

*/
Boolean XNode::hasChildNode(const std::string & name) const
{
	boost::optional<const ptree &> n = _node.get_child_optional(name);

	return n.is_initialized();
}


/*

*/
boost::optional<std::string> XNode::getAttribute(const std::string & attribute) const
{
	boost::optional<std::string> attr;

	// Get XML Attributes
	boost::optional<const ptree &> attributes = _node.get_child_optional("<xmlattr>");
	if (attributes.is_initialized())
	{
		// Get XML Attribute
		attr = attributes->get_optional<std::string>(attribute);
	}

	// Attribute not Set? Look for Child node
	if (!attr.is_initialized())
	{
		// Check for ptree children :: Alternate way of setting attributes
		boost::optional<const ptree &> n = _node.get_child_optional(attribute);

		// Child Node Exists?
		if (n.is_initialized())
		{
			// Get Node Value
			attr = n->get_value_optional<std::string>();
		}
	}

	// Attribute Set?
	if (attr.is_initialized())
	{
		std::string s = attr.get();

		// Reset Empty Strings
		// Reassign after processing with variables
		if (s.length() == 0)
			attr.reset();
		else
			attr = _variables.parse(s);
	}


#if 0
	// Get XML Attributes
	boost::optional<const ptree &> attributes = _node.get_child_optional("<xmlattr>");

	// XML Attributes Exist?
	if (attributes.is_initialized())
	{
		// Get Attribute Value
		attr = attributes->get_optional<std::string>(attribute);

		// Specific Attribute Exists? Replace variables with their value
		if (attr.is_initialized())
		{
			attr = _variables.parse(attr.get());
			return attr;
		}
	}
	
	// Check for ptree children :: Alternate way of setting attributes
	boost::optional<const ptree &> n = _node.get_child_optional(attribute);

	// Node Exists?
	if (n.is_initialized())
	{
		// Get Node Value
		attr = n->get_value_optional<std::string>();

		// Replace variables with their value
		if (attr.is_initialized())
			attr = _variables.parse(attr.get());
	}
#endif 

	return attr;
}


/*

*/
std::string XNode::getAttribute(const std::string & attribute, const std::string & defValue) const
{
	boost::optional<std::string> val = getAttribute(attribute);

	if (val.is_initialized())
		return val.get();

	return defValue;
}


/*

*/
Boolean XNode::getAttributeArray(const std::string & attribute, std::vector<std::string> & values) const
{
	// Get the Attribute
	boost::optional<std::string> attr = getAttribute(attribute);

	// Is attribute initialized?
	if (!attr.is_initialized())
		return false;
	
	// Get the string
	std::string str = attr.get();

	// False Positive
	if (str.length() == 0)
		return false;

	// Look for Array Signature
	if (str.find('{') == 0 && str.find('}') == str.length() - 1)
	{
		// Remove Array Characters and split
		boost::split(values, str.substr(1, str.length() - 2), boost::is_any_of(","));
	}
	else
		values.push_back(str);

	// Trim
	for (std::string & value : values)
	{
		// Trim Whitespace
		boost::trim(value);
	}

	return true;
}


/*

*/
boost::optional<std::string> XNode::getValue() const
{
	return _node.get_value_optional<std::string>();
}