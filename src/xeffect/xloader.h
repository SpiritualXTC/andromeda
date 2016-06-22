#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <boost/property_tree/ptree_fwd.hpp>


#include <andromeda/stddef.h>



#include "x_extension.h"
#include "x_variable_map.h"

namespace andromeda
{
	namespace xeffect
	{
		// Forward Declarations
		class XEffect;
		class XNode;
		class XPass;
		class XShader;
		class XShaderBuilder;
		class XShaderSource;
		class XStateGroup;
		class XTechnique;

		enum class XShaderType;
		




		class XEffectLoader
		{
		private:
			const std::string INVALID_CHARACTERS = "{}";
			const std::string VARIABLE_REGEX_PATTERN = "\\$\\(\\w+\\)";

			const std::string GLOBAL_SHADER_NAME = "[global]";
		

		public:
			XEffectLoader();
			virtual ~XEffectLoader();


			std::shared_ptr<XEffect> loadFromFile(const std::string & filepath);
			std::shared_ptr<XEffect> loadFromSource(const std::string & source);

			Boolean setLoadFileCallback(std::function<std::string(const std::string&)> load)
			{
				_cbLoad = load;

				return true;
			}

		private:

			/*
				Execute the Callback
			*/
			inline std::string loadFile(const std::string & filename)
			{
				// TODO: Needs to use the callback loadFile, or the default loadFile
				return _cbLoad(filename);
			}



	
			/*
				Default Action when loading a file
			*/
			std::string loadFileDefault(const std::string & filename);


			std::shared_ptr<XEffect> loadEffect(std::istream & is);
			std::shared_ptr<XEffect> loadEffect(XNode & node);

			
			void loadVariable(XNode & node);
			void loadExtension(XNode & node);

			std::shared_ptr<XShaderSource> loadShader(XNode & node, Boolean global = false);
			std::shared_ptr<XStateGroup> loadState(XNode & node, Boolean global = false);

			std::shared_ptr<XTechnique> loadTechnique(XNode & node, const std::shared_ptr<XEffect> & effect);
			std::shared_ptr<XPass> loadPass(XNode & node, const std::shared_ptr<XTechnique> & technique);

			std::shared_ptr<XShaderBuilder> loadPassShader(XNode & node, XShaderType type);


			std::shared_ptr<XShaderSource> findShader(const std::string & name);





			std::string _location;

			std::function<std::string(const std::string&)> _cbLoad;

			std::unordered_map<std::string, std::shared_ptr<XStateGroup>> _states;
			std::unordered_map<std::string, std::shared_ptr<XShaderSource>> _shaders;

			XExtension _extensions;
			XVariableMap _variables;
		};

	}
}
