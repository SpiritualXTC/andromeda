#include "effect_resource.h"

#include <andromeda/IO/file.h>
#include <andromeda/IO/file_location.h>


#include <andromeda/Graphics/effect.h>
#include <andromeda/Utilities/io.h>
#include <andromeda/Utilities/Util/ptree_helper.h>

#include <xeffect/xeffect.h>

#include <andromeda/Utilities/log.h>



// TODO: Remove this!
// It is currently required while XEffect is built into andromeda.
// XEffect is going to be completely pulled out of the main library, with a lightweight passthrough class that extends Effect
#include "../../xeffect/x_effect.h"


using namespace andromeda;

/*

*/
std::shared_ptr<ResourceEx<Effect, EffectResourceArgs>> EffectResourceBuilder::build(const boost::property_tree::ptree & propTree, const IFileLocation * location)
{
	// Get Args from Tree
	boost::optional<std::string> name = util::getChildValueOptional(propTree, "name");
	boost::optional<std::string> filename = util::getChildValueOptional(propTree, "filename");

	// Filename must be set
	if (!filename.is_initialized())
		return nullptr;

	log_debugp("EffectResourceBuilder :: build() :: Creating Effect Resource");
	log_tree();


	// Set the Name :: Strip the Filename for the name (Remove Slashes)
	if (!name.is_initialized())
		name = GetFilename(filename.get());


	// Create Resource
	auto resource = std::make_shared<EffectResource>(name.get(), location);

	// Set Filename
	resource->setFilename(filename.get());

	return resource;
}





class EffectResourceLoaderCallback : public xeffect::IXEffectLoadFileCallback
{
public:
	EffectResourceLoaderCallback(const IFileLocation * location, const std::string & shaderDir)
		: _location(location)
		, _shaderDirectory(shaderDir)
	{
		if (_shaderDirectory.length() > 0)
			_shaderDirectory.push_back('/');

	}

	std::string loadFile(const std::string & filename) override
	{
		std::string fn = _shaderDirectory + filename;

		log_debugp("EffectResourceLoaderCallback :: Loading '%1%' from callback", fn);

		std::shared_ptr<File> file = _location->loadFile(fn, false);

		return file->data();
	}

private:
	const IFileLocation * _location;
	std::string _shaderDirectory;
};


/*

*/
std::shared_ptr<Effect> EffectResourceBuilder::load(const EffectResourceArgs & args, const IFileLocation * location)
{
	assert(location);

	log_debugp("Loading Effect : %1%", args.filename);

	std::string dir = andromeda::GetDirectory(args.filename);

	// Set up the Callback
	EffectResourceLoaderCallback cb(location, dir);

	// Use the Loader to load the File :: This needs to be done on a seperate thread
	std::shared_ptr<File> file = location->loadFile(args.filename, false);

	// This source file has no way of knowing that XEffect is derived from Effect
	// This is resolved temporarily by including the XEffect header :: this method shouldn't be used.
	// XEffect needs to be refactored.
	std::shared_ptr<Effect> effect = xeffect::LoadEffectFromSource(file->data(), &cb);

	return effect;
}