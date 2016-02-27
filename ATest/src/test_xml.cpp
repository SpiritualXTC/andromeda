#include "test_xml.h"


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <andromeda/Utilities/log.h>

/*

*/
void testXML(const std::string & filename)
{
	using boost::property_tree::ptree;


	ptree pt;




	boost::property_tree::read_xml(filename, pt);

	ptree root = pt.get_child("effect");
	

	
	for (auto technique : root)
	{
		log_warn("Node = ", technique.first.c_str());
	
		for (auto pass : technique.second)
		{
			log_warn("Node = ", pass.first.c_str());

		}
	}
	

}