#include "Context.h"
#include "State.h"

namespace HsmState
{
	// 设置时间响应回调函数
	void State::set_event_func(std::function<EventDeal(EventData&)> func)
	{
		_event_func = func;
	}

	EventDeal State::RunEventFunc(EventData& event_data)
	{
		if (_event_func == nullptr)
			return keep_on;
		return _event_func(event_data);
	}

	void State::SetContext(Context* context)
	{
		_context = context;
	}

	void State::TransState(std::string name)
	{
		_context->TransForState(name);
	}
}