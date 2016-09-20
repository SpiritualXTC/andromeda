#pragma once

#include <string>

#include <andromeda/stddef.h>

#include <andromeda/Resources/resource_builder.h>

namespace andromeda
{
	class Font;

	/*
	
	*/
	struct FontResourceArgs
	{
		std::string filename;
	};

	/*
	
	*/
	class FontResourceBuilder : public ResourceBuilderEx<Font, FontResourceArgs>
	{
	public:
		virtual std::shared_ptr<ResourceEx<Font, FontResourceArgs>> build(const boost::property_tree::ptree & propTree, const IFileLocation * location) override;
		std::shared_ptr<Font> load(const FontResourceArgs & args, const IFileLocation * location) override;
	};

	/*
	
	*/
	class FontResource : public ResourceEx<Font, FontResourceArgs>
	{
	public:
		FontResource(const std::string & name, const IFileLocation * location)
			: ResourceEx(name, location)
		{

		}

		inline FontResource & setFilename(const std::string & filename)
		{
			_args.filename = filename;
			return *this;
		}

	protected:
		const inline FontResourceArgs & getArgs() const override { return _args; }

	private:
		FontResourceArgs _args;
	};
}