#pragma once

#include <string>

#include <andromeda/stddef.h>

#include <andromeda/Utilities/chain.h>

#include <boost/property_tree/ptree_fwd.hpp>

namespace andromeda
{
	namespace xeffect
	{
		class XNode;

		/*
		
		*/
		class XShaderSource
		{
		public:

			/*
			
			*/
			XShaderSource(const std::string & name, const std::string & source);
			virtual ~XShaderSource();




			/*
				Gets the full Source Code for the shader
			*/
			const std::string & source() const { return _source; }
			const std::string & name() const { return _name; }


		private:
			std::string _name;
			std::string _source;
		};







		/*
		
		*/
		typedef Chain<std::string, const XNode> XChainShaderSource;


		/*
		
		*/
		class XChainShaderSourceFile : virtual public XChainShaderSource
		{
		public:
			XChainShaderSourceFile(std::function<std::string(const std::string&)> cbLoad);

		protected:
			boost::optional<std::string> process(const XNode & node) override;

		private:
			Boolean preprocess(std::string & source);

			std::function<std::string(const std::string&)> _cbLoad;
		};


		/*
		
		*/
		class XChainShaderSourceCode : virtual public XChainShaderSource
		{
		public:

		protected:
			boost::optional<std::string> process(const XNode & node) override;
		};
	}
}
