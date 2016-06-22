#pragma once

#include <unordered_map>

#include <andromeda/stddef.h>

namespace andromeda
{
	namespace xeffect
	{
		/*
			Mirrors functionality of an unordered map, but could be done using a boost::ptree

			Only reason the class is used, is to add a parsing function to it.
		*/
		class XVariableMap
		{
		public:
			XVariableMap();
			virtual ~XVariableMap();


			/*
				Check whether a key exists
			*/
			const Boolean exists(const std::string & key);

			/*
				Add or Modify a Value
			*/
			const void set(const std::string & key, const std::string & value);

			/*
				Get a Value
			*/
			const std::string & get(const std::string & key);

			/*
				Parse a string for variables, and replace with their value
			*/
			std::string parse(const std::string & value);


		private:
			std::unordered_map<std::string, std::string> _map;
		};
	}
}