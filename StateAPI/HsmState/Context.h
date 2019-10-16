#ifndef _CONTEXT_H_
#define _CONTEXT_H_
#include "Event.h"
#include <string>
#include <unordered_map>
#include <thread>

namespace HsmState
{
	class State;
	struct NodeState
	{
		NodeState& operator = (const NodeState& n)
		{
			_state = n._state;
			_father_name = n._father_name;
			return *this;
		}
		State* _state;
		std::string _father_name;
	};

	class Context
	{
	public:
		friend class State;

		Context();

		~Context();
		// 开始状态机
		bool Start(std::string name);

		// 创建一个状态
		// [in] state 状态对象，在Context销毁时，内部释放state
		// [in] name  状态名称，为空名称为typedname的值
		// [in] father_name 父状态的名称
		// [out] 返回state
		State* CreateState(State* state, std::string name, std::string father_name = "");

		// 更新当前状态
		void Update();

		// 同步事件
		// 发送一个事件，提供给root状态和当前状态处理
		// 如果当前状态是子状态，则还会给父状态处理
		void SendEvent(EventData event_data);

		// 异步事件
		void SendAsyncEvent(EventData event_data);

		// 获取当前状态名称
		std::string GetCurStateName();

	private:
		// 状态切换
		void TransForState(std::string name);

		// 递归send
		void RecursiveSend(NodeState& node_state, EventData& event_data);

		std::unordered_map<std::string, NodeState> _states; // 状态列表
		NodeState _cur_node_state; // 当前状态名
		std::string _cur_name;

		std::string _root_name;    // 根状态名
	};
}

#endif // !STATE_H_
