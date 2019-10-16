#ifndef _ONE_DAY_STATE_TEST_H_
#define _ONE_DAY_STATE_TEST_H_
#include "Context.h"
#include "State.h"
#include "Event.h"
#include <iostream>

using namespace HsmState;
bool run = true;

enum EventS
{
	belazy = 0, // ÍµÀÁÊÂ¼þ
};

// ¿ªÊ¼×´Ì¬
class StartState : public State
{
public:
	void start()
	{
		std::cout << "StartState start" << std::endl;
	}

	void stop()
	{
		std::cout << "StartState stop" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			TransState("HungerState");
		}
	}

	int time = 0;
};

// ¼¢¶ö×´Ì¬
class HungerState : public State
{
public:
	void start()
	{
		std::cout << "HungerState start" << std::endl;
	}

	void stop()
	{
		std::cout << "HungerState stop" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			TransState("Dinner");
		}
	}

	int time = 0;
};

class Dinner : public State
{
public:
	void start()
	{
		std::cout << "Dinner start" << std::endl;
	}

	void stop()
	{
		std::cout << "Dinner stop" << std::endl;
	}

	void update()
	{
		TransState("DoTheCookingState");
	}
};

// ×ö·¹×´Ì¬
class DoTheCookingState : public State
{
public:
	void start()
	{
		std::cout << "DoTheCookingState start" << std::endl;
	}

	void stop()
	{
		std::cout << "DoTheCookingState stop" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 60)
		{
			TransState("EatState");
		}
	}

	int time = 0;
};


// ³Ô·¹×´Ì¬
class EatState : public State
{
public:
	void start()
	{
		std::cout << "EatState start" << std::endl;
	}

	void stop()
	{
		std::cout << "EatState stop" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 5)
		{
			TransState("SleepState");
		}
	}

	int time = 0;
};


// ·¹ºóË¯¾õ×´Ì¬
class SleepState : public State
{
public:
	void start()
	{
		std::cout << "SleepState start" << std::endl;
	}

	void stop()
	{
		std::cout << "SleepState stop" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 30)
		{
			TransState("WorkState");
		}
	}

	int time = 0;
};

// ¹¤×÷×´Ì¬
class WorkState : public State
{
public:
	void start()
	{
		std::cout << "WorkState start" << std::endl;

		std::function<EventDeal(EventData&)> func = std::bind(&WorkState::DealEvent, this, std::placeholders::_1);;
		set_event_func(func);
	}

	void stop()
	{
		std::cout << "WorkState stop" << std::endl;
	}

	EventDeal DealEvent(EventData& event_data)
	{
		switch ((EventS)event_data._event_type)
		{
		case belazy:
			TransState("LoafOnAJob");
			break;
		default:
			break;
		}
		return keep_on;
	}

	void update()
	{
		time++;
		if (time == 180)
		{
			run = false;
		}
	}

	int time = 0;
};

// ¹¤×÷ÃþÓã×´Ì¬
class LoafOnAJob : public State
{
public:
	void start()
	{
		time = 0;
		std::cout << "LoafOnAJob start" << std::endl;
	}

	void stop()
	{
		std::cout << "LoafOnAJob stop" << std::endl;
	}

	void update()
	{
		time++;
		if (time == 10)
		{
			TransState("WorkState");
		}
	}

	int time = 0;
};

#endif // !_ONE_DAY_STATE_TEST_H