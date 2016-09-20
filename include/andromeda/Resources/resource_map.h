#pragma once

/*
	This class should not be accessible to the API
*/

#include <memory>

#include <unordered_map>

#include <boost/property_tree/ptree.hpp>

#include "resource.h"
#include "resource_builder.h"

namespace andromeda
{
	/*
		Interface for easy use in containers :)
	*/
	class IResourceMap
	{
	public:
		virtual void addResource(const boost::property_tree::ptree & propTreeResourceNode, const IFileLocation * location) = 0;
	};



	/*
		TODO: Rename Me
		Interface that contains the resource type argument
	*/
	template <typename RESOURCE>
	class AResourceMap : public IResourceMap
	{
	public:
		virtual std::shared_ptr<RESOURCE> getResource(const std::string & name) = 0;
	};






	/*
		TODO: Rename Me
	*/
	template <typename RESOURCE, typename ARGS>
	class ResourceMap : public AResourceMap<RESOURCE>
	{
	public:
		ResourceMap(std::unique_ptr<ResourceBuilderEx<RESOURCE, ARGS>> && builder)
			: _builder(std::move(builder))
		{

		}

		/*
			Adds the Resource
		*/
		void addResource(const boost::property_tree::ptree & propTreeResourceNode, const IFileLocation * location) override
		{
			assert(location);

			std::shared_ptr<ResourceEx<RESOURCE, ARGS>> res = _builder->build(propTreeResourceNode, location);

			if (res)
			{
				// Add resource
				_resources.insert({ res->getName(), std::move(res) });
			}
			else
			{
				// Failed to add resource
			}
		}


		/*
			Gets the Resource
		*/
		std::shared_ptr<RESOURCE> getResource(const std::string & name) override
		{
			const auto & it = _resources.find(name);

			if (it == _resources.end())
				return nullptr;

			return it->second->acquire(_builder.get());
		}


	private:
		std::unique_ptr<ResourceBuilderEx<RESOURCE, ARGS>> _builder;

		// TODO: Should be unique
		std::unordered_map<std::string, std::shared_ptr<ResourceEx<RESOURCE, ARGS>>> _resources;
	};
}