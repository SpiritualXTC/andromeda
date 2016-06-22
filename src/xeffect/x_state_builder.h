#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <boost/algorithm/string.hpp>

#include <andromeda/stddef.h>




namespace andromeda
{
	namespace xeffect
	{
		class IState;


		class XNode;
		class XStateGroup;
		
		/*
		
		*/
		class XStateBuilder
		{
		public:
			XStateBuilder(const std::string & name, const XNode & node);
			virtual ~XStateBuilder();


			std::shared_ptr<XStateGroup> build();

		private:

			std::shared_ptr<IState> buildState(const std::string & element, const XNode & node);


			std::shared_ptr<IState> buildCulling(const XNode & node);

			std::shared_ptr<IState> buildPolygon(const XNode & node);

			std::shared_ptr<IState> buildBlending(const XNode & node);
			std::shared_ptr<IState> buildDepth(const XNode & node);
			std::shared_ptr<IState> buildStencil(const XNode & node);

			std::string _name;
			const XNode & _node;
		};
	}
}
