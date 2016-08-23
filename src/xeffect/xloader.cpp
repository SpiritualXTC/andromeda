#include "xloader.h"


#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>


#include <andromeda/graphics_conversion.h>

#include <andromeda/Utilities/chain.h>
#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/log.h>


#include "x_effect.h"
#include "x_name.h"
#include "x_node.h"
#include "x_pass.h"
#include "x_shader.h"
#include "x_shader_builder.h"
#include "x_shader_source.h"
#include "x_state.h"
#include "x_state_builder.h"
#include "x_technique.h"
#include "x_uniform_builder.h"

using namespace andromeda;
using namespace andromeda::xeffect;

using namespace boost;
using namespace boost::property_tree;

















/*

*/
XEffectLoader::XEffectLoader()
{
	log_debugp("XEffectLoader :: <init>()");

	// Setup Callback
	_cbLoad = std::bind(&XEffectLoader::loadFileDefault, this, std::placeholders::_1);
}


/*

*/
XEffectLoader::~XEffectLoader()
{
	
}


/*
	Load an Effect from File
*/
std::shared_ptr<XEffect> XEffectLoader::loadFromFile(const std::string & filepath)
{
	log_debugp("XEffectLoader :: loadFromFile()");

	using namespace boost;

	// Validate if File Exists
	if (!filesystem::exists(filepath))
		return nullptr;

	// Get the Location of the File
	_location = GetDirectory(filepath);

	// Select Open Mode
	UInt mode = 0;	// Read Mode ???

	// Open File
	std::ifstream file(filepath, mode);

	// Is the File Open ?
	if (!file.is_open())
		return nullptr;

	// Load Effect
	std::shared_ptr<XEffect> effect = loadEffect(file);

	// Close File
	file.close();

	return effect;
}


/*
	Load the Effect from Source
*/
std::shared_ptr<XEffect> XEffectLoader::loadFromSource(const std::string & source)
{
	std::stringstream str(source);

	// Load Effect
	std::shared_ptr<XEffect> effect = loadEffect(str);

	return effect;
}



/*
	Default File Loading Mechanism
*/
std::string XEffectLoader::loadFileDefault(const std::string & filename)
{
	std::string filepath = _location + "/" + filename;

	log_infop(" - Loading Shader '%1%'", filepath);

	// Validate if File Exists
	if (!filesystem::exists(filepath))
	{
		log_errp(" - File doesn't exist '%1%'", filepath);
		return "";
	}

	// Open File
	std::ifstream file(filepath);

	// Is the File Open ?
	if (!file.is_open())
	{
		log_errp(" - Unable to open file '%1%'", filepath);
		return "";
	}

	// Load all of the file
	std::stringstream stream;
	std::string line;
	while (std::getline(file, line))
	{
		stream << line << std::endl;
	}

	// Close File
	file.close();

	return stream.str();
}



/*

*/
std::shared_ptr<XEffect> XEffectLoader::loadEffect(std::istream & stream)
{
	log_debugp("XEffectLoader :: loadEffect()");

	property_tree::ptree pt;

	// TODO: Choose between XML or JSON parsers
	// Parse XML
	read_xml(stream, pt);

	XNode root(pt, _variables);

	return loadEffect(root.getChildNode("effect"));
}



/*

*/
std::shared_ptr<XEffect> XEffectLoader::loadEffect(XNode & node)
{
	std::shared_ptr<XEffect> effect = std::make_shared<XEffect>();


	log_debugp("XEffectLoader :: loadEffect() :: XML Parsed");
	log_tree();

	// Set Shader Version
	_extensions.setVersion(node.getAttribute("version"));


	// Interpret Property Tree
	for (const auto & p : node.getNode())
	{
		const std::string & element = p.first;
		XNode n(p.second, _variables);

		// Load "Shared" Shaders
		if (element == "var")
		{
			// Load Variable
			loadVariable(n);
		}
		else if (element == "extension")
		{
			// Load Extension
			loadExtension(n);
		}
		else if (element == "state")
		{
			// Load State
			loadState(n, true);
		}
		else if (element == "shader")
		{
			// Load Shader
			loadShader(n, true);
		}
		else if (element == "technique")
		{
			// Load Technique
			loadTechnique(n, effect);
		}
		else
		{
			log_infop("Node <%1%>, Name = %2%", element, n.getName());
		}
	}

	return effect;
}


/*

*/
void XEffectLoader::loadVariable(XNode & node)
{
	boost::optional<std::string> name = node.getName();
	boost::optional<std::string> value = node.getAttribute("value");

	// TODO: Warning or Error here!
	if (!name.is_initialized() || !value.is_initialized())
	{
		if (!name.is_initialized())
			log_warnp("Invalid Declaration :: Variables require a name");
		else 
			log_warnp("Invalid Declaration :: Variable '%1%' requires an initial value", name);

		return;
	}

	log_verbosep("Variable Declaration :: %1% = %2%", name, value);


	// Set Variable
	_variables.set(name.get(), value.get());

	return;
}


