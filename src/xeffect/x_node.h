#pragma once

/*
	Helper/Wrapper Class for Accessing the ptree

	Currently just a dumb wrapper :(
*/



#include <memory>
#include <vector>

#include <boost/optional.hpp>
#include <boost/property_tree/ptree_fwd.hpp>

#include <andromeda/stddef.h>
#include <andromeda/Utilities/convert.h>

namespace andromeda
{
	namespace xeffect
	{
		// Forward-Declarations
		class XVariableMap;







		/*
			This class pulls some of the additional logic needed away from the loader itself
		*/

		class XNode
		{
		public:
			XNode(const boost::property_tree::ptree & node, XVariableMap & varMap);
			virtual ~XNode();

			// Get a child XNode
			XNode getChildNode(const std::string & name) const;

			Boolean hasChildNode(const std::string & name) const;

			// Has Name
			inline Boolean hasName() const {return _name.is_initialized();}

			// Get Name
			inline const boost::optional<std::string> getName() const { return _name; }

			// Is Empty
			Boolean isEmpty() const;

			// Get Attribute :: Processed for variables
			boost::optional<std::string> getAttribute(const std::string & attribute) const;
			std::string getAttribute(const std::string & attribute, const std::string & defValue) const;

			
			Boolean getAttributeArray(const std::string & attribute, std::vector<std::string> & values) const;


			// Get Value :: NOT Processed for variables
			boost::optional<std::string> getValue() const;


			// Get Attribute and Cast it to a type :: Processed for variables
			template <typename T>
			boost::optional<T> getAttribute(const std::string & attribute) const
			{
				// TODO:
				// Should probably catch any failed lexical_casts, and display an error :)

				boost::optional<T> attr;

				boost::optional<std::string> str = getAttribute(attribute);
				
				if (!str.is_initialized())
					return attr;

				std::string s = str.get();

				return convert<T>(s);
			}

			// Get Value of specific type :: NOT Processed for variables
			template <typename T>
			boost::optional<T> getValue() const
			{
				return _node.get_value_optional<T>();
			}






			// Get Raw Node!
			inline const boost::property_tree::ptree & getNode() const { return _node; }

		private:
			XVariableMap & _variables;

			boost::optional<std::string> _name;
			

			const boost::property_tree::ptree & _node;
		};
	}
}
