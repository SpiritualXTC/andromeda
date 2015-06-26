#ifndef _ANDROMEDA_INPUT_ACTION_H_
#define _ANDROMEDA_INPUT_ACTION_H_

#include <list>
#include <unordered_map>

#include "../stddef.h"

namespace andromeda
{
	struct ActionEventArgs
	{

	};




	class IAction
	{
	public:
		IAction(){}
		virtual ~IAction(){}
	private:
	};



	class ActionKeyboard : public IAction
	{
	public:
		ActionKeyboard(){}
		virtual ~ActionKeyboard(){}

	private:
	};


	class ActionMouseButton : public IAction
	{
	public:
		ActionMouseButton() {}
		virtual ~ActionMouseButton() {}

	private:
	
	};


	

	/*
		List of actions that can trigger an event
	*/
	class ActionList
	{
	public:
		ActionList();
		virtual ~ActionList();

	private:
		std::list<IAction*> _actions;
	};

	/*
		Action Mapping: This should be a LOWEST PRIORITY Input Module
	*/
	class Action
	{
	public:
		Action();
		virtual ~Action();


		Boolean addAction(Int32 actionId);
		Boolean removeAction(Int32 actionId);

	private:
		std::unordered_map<Int32, ActionList*> _actions;
	};
}

#endif