#ifndef _FACTORY_H_
#define _FACTORY_H_
#include "State.h"
#include "Context.h"
using namespace HsmState;
// 对象工厂
class Factory
{
public:
	static State* CreateState(Context* context, std::string name, std::string parent_name = "")
	{
		State* state = nullptr;
		if (name == "StartState")
		{
			state = new StartState();
		}
		else if (name == "HungerState")
		{
			state = new HungerState();
		}
		else if (name == "Dinner")
		{
			state = new Dinner();
		}
		else if (name == "DoTheCookingState")
		{
			state = new DoTheCookingState();
		}
		else if (name == "EatState")
		{
			state = new EatState();
		}
		else if (name == "SleepState")
		{
			state = new SleepState();
		}
		else if (name == "WorkState")
		{
			state = new WorkState();
		}
		else if (name == "LoafOnAJob")
		{
			state = new LoafOnAJob();
		}

		context->CreateState(state, name, parent_name);
		return state;
	}
};

#endif