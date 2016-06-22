#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <boost/algorithm/string.hpp>

#include <andromeda/stddef.h>
#include <andromeda/graphics_types.h>

namespace andromeda
{
	namespace xeffect
	{

		class XTypeConversion
		{
		public:

			static Boolean convBoolean(const std::string & value, Boolean def);

			static PolygonMode convPolygonMode(const std::string & value, PolygonMode def);
			static CullMode convCullMode(const std::string & value, CullMode def);
			static FaceMode convFaceMode(const std::string & value, FaceMode def);
			static FaceDirection convFaceDirection(const std::string & value, FaceDirection def);


			
			static Function convFunction(const std::string & value, Function def);

			static BlendFunction convBlendFunction(const std::string & value, BlendFunction def);
			static BlendEquation convBlendEquation(const std::string & value, BlendEquation def);

			static StencilOperation convStencilOperation(const std::string & value, StencilOperation def);

		private:
			// Helper to access the conversion functions
			template <class T>
			static T getFromMap(const std::unordered_map<std::string, T> & map, const std::string & key, T def)
			{
				/*
					TODO: 
					Should display an error for invalid values!

					Probably via an exception -- which could be caught by the loader
				*/

				T val = def;

				std::string k = boost::to_lower_copy(key);

				const auto & it = map.find(k);

				if (it != map.end())
					val = it->second;

				return val;
			}
		};

	}
}
