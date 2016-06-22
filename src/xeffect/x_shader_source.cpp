#include "x_shader_source.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>

#include <andromeda/Utilities/log.h>


#include "x_node.h"

using namespace andromeda;
using namespace andromeda::xeffect;

using namespace boost;


/*

*/
XShaderSource::XShaderSource(const std::string & name, const std::string & source)
	: _name(name)
	, _source(source)
{

}


/*

*/
XShaderSource::~XShaderSource()
{

}


/*

*/
XChainShaderSourceFile::XChainShaderSourceFile(std::function<std::string(const std::string&)> cbLoad)
	: _cbLoad(cbLoad)
{

}


/*

*/
boost::optional<std::string> XChainShaderSourceFile::process(const XNode & node)
{
	boost::optional<std::string> p;

	// Get Attributes
//	boost::optional<const property_tree::ptree &> attributes = pt.get_child_optional("<xmlattr>");

	// No Attributes
//	if (! attributes.is_initialized())
//		return p;

	// Get Source Tag
	// TODO: This COULD be a variable
//	boost::optional<std::string> source = attributes->get_optional<std::string>("source");

	boost::optional<std::string> file = node.getAttribute("source");

	// Source Tag Found?
	if (!file.is_initialized())
		return p;

	log_infop(" - Source File: %1%", file.get());

	// Load the File via the Callback (This will allow the application to determine how to load the file, rather than making a bunch of assumptions)
	// Default implementation however will load the file from the same directory as the XML File itself
	p = _cbLoad(file.get());
	
	/*
		TODO:

		Parse:
		#include <filename.glsl>

		boost::regex (Match?)
	*/

	if (p.is_initialized())
	{
		preprocess(p.get());
	}

	return p;
}

/*
	TODO:
	This may make more sense, to preprocess when the source is "stitched" together, rather than here
	#defines, will definately need to be done then anyway

	IE in the builder.
*/
Boolean XChainShaderSourceFile::preprocess(std::string & source)
{
	// (\"\w+\")
	//std::string pattern = "(#include)(\\h+)(\"[\\w|\\.]+\")";

	// Pattern to look for
	//std::string search_pattern = "(#include\\h+\"[\\w|\\.]+\")";

	// Pattern to look for = #include "[A-Z|a-z|0-9|.|\|/]"
	boost::regex search_regex("(#include\\h+\"[\\w|\\.|\\\\|/]+\")");

	// Result
	std::vector<std::string> includes;

	if (!boost::regex_search(source, boost::regex("(#include)(\\h+)(\"[\\w|\\.]+\")")))
	{
		// Nothing to preprocess
		// This is normal, so don't do anything.
		return false;
	}

	// Get All Cases
	boost::regex_split(std::back_inserter(includes), std::string(source), search_regex);

	for (const auto & s : includes)
	{
		log_verbosep("Value = %1%", s);

		boost::regex include_regex("(#include\\h+\")([\\w|\\.|\\\\|/]+)(\")");

		boost::smatch matches;

		if (boost::regex_match(s, matches, include_regex))
		{
			if (matches.size() >= 3)
			{
				// Get Filename
				std::string filename = matches[2].str();

				log_debugp("Including Filename = %1%", filename);

				// Load the New File
				std::string file = _cbLoad(filename);

				// Preprocess the New File
				preprocess(file);

				// Build String Replace Regex
				boost::regex source_regex("(#include\\h+\"" + filename + "\")");

				// Replace Source
				source = boost::regex_replace(source, source_regex, file);

				

			//	log_infop("Source = \n%1%", source);
			}

		}
		else
			log_errp("Umm No Match :: This should NOT be possible");
	}

	return true;
}







/*

*/
boost::optional<std::string> XChainShaderSourceCode::process(const XNode & node)
{
	return node.getValue();
}