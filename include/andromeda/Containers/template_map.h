#ifndef _ANDROMEDA_CONTAINERS_TEMPLATE_MAP_H_
#define _ANDROMEDA_CONTAINERS_TEMPLATE_MAP_H_

#include <memory>
#include <unordered_map>

#include <andromeda/stddef.h>
#include <andromeda/Utilities/template.h>

namespace andromeda
{
	/*
		Container for accessing an unordered_map via template ID
		The Template ID is the key to the map
	*/
	template <typename _INTERFACE_>
	class TemplateMap
	{
	public:
		typedef std::unordered_map<TemplateID, std::shared_ptr<_INTERFACE_>> _Map;

	


	public:
		/*
		
		*/
		TemplateMap() {}

		/*
		
		*/
		virtual ~TemplateMap() {}


		/*
			Is the Map Empty?
		*/
		Boolean empty()
		{
			return _map.empty();
		}

		/*
			Get Size of the Map
		*/
		Boolean size()
		{
			return _map.size();
		}

		/*
			Clear the Map
		*/
		void clear()
		{
			_map.clear();
		}


		/*
			Retrieve the value
		*/
		template <typename T>
		std::shared_ptr<T> at()
		{
			TemplateID id = templateId<T>();
			
			return std::static_pointer_cast<T>(_map.at(id));
		}

		/*
			Determines whether it exists
		*/
		template <typename T>
		Boolean exists()
		{
			// Get Template ID
			TemplateID id = templateId<T>();

			// Find Key
			return _map.find(id) != _map.end();
		}

		/*
			Inserts into the Map
		*/
		template <typename T>
		Boolean insert(std::shared_ptr<T> & p)
		{
			// Get Template ID
			TemplateID id = templateId<T>();

			// Insert Into the Map :: This fails when attempting to override
			auto result = _map.insert(std::pair<TemplateID, std::shared_ptr<_INTERFACE_>>(id, p));

			// Return SUCCESS if the key exists
			return result.second;
		}


		/*
			Erase from the Map
		*/
		template <typename T>
		Boolean erase()
		{
			// Get Template ID
			TemplateID id = templateId<T>();

			// Erase Key
			Size removed = _map.erase(id);
			
			// Return SUCCESS if elements where removed 
			return removed > 0;
		}


		/* Iteration */
		inline auto begin() { return _map.begin(); }
		inline const auto begin() const { return _map.begin(); }

		inline auto end() { return _map.end(); }
		inline const auto end() const { return _map.end(); }


	protected:
		/*
			Gets the Template ID
		*/
		template <typename T>
		const inline TemplateID templateId() const { return TemplateIndex<T, _INTERFACE_>::getTemplateId(); }

	private:

		_Map _map;
	};
}



#endif
