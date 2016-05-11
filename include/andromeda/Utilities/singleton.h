#ifndef _ANDROMEDA_UTILITIES_SINGLETON_H_
#define _ANDROMEDA_UTILITIES_SINGLETON_H_

#include <memory>
#include <cassert>

namespace andromeda
{
	/*
	Singleton default creation
	*/
	template <typename T>
	class SingletonCreate
	{
	public:
		static std::unique_ptr<T> create()
		{
			return std::make_unique<T>();
		}
	};



	/*
	Singleton
	*/
	template <typename T, typename CreatePolicy = SingletonCreate<T>>
	class Singleton : private CreatePolicy
	{
		using CreatePolicy::create;

	public:
		static T * instance()
		{
			static std::unique_ptr<T> _instance = std::move(create());

			assert(_instance);

			return _instance.get();
		}
	protected:
		Singleton()
		{
			
		}
	private:
//		Singleton(const Singleton&);

//		Singleton& operator=(const Singleton&);

		Singleton(Singleton const&) = delete;
		void operator=(Singleton const&) = delete;
	};
}

#endif