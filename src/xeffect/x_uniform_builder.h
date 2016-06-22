#pragma once

#include <memory>
#include <vector>


#include <andromeda/stddef.h>

namespace andromeda
{
	namespace xeffect
	{
		class XNode;
		class XUniform;

		class XUniformBuilder
		{
		private:
			enum class _UniformDataType
			{
				Auto,
				Float,
				Int,
			};

		public:
			XUniformBuilder(const XNode & node);
			virtual ~XUniformBuilder();


			std::shared_ptr<XUniform> build();


		private:
			_UniformDataType determineType(const std::string & type);
			std::shared_ptr<XUniform> buildFloat();
			std::shared_ptr<XUniform> buildInt();


			std::string _name;
			_UniformDataType _type = _UniformDataType::Auto;
			std::vector<std::string> _values;
	
			const XNode & _node;
		};
	}
}