/*
	loadExtension():


*/
void XEffectLoader::loadExtension(XNode & node)
{
	boost::optional<std::string> name = node.getName();
	if (!name.is_initialized())
	{
		log_warnp("Invalid Extension :: Extension requires a name");
		return;
	}

	std::string value = node.getAttribute("value", "enable");

	// Add Extension
	_extensions.addExtension(name.get(), value);
	return;
}



/*
	loadShader();

	Shaders can be loaded from file or inline source
*/
std::shared_ptr<XShaderSource> XEffectLoader::loadShader(XNode & node, Boolean global)
{
	// TODO:
	// Clean up default naming
	static Int32 counter = 0;

	// Get Name
	std::string name;
	
	if (!node.hasName())
	{
		if (global)
			name = GLOBAL_SHADER_NAME;
		else
			name = XNameGenerator<XShader>().generate("shader");
	}
	else
		name = node.getName().get();

	log_infop("Shader <%1%>", name);
	log_tree();

	

	// Get Name
	// TODO:
	// Due to the fact that shaders can be loaded from numerous sources and in numerous places (Shared or Pass Specific) a better system for default name will need to be used
	// As support for a "nameless" shader is also needed, defaulting the name needs to be done with care. lol
	// Anonymous (nameless) shaders ARE allowed to be loaded so long as they are declared inline from a "Pass"
	// There can only be ONE, anonymous (nameless) shaders loaded in the shared area :: This is attached to every other shader

	// TODO: Anonymous Shaders still need to be handled!

	// Get the source code from the Node
	XChainShaderSource chain;

	chain.add(std::make_shared<XChainShaderSourceFile>(_cbLoad));
	chain.add(std::make_shared<XChainShaderSourceCode>());

	boost::optional<std::string> source = chain.handle(node);

	// Validate Source
	if (!source.is_initialized())
		return nullptr;

	std::string & src = source.get();

	// Trim Whitespace
	algorithm::trim(src);

	// Empty String
	if (src.empty())
		return nullptr;

	// Create Shader OR Append Shader
	std::shared_ptr<XShaderSource> shader = std::make_shared<XShaderSource>(name, src);

//	log_verbosep("%1%", shader->source());

	// Add to Shader Source Map
	// TODO: Check whether a shader with that name matches
	if (global && shader)
		_shaders[shader->name()] = shader;

	return shader;
}


/*

*/
std::shared_ptr<XStateGroup> XEffectLoader::loadState(XNode & node, Boolean global)
{
	// Get Name
	std::string name;

	if (!node.hasName())
	{
		if (global)
		{
			log_warnp("State requires a name");
			return nullptr;
		}
		else
			name = XNameGenerator<XStateGroup>().generate("state");
	}
	else
		name = node.getName().get();

	// Create the Builder
	XStateBuilder builder(name, node);

	// Build the State Group
	std::shared_ptr<XStateGroup> state = builder.build();

	// Add State Group
	if (global && state)
		_states[state->getName()] = state;

	return state;
}


/*

*/
std::shared_ptr<XTechnique> XEffectLoader::loadTechnique(XNode & node, const std::shared_ptr<XEffect> & effect)
{
	// TODO:
	// Seriously No. Counter Bad!
	static Int32 counter = 0;

	// Get Technique Name
	std::string name = node.hasName() ? node.getName().get() : XNameGenerator<XTechnique>().generate("technique");
	log_infop("Technique <%1%>", name);
	log_tree();

	// TODO: Technique Already Exists ?

	// Create Technqiue
	std::shared_ptr<XTechnique> technique = std::make_shared<XTechnique>(name);

	// Loop through all nodes
	for (const auto & p : node.getNode())
	{
		const std::string & element = p.first;

		// Ignore anything that isn't a "pass"
		// Techniques only have one valid child for now.
		if (element != "pass")
			continue;

		// Load Pass
		XNode node(p.second, _variables);
		std::shared_ptr<XPass> pass = loadPass(node, technique);
	}

	if (technique)
		effect->addTechnique(technique);

	return technique;
}


/*

*/
std::shared_ptr<XPass> XEffectLoader::loadPass(XNode & node, const std::shared_ptr<XTechnique> & technique)
{
	assert(technique);

	// TODO:
	// Seriously No. Counter Bad!
	static Int32 counter = 0;

	// Get Pass Name
	std::string name = node.hasName() ? node.getName().get() : XNameGenerator<XPass>().generate("pass");;
	log_infop("Pass <%1%>", name);

	log_tree();

	// Load Rasterisation

	// Load Shaders
	// Vertex Shader
	std::shared_ptr<XShaderBuilder> vertex = loadPassShader(node, XShaderType::Vertex);


	// Fragment Shader
	std::shared_ptr<XShaderBuilder> fragment = loadPassShader(node, XShaderType::Fragment);


	// Geometry Shader
	std::shared_ptr<XShaderBuilder> geometry = loadPassShader(node, XShaderType::Geometry);

	// Validate Vertex and Fragment Shader
	if (!vertex || !fragment)
	{
		log_errp("Rendering passes requires both, Vertex and Fragment Shaders");
		return nullptr;
	}

	// Create a Shader Program!
	XShaderProgramBuilder programBuilder;

	if (vertex)
	{
		programBuilder.attachShader(vertex);
		log_infop("Attached Vertex Shader");
	}

	if (fragment)
	{
		programBuilder.attachShader(fragment);
		log_infop("Attached Fragment Shader");
	}

	if (geometry)
	{
		programBuilder.attachShader(geometry);
		log_infop("Attached Geometry Shader");
	}

	// Build Shader Program
	std::shared_ptr<XShaderProgram> program = programBuilder.link();


	// Validate
	if (!program)
	{
		log_errp("Pass <%2%> :: Unable to link shader Technique = %1%, Pass = %2%", technique->getName(), name);
		return nullptr;
	}

	log_infop("Pass <%1%> :: Shader Created", name);

	// Create Pass
	std::shared_ptr<XPass> pass = std::make_shared<XPass>(name, program);

	// Enabled State
	boost::optional<std::string> enabled = node.getAttribute("enabled");
	
	if (enabled.is_initialized())
	{
		log_debugp("Pass <%1%> :: Set Enabled = %2%", name, enabled);
		pass->setEnabled(util::convertToBoolean(enabled.get(), true));
	}

	// Load States
	std::vector<std::string> states;
	if (node.getAttributeArray("state", states))
	{
		for (const auto & s : states)
		{
			// Find the State
			const auto & it = _states.find(s);
			if (it != _states.end())
			{
				// Add it only if it isn't empty :: Premature Optimization :P
				if (! it->second->isEmpty())
					pass->addState(it->second);
			}
			else
				log_warnp("Pass <%1%> :: Unable to find State '%2%'", pass->getName(), s);
		}
	}

	// Loop through nodes
	for (const auto & p : node.getNode())
	{
		const std::string & element = p.first;


		XNode n(p.second, _variables);


		if (element == "uniform")
		{
			// Create New Uniform
			std::shared_ptr<XUniform> uniform = XUniformBuilder(n).build();
			if (uniform != nullptr)
				pass->addUniform(uniform);
		}
		else if (element == "state")
		{
			// Create New State
			std::shared_ptr<XStateGroup> state = loadState(n);
			if (state)
			{
				pass->addState(state);

				log_debugp("Inline State Created");
			}
		}
	}


	// Add Pass
	if (pass != nullptr)
		technique->addPass(pass);

	return pass;
}




/*

*/
std::shared_ptr<XShaderBuilder> XEffectLoader::loadPassShader(XNode & node, XShaderType type)
{
	static std::unordered_map<XShaderType, std::string> nodeName =
	{
		{ XShaderType::Vertex, "vertexShader" },
		{ XShaderType::Fragment, "fragmentShader" },
		{ XShaderType::Geometry, "geometryShader" }
	};

	XNode n = node.getChildNode(nodeName[type]);

	if (n.isEmpty())
		return nullptr;


	log_infop("Building Shader Source: %1%", nodeName[type]);
	log_tree();

	Int32 count = 0;


	// Build Complete Shader Source
	std::shared_ptr<XShaderBuilder> builder = std::make_shared<XShaderBuilder>(type);

	/*
		TODO:
		Ability to Override shader extensions / version
	*/

	// Get and Attach Shader Headers
	builder->attachHeader(_extensions);

	// Get and Attach Global Shader
	std::shared_ptr<XShaderSource> globalShader = findShader(GLOBAL_SHADER_NAME);
	if (globalShader)
	{
		builder->attachCode(globalShader);
	}



	// Link "Shared" Shaders
	std::vector<std::string> values;
	if (n.getAttributeArray("shader", values))
	{
		// Loop through list and attach code
		for (const std::string & name : values)
		{
			// Find and Attach
			std::shared_ptr<XShaderSource> shader = findShader(name);
			if (shader)
			{
				// Attach Source Code
				if (builder->attachCode(shader))
					count++;
			}
			else
			{
				log_warnp("Shader with name, '%1%' can't be found", name);
			}
		}
	}


	// Look for "shader" child nodes :: There may be multiple
	for (const auto & p : n.getNode())
	{
		if (p.first == "shader")
		{
			// Load Shader
			std::shared_ptr<XShaderSource> source = loadShader(XNode(p.second, _variables));
			if (source)
			{
				if (builder->attachCode(source))
					count++;
			}
		}
	}

//	log_warnp("Complete Shader Source. Source Attached = %1%", count);

	// No Source was Attached :: Currently Global Source ISN'T COUNTED
	if (count == 0)
		return nullptr;

	//log_verbosep("%1%", builder->source());



	return builder;
}


/*
	Find the Shader
*/
std::shared_ptr<XShaderSource> XEffectLoader::findShader(const std::string & name)
{
	const auto & it = _shaders.find(name);
	return it == _shaders.end() ? nullptr : it->second;
}

