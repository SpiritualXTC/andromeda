#ifndef _ANDROMEDA_ENGINE_MODULE_H_
#define _ANDROMEDA_ENGINE_MODULE_H_

#include <string>

#include "../stddef.h"

#include "../Utilities/dependancy.h"
#include "../Utilities/template.h"


namespace andromeda
{
	class IModule
	{
	public:
		IModule() {}
		virtual ~IModule() {}

		/*
			Priority of the Module
		*/
		virtual const Int32 priority() const = 0;

		/*
			Is it a System Module?
			System Modules CAN NOT be made inactive (They can be paused)
		*/
		virtual const Boolean isSystem() const = 0;

#if 0
		/*
			Start the Module
		*/
		virtual void onStart() = 0;

		/*
			Stop the Module
		*/
		virtual void onStop() = 0;
#endif
		/*
			Resume the Module
		*/
		virtual void onResume() = 0;

		/*
			Pause the Module
		*/
		virtual void onPause() = 0;

		/*
			Update the Module
		*/
		virtual void update() = 0;



		/*
			Makes the Multiset Work :)
		*/
		friend Boolean operator < (const std::shared_ptr<IModule> & lhs, const std::shared_ptr<IModule> & rhs)
		{
			return lhs->priority() < rhs->priority();
		}

		friend Boolean operator < (const IModule & lhs, const IModule & rhs)
		{
			return lhs.priority() < rhs.priority();
		}
	};



	/*
		Abstract Module
	*/
	template <class T>
	class Module : public IModule, public Dependancy <T, IModule>
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
			Critical = 1,	// Critical. Needs to be done first.	Timing, Operating System Interaction

			Input,			// Input. Mouse, Keybaord, etc
			Game,			// Game. Game logic
			Render,			// Render. Rendering Code.

			Idle,			// Everything Else. Threads [Checks / Messaging], Messaging, File I/O, Resources, etc.
		};

	public:

		/*
		
		*/
		Module(_Class c, _Priority p = Module::Normal, Boolean system = false) : _class(c), _priority(p), _system(system)
		{

		}

		/*
		
		*/
		virtual ~Module()
		{

		}

		/*
			Get the Priority of the Module
		*/
		const inline Int32 priority() const override { return _class * PRIORITY_MULTIPLIER + _priority; }


		/*
			Modules by Default are NOT system Modules!
		*/
		const inline Boolean isSystem() const override { return _system; }

		/*
			Temporary
		*/
	//	void onStop() override { onPause(); }
	//	void onStart() override { onResume(); }

		// Should the Engine be a dependancy ?
	//	void pause() { return; }	// Tell the Engine to Pause ME
	//	void resume(){ return; }	// Tell the Engine to Resume ME


		/*
		const std::string operator()
		{
			return "Module: ";
		}
		*/

	private:
		Boolean _system = false;
		_Class _class = Module::Idle;
		_Priority _priority = Module::Highest;
	};

}

#endif