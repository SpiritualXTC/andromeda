#include <andromeda/Graphics/effect.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>



#include <andromeda/Graphics/pass.h>
#include <andromeda/Graphics/shader.h>

#include <andromeda/Utilities/log.h>
#include <andromeda/Utilities/io.h>

using namespace andromeda;






/*
	Loads a Shader
*/
std::shared_ptr<ShaderPartial> LoadShader(boost::property_tree::ptree & pt, GLenum shaderType)
{
	// Get Filename Attribute
	boost::optional<std::string> fn = pt.get_optional<std::string>("<xmlattr>.filename");

	std::string source = "";

	if (fn.is_initialized())
	{
		log_warn("Load Shader = ", fn.get());

		// Load the File
		source = andromeda::LoadFile("../res/shader/" + fn.get());
	}
	else
	{
		boost::optional<std::string> src = pt.get_value_optional<std::string>();

		if (src.is_initialized())
		{
			// Load the Source
			source = src.get();
		}
	}

	// Validate Source
	if (source.length() == 0)
		return nullptr;

	// Compile the Shader!
	std::shared_ptr<ShaderPartial> sp = std::make_shared<ShaderPartial>(source, shaderType);

	return sp;
}

/*

*/
std::shared_ptr<ShaderPartial> LoadShader(boost::optional<boost::property_tree::ptree&> & pt, GLenum shaderType)
{
	if (pt.is_initialized())
		return LoadShader(pt.get(), shaderType);

	return nullptr;
}




/*
	Loads a Pass
*/
std::shared_ptr<Pass> LoadPass(boost::property_tree::ptree & pt)
{
	// This is a temporary thing generic passes. which aren't added :)
	typedef andromeda::Pass GenericPass;


	// Get Technique ID Attribute
	boost::optional<std::string> id = pt.get_optional<std::string>("<xmlattr>.id");

	if (!id.is_initialized())
	{
		log_warn("Pass has no ID");
		return nullptr;
	}

	

	log_warn("Adding Pass = ", id.get());

	// Load Vertex Shader
	std::shared_ptr<ShaderPartial> vs = LoadShader(pt.get_child_optional("vertexshader"), GL_VERTEX_SHADER);
	std::shared_ptr<ShaderPartial> fs = LoadShader(pt.get_child_optional("fragmentshader"), GL_FRAGMENT_SHADER);
	std::shared_ptr<ShaderPartial> gs = LoadShader(pt.get_child_optional("geometryshader"), GL_GEOMETRY_SHADER);

	std::shared_ptr<Shader> shader = nullptr;

	// Create Shader
	if (vs && fs)
	{
		shader = std::make_shared<Shader>();

		shader->attach(vs);
		shader->attach(fs);

		/* Optional Shaders */
		// Geometry
		if (gs)
			shader->attach(gs);

		// Tesselation

		// Link
		shader->link();
	}
	else
		return nullptr;

	// Validate Shader
	if (!shader)
	{
		log_err("Pass contains no Shader");
		return nullptr;
	}

	// Create Pass
	std::shared_ptr<GenericPass> pass = std::make_shared<GenericPass>(id.get(), shader);

	return pass;
}


/*
	Loads an Effect File
*/
std::shared_ptr<Effect> andromeda::LoadEffect(const std::string & filename)
{
	/*
		Loads the XML File (Allow loading of XML or JSon Effects)
	*/
	using boost::property_tree::ptree;

	ptree pt;

	// Parse XML File
	boost::property_tree::read_xml(filename, pt);

	// Get XML Root
	ptree root = pt.get_child("effect");

	// Create the Effect
	std::shared_ptr<Effect> effect = std::make_shared<Effect>();

	// Loop through all Techniques!
	for (auto node : root)
	{
		if (node.first != "technique")
			continue;

		// Get Technique ID Attribute
		boost::optional<std::string> technique = node.second.get_optional<std::string>("<xmlattr>.id");

		boost::optional<Int32> group = node.second.get_optional<Int32>("<xmlattr>.group");

		if (!technique.is_initialized())
		{
			log_warn("Technique has no ID");
			continue;
		}

		// Get Technique ID
		std::string id = technique.get();

		// Add Technique
		effect->addTechnique(id, group.is_initialized() ? group.get() : 0);


		log_warn("Adding Technique = ", id);


		// Loop through all Passes
		for (auto n : node.second)
		{
			if (n.first != "pass")
				continue;

			// Load Pass
			std::shared_ptr<Pass> pass = LoadPass(n.second);

			// Add Pass
			if (pass)
				effect->addPass(id, pass);
		}
	}

	return effect;
}
