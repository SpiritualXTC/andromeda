#include <andromeda/Utilities/Util/ptree_helper.h>

using namespace andromeda;




boost::optional<std::string> util::getChildValueOptional(const boost::property_tree::ptree & propTree, const std::string & child)
{
	boost::optional<std::string> value;

	boost::optional<const boost::property_tree::ptree&> childTree = propTree.get_child_optional(child);

	if (childTree.is_initialized())
	{
		value = childTree->get_value_optional<std::string>();
	}

	return value;
}