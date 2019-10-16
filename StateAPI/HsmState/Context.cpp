#include "Context.h"
#include "State.h"

namespace HsmState
{
	Context::Context()
	{

	}

	Context::~Context()
	{
		if (_cur_node_state._state != nullptr)
		{
			_cur_node_state._state->stop();
		}

		for (auto iter : _states)
		{
			if (iter.second._state)
			{
				delete iter.second._state;
				iter.second._state = nullptr;
			}
		}
		_states.clear();
	}

	// 开始状态机
	bool Context::Start(std::string name)
	{
		std::unordered_map<std::string, NodeState>::iterator iter_map = _states.find(name);
		if (iter_map != _states.end())
		{
			_cur_node_state = iter_map->second;
			_cur_name = iter_map->first;
			iter_map->second._state->start();
		}
		return false;
	}

	// 创建一个状态
	// [in] state 状态对象，在Context销毁时，内部释放state
	// [in] name  状态名称，为空名称为typedname的值
	// [in] father_name 父状态的名称
	// [out] 返回state
	State* Context::CreateState(State* state, std::string name, std::string father_name)
	{
		NodeState node_state;
		node_state._state = state;
		node_state._state->SetContext(this);
		node_state._father_name = father_name;
		_states[name] = node_state;
		return state;
	}

	// 更新当前状态
	void Context::Update()
	{
		_cur_node_state._state->update();
	}

	// 同步事件
	// 发送一个事件，提供给root状态和当前状态处理
	// 如果当前状态是子状态，则还会给父状态处理
	void Context::SendEvent(EventData event_data)
	{
		RecursiveSend(_cur_node_state, event_data);
	}

	// 异步事件
	void Context::SendAsyncEvent(EventData event_data)
	{
		// todo 待实现
	}

	std::string Context::GetCurStateName()
	{
		return _cur_name;
	}

	// 递归send
	void Context::RecursiveSend(NodeState& node_state, EventData& event_data)
	{
		EventDeal event_deal = node_state._state->RunEventFunc(event_data);
		if (event_deal == keep_on
			&& !node_state._father_name.empty())
		{
			std::unordered_map<std::string, NodeState>::iterator iter_map = _states.find(node_state._father_name);
			if (iter_map != _states.end())
			{
				RecursiveSend(iter_map->second, event_data);
			}
		}
	}

	void Context::TransForState(std::string name)
	{
		std::string str_name = std::string(name);
		std::unordered_map<std::string, NodeState>::iterator iter_map = _states.find(str_name);
		if (iter_map != _states.end())
		{
			// 停止上一个状态
			_cur_node_state._state->stop();

			// 初始化下一个状态
			_cur_node_state = iter_map->second;
			_cur_name = iter_map->first;
			_cur_node_state._state->start();
		}
	}
}