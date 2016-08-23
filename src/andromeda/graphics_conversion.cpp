#include <andromeda/graphics_conversion.h>

#include <unordered_map>


#include <boost/algorithm/string.hpp>


using namespace andromeda;









// Helper to access the conversion functions
template <class T>
T getFromMap(const std::unordered_map<std::string, T> & map, const std::string & key, T def)
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





/*

*/
Boolean util::convertToBoolean(const std::string & value, Boolean def)
{
	static std::unordered_map<std::string, Boolean> values =
	{
		{ "false", false },
		{ "true", true },
		{ "f", false },
		{ "t", true },
		{ "n", false },
		{ "y", true },
		{ "0", false },
		{ "1", true }
	};

	return getFromMap<Boolean>(values, value, def);
}




/*

*/
PolygonMode util::convertToPolygonMode(const std::string & value, PolygonMode def)
{
	static std::unordered_map<std::string, PolygonMode> values =
	{
		{ "fill", PolygonMode::Fill },
		{ "line", PolygonMode::Wireframe },
		{ "wireframe", PolygonMode::Wireframe }
	};

	return getFromMap<PolygonMode>(values, value, def);
}

/*

*/
CullMode util::convertToCullMode(const std::string & value, CullMode def)
{
	static std::unordered_map<std::string, CullMode> values =
	{
		{ "front", CullMode::Front },
		{ "back", CullMode::Back },
		{ "all", CullMode::FrontAndBack },
		{ "both", CullMode::FrontAndBack },
		{ "frontandback", CullMode::FrontAndBack },
		{ "none", CullMode::None }
	};

	return getFromMap<CullMode>(values, value, def);
}


/*

*/
FaceMode util::convertToFaceMode(const std::string & value, FaceMode def)
{
	static std::unordered_map<std::string, FaceMode> values =
	{
		{ "front", FaceMode::Front },
		{ "back", FaceMode::Back },
		{ "all", FaceMode::FrontAndBack },
		{ "both", FaceMode::FrontAndBack },
		{ "frontandback", FaceMode::FrontAndBack }
	};

	return getFromMap<FaceMode>(values, value, def);
}

/*

*/
FaceDirection util::convertToFaceDirection(const std::string & value, FaceDirection def)
{
	static std::unordered_map<std::string, FaceDirection> values =
	{
		{ "cw", FaceDirection::Clockwise },
		{ "ccw", FaceDirection::CounterClockwise },
		{ "clockwise", FaceDirection::Clockwise },
		{ "counterclockwise", FaceDirection::CounterClockwise }
	};

	return getFromMap<FaceDirection>(values, value, def);
}

/*

*/
Function util::convertToFunction(const std::string & value, Function def)
{
	static std::unordered_map<std::string, Function> values =
	{
		{ "never", Function::Never },
		{ "equal", Function::Equal },
		{ "notequal", Function::NotEqual },
		{ "less", Function::Less },
		{ "lessequal", Function::LessEqual },
		{ "lequal", Function::LessEqual },
		{ "le", Function::LessEqual },
		{ "greater", Function::Greater },
		{ "greaterequal", Function::GreaterEqual },
		{ "gequal", Function::GreaterEqual },
		{ "ge", Function::GreaterEqual },
		{ "always", Function::Always }
	};

	return getFromMap<Function>(values, value, def);
}



/*

*/
BlendFunction util::convertToBlendFunction(const std::string & value, BlendFunction def)
{
	static std::unordered_map<std::string, BlendFunction> values =
	{
		{ "zero", BlendFunction::Zero },
		{ "one", BlendFunction::One },

		{ "srccolor", BlendFunction::SourceColor },
		{ "sourcecolor", BlendFunction::SourceColor },
		{ "oneminussrccolor", BlendFunction::OneMinusSourceColor },
		{ "oneminussourcecolor", BlendFunction::OneMinusSourceColor },

		{ "destcolor", BlendFunction::DestinationColor },
		{ "destinationcolor", BlendFunction::DestinationColor },
		{ "oneminusdestcolor", BlendFunction::OneMinusDestinationColor },
		{ "oneminusdestinationcolor", BlendFunction::OneMinusDestinationColor },

		{ "srcalpha", BlendFunction::SourceAlpha },
		{ "sourcealpha", BlendFunction::SourceAlpha },
		{ "oneminussrcalpha", BlendFunction::OneMinusSourceAlpha },
		{ "oneminussourcealpha", BlendFunction::OneMinusSourceAlpha },

		{ "srcalphasaturate", BlendFunction::SourceAlphaSaturate },
		{ "sourcealphasaturate", BlendFunction::SourceAlphaSaturate },

		{ "destalpha", BlendFunction::DestinationAlpha },
		{ "destinationalpha", BlendFunction::DestinationAlpha },
		{ "oneminusdestalpha", BlendFunction::OneMinusDestinationAlpha },
		{ "oneminusdestinationalpha", BlendFunction::OneMinusDestinationAlpha },

		{ "constantcolor", BlendFunction::ConstantColor },
		{ "constantalpha", BlendFunction::ConstantAlpha },
		{ "oneminusconstantcolor", BlendFunction::OneMinusConstantColor },
		{ "oneminusconstantalpha", BlendFunction::OneMinusConstantAlpha },

		{ "constcolor", BlendFunction::ConstantColor },
		{ "constalpha", BlendFunction::ConstantAlpha },
		{ "oneminusconstcolor", BlendFunction::OneMinusConstantColor },
		{ "oneminusconstalpha", BlendFunction::OneMinusConstantAlpha },
	};

	return getFromMap(values, value, def);
}


/*

*/
BlendEquation util::convertToBlendEquation(const std::string & value, BlendEquation def)
{
	static std::unordered_map<std::string, BlendEquation> values =
	{
		{ "add", BlendEquation::Add },
		{ "subtract", BlendEquation::Subtract },
		{ "reverse", BlendEquation::ReverseSubtract },
		{ "reversesubstract", BlendEquation::ReverseSubtract },
		{ "min", BlendEquation::Minimum },
		{ "minimum", BlendEquation::Minimum },
		{ "max", BlendEquation::Maximum },
		{ "maximum", BlendEquation::Maximum }
	};

	return getFromMap(values, value, def);
}


/*

*/
StencilOperation util::convertToStencilOperation(const std::string & value, StencilOperation def)
{
	static std::unordered_map<std::string, StencilOperation> values =
	{
		{ "zero", StencilOperation::Zero },
		{ "keep", StencilOperation::Keep },
		{ "replace", StencilOperation::Replace },

		{ "incr", StencilOperation::Increment },
		{ "increment", StencilOperation::Increment },
		{ "incrwrap", StencilOperation::IncrementWrap },
		{ "incrementwrap", StencilOperation::IncrementWrap },

		{ "decr", StencilOperation::Decrement },
		{ "decrement", StencilOperation::Decrement },
		{ "decrwrap", StencilOperation::DecrementWrap },
		{ "decrementwrap", StencilOperation::DecrementWrap },

		{ "invert", StencilOperation::Invert }
	};

	return getFromMap(values, value, def);
}





/*

*/
TextureMinFilter util::convertToTextureMinFilter(const std::string & value, TextureMinFilter def)
{
	static std::unordered_map<std::string, TextureMinFilter> values =
	{
		{ "nearest", TextureMinFilter::Nearest },
		{ "linear", TextureMinFilter::Linear },

		{ "nearestmipmapnearest", TextureMinFilter::NearestMipmapNearest },
		{ "linearmipmapnearest", TextureMinFilter::LinearMipmapNearest },

		{ "nearestmipmaplinear", TextureMinFilter::NearestMipmapLinear },
		{ "linearmipmaplinear", TextureMinFilter::LinearMipmapLinear },
	};

	return getFromMap(values, value, def);
}


/*

*/
TextureMagFilter util::convertToTextureMagFilter(const std::string & value, TextureMagFilter def)
{
	static std::unordered_map<std::string, TextureMagFilter> values =
	{
		{"nearest", TextureMagFilter::Nearest},
		{"linear", TextureMagFilter::Linear}
	};

	return getFromMap(values, value, def);
}



/*
	TODO:
	Add Support for more formats :)
*/
StorageFormat util::convertToStorageFormat(const std::string & value, StorageFormat def)
{
	static std::unordered_map<std::string, StorageFormat> values =
	{
		{ "rgba", StorageFormat::RGBA },
	};

	return getFromMap(values, value, def);

}