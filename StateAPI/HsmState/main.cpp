#include "Context.h"
#include "State.h"
#include "OneDayStateTest.h"
#include "Factory.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <functional>

int main()
{
	Context* context = new Context();

	// ����״̬��
	Factory::CreateState(context, "StartState");
	Factory::CreateState(context, "HungerState");
	Factory::CreateState(context, "Dinner");
	Factory::CreateState(context, "DoTheCookingState", "Dinner");
	Factory::CreateState(context, "EatState", "Dinner");
	Factory::CreateState(context, "SleepState");
	Factory::CreateState(context, "WorkState");
	Factory::CreateState(context, "LoafOnAJob");

	// ��ʼ״̬��
	context->Start("StartState");

	int time = 0;
	while (run)
	{
		time++;
		std::this_thread::sleep_for(
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(10)));

		context->Update();

		// ���Ϊ����״̬��ÿ��60���ӷ���͵���¼�
		if (context->GetCurStateName() == "WorkState" 
			&& time % 60 == 0) 
		{
			EventData e = EventData((int)belazy);
			context->SendEvent(e);
		}
	}

	if (context)
	{
		delete context;
		context = nullptr;
	}

	std::cout << "state close" << std::endl;
	return 0;
}