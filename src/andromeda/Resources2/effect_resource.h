#pragma once

#include <string>

#include <andromeda/stddef.h>


#include <andromeda/Resources2/resource.h>
#include <andromeda/Resources2/resource_builder.h>

namespace andromeda
{
	class Effect;


	/*
		Arguments for Loading a Effect

		TODO:
		Add a spot so variables can be injected into the effect (Maybe)
	*/
	struct EffectResourceArgs
	{
		std::string filename;
	};


	/*
		Create and Load a Effect Resource
	*/
	class EffectResourceBuilder : public ResourceBuilderEx<Effect, EffectResourceArgs>
	{
	public:
		std::shared_ptr<ResourceEx<Effect, EffectResourceArgs>> build(const boost::property_tree::ptree & propTree, const IFileLocation * location) override;
		std::shared_ptr<Effect> load(const EffectResourceArgs & args, const IFileLocation * location) override;
	};



	/*
		Effect Resource
	*/
	class EffectResource : public ResourceEx<Effect, EffectResourceArgs>
	{
	public:
		EffectResource(const std::string & name, const IFileLocation * location)
			: ResourceEx(name, location)
		{

		}

		// Set Filename
		inline EffectResource & setFilename(const std::string & filename)
		{
			_args.filename = filename;

			return *this;
		}

	protected:
		const inline EffectResourceArgs & getArgs() const override { return _args; }

	private:
		EffectResourceArgs _args;
	};

}
