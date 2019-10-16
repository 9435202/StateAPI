#ifndef _STATE_H_
#define _STATE_H_
#include "Event.h"
#include<functional>
#include<string>

namespace HsmState
{
	class Context;

	class State
	{
	public:

		// 进入状态时调用，子类重写
		virtual void start(){}

		// 更新状态，可以由外部周期性调用
		virtual void update(){}

		// 停止状态是调用，子类重写
		virtual void stop(){}

		// 设置事件响应回调函数
		void set_event_func(std::function<EventDeal(EventData&)> func);

		EventDeal RunEventFunc(EventData& event_data); 

		void SetContext(Context* context);

		// 切换状态
		// [in] name 状态名称
		void TransState(std::string name);

	private:
		std::function<EventDeal(EventData&)> _event_func;
		Context *_context;
	};
}
#endif // !STATE_H_



