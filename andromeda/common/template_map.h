#pragma once 

#include <memory>
#include <unordered_map>

#include "types.h"
#include "template.h"

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
		TemplateMap() {}
		virtual ~TemplateMap() {}


		inline Boolean empty()
		{
			return _map.empty();
		}

		inline Size size()
		{
			return _map.size();
		}

		inline void clear()
		{
			_map.clear();
		}

		template <typename T>
		std::shared_ptr<T> at()
		{
			return std::static_pointer_cast<T>(_map.at(templateId<T>()));
		}

		template <typename T>
		Boolean exists()
		{
			return _map.find(templateId<T>()) != _map.end();
		}

		template <typename T>
		Boolean insert(std::shared_ptr<T> & p)
		{
			auto result = _map.insert(std::pair<TemplateID, std::shared_ptr<_INTERFACE_>>(templateId<T>(), p));
			return result.second;
		}

		template <typename T>
		Boolean erase()
		{
			Size removed = _map.erase(templateId<T>());
			return removed > 0;
		}


		// Iteration
		inline auto begin() { return _map.begin(); }
		inline const auto begin() const { return _map.begin(); }

		inline auto end() { return _map.end(); }
		inline const auto end() const { return _map.end(); }


	protected:
		template <typename T>
		const inline TemplateID templateId() const { return TemplateIndex<T, _INTERFACE_>::getTemplateId(); }

	private:
		_Map _map;
	};
}
