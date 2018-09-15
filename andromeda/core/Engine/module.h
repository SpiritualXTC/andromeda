#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <boost/type_traits.hpp>

#include <common/class.h>
#include <common/types.h>

#include <common/template.h>



namespace andromeda
{
	// Forward declarations
	class Engine;

	class IModule
	{
	public:
		IModule() {}
		virtual ~IModule() {}

		virtual Boolean open() = 0;	
		virtual Boolean close() = 0;	
		virtual Boolean resume() = 0;	
		virtual Boolean pause() = 0;	
		virtual Boolean update() = 0;


	};

	// TODO: REmove me
	class ModuleContainer : public IModule
	{
	public:
		ModuleContainer();
		virtual ~ModuleContainer();

		// TODO: Make a decent class-template edition

		Boolean open() override;
		Boolean close() override;
		Boolean resume() override;
		Boolean pause() override;
		Boolean update() override;

		template <typename T>
		Boolean insert(std::shared_ptr<IModule> m)
		{
			/*
			BOOST_STATIC_ASSERT((boost::is_base_of<IModule, T>::value));
			*/
			return insert(IClass<T>::id(), m);
		}

		template <typename T>
		Boolean exists()
		{
			return exists(IClass<T>::id())
		}

	protected:
		Boolean exists(ClassId id);
		Boolean insert(ClassId id, std::shared_ptr<IModule> _modules);

	private:
		std::unordered_map<ClassId, std::shared_ptr<IModule>> _modules;
	};











	class IModuleOLD
	{
	public:
		IModuleOLD() {}
		virtual ~IModuleOLD() {}

		virtual const Int32 priority() const = 0;

		/*
			Is it a System Module?
			System Modules CAN NOT be made inactive (They can be paused)
		*/
		virtual const Boolean isSystem() const = 0;	// Deprecated


		virtual Boolean onOpen() = 0;		// Open Module		:: Called by Engine::add		- Heavy Weight Initialisation
		virtual Boolean onClose() = 0;		// Close Module		:: Called by Engine::remove		- Heavy Weight Stop
		virtual Boolean onResume() = 0;		// Resume Module	:: Called by Engine::resume, or Engine::add
		virtual Boolean onPause() = 0;		// Pause Module		:: Called by Engine::pause, or Engine::remove
		virtual Boolean update() = 0;



		/*
			Makes the Multiset Work :)
		*/
		friend Boolean operator < (const std::shared_ptr<IModuleOLD> & lhs, const std::shared_ptr<IModuleOLD> & rhs)
		{
			return lhs->priority() < rhs->priority();
		}

		friend Boolean operator < (const IModuleOLD & lhs, const IModuleOLD & rhs)
		{
			return lhs.priority() < rhs.priority();
		}
	};



	/*
		TODO:
		SystemModule:
			This modules disables the ability to pause/resume -- this allows the engine to NOT care about the difference between the two types.

		Abstract Module
	*/
	template <class T>
	class Module : public IModuleOLD, virtual public TemplateIndex <T, IModuleOLD>
	{
		static const Int32 PRIORITY_MULTIPLIER = 10;

	protected:
		// Priority of the Module
		enum _Priority
		{
			Highest = -4,
			High = -2,
			Normal = 0,
			Low = 2,
			Lowest = 4
		};


		// Module Class
		enum  _Class
		{
			Critical = 1,	// Critical. Needs to be done first. Timing, Operating System Interaction

			Input,			// Input. Mouse, Keybaord, etc
			Update,			// Application logic
			Process,		// Additional Processing [This should be extremely light weight, probably sync physics with visuals]
			Render,			// Render. Rendering Code.

			Idle,			// Everything Else. Threads [Checks / Messaging], Messaging, File I/O, Resources, etc.
		};

	public:

		Module(_Class c, _Priority p = Module::Normal, Boolean system = false) 
			: _class(c)
			, _priority(p)
			, _system(system)
		{

		}

		virtual ~Module() { }

		const inline Int32 priority() const override { return _class * PRIORITY_MULTIPLIER + _priority; }
		const inline Boolean isSystem() const override { return _system; }






		

		


		/*
			Temporary
		*/
	//	void onStop() override { onPause(); }
	//	void onStart() override { onResume(); }

		// Should the Engine be a dependancy ?
	//	void pause() { return; }	// Tell the Engine to Pause ME
	//	void resume(){ return; }	// Tell the Engine to Resume ME

	protected:
		/*
		virtual void onAdd(Engine * engine) 
		{
		//	_engine = engine;
		}

		virtual void onRemove(Engine * engine) 
		{
		//	_engine = nullptr;
		}
		*/

	private:
		Boolean _system = false;		// Remove
		_Class _class = Module::Idle;
		_Priority _priority = Module::Normal;
	};



}
