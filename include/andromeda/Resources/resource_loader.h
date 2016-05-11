#pragma once

#include <string>
#include <list>

#include <andromeda/stddef.h>
//#include <andromeda/Engine/module.h>

#include <andromeda/Utilities/log.h>

#include <andromeda/Resources/resource_manager.h>


namespace andromeda
{
	//template <typename RESOURCE>
	class ResourceLoader
	{
	public:
		ResourceLoader()
		{
		}


		template <typename RESOURCE>
		std::shared_ptr<RESOURCE> build(std::shared_ptr<File> file);
		/*
		{
			log_errp("No Resource Loading Implemented. Unable to load Resource");

			return nullptr;
		}
		*/
	};

	class Mesh;




#if 0
	/*
		Module that loads resources
	*/
	class ResourceLoader : public Module<ResourceLoader>
	{
	private:
		struct _Resource
		{

		};

	public:
		ResourceLoader();
		virtual ~ResourceLoader();


		// IModule
		void onPause() {}
		void onResume() {}

		void update();

	private:
		std::list<_Resource> _load;
	};
#endif
}
