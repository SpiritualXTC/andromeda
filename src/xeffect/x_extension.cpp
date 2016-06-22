#include "x_extension.h"

#include <algorithm>
#include <sstream>

using namespace andromeda;
using namespace andromeda::xeffect;


/*

*/
XExtension::XExtension()
{

}

/*

*/
XExtension::~XExtension()
{

}


/*

*/
void XExtension::setVersion(boost::optional<std::string> & version)
{
	_version = version;
}


/*

*/
Boolean XExtension::addExtension(const std::string & extension, const std::string & behaviour)
{
	static std::list<std::string> valid = 
	{
		{"enable"},
		{"require"},
		{"warn"},
		{"disable"}
	};
	
	// Search
	const auto & find = std::find(valid.begin(), valid.end(), behaviour);

	// Found?
	if (find == valid.end())
		return false;
	
	// Add Extension
	_Extension e;
	e.extension = extension;
	e.behaviour = behaviour;

	_extensions.push_back(e);

	return true;
}

std::string XExtension::getHeader()
{
	std::stringstream stream;

	if (_version.is_initialized())
		stream << "#version " << _version.get() << std::endl;

	for (const auto & it : _extensions)
	{
		stream << "#extension " << it.extension << " " << ":" << " " << it.behaviour << std::endl;
	}

	return stream.str();
}


