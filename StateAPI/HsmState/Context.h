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
		// ��ʼ״̬��
		bool Start(std::string name);

		// ����һ��״̬
		// [in] state ״̬������Context����ʱ���ڲ��ͷ�state
		// [in] name  ״̬���ƣ�Ϊ������Ϊtypedname��ֵ
		// [in] father_name ��״̬������
		// [out] ����state
		State* CreateState(State* state, std::string name, std::string father_name = "");

		// ���µ�ǰ״̬
		void Update();

		// ͬ���¼�
		// ����һ���¼����ṩ��root״̬�͵�ǰ״̬����
		// �����ǰ״̬����״̬���򻹻����״̬����
		void SendEvent(EventData event_data);

		// �첽�¼�
		void SendAsyncEvent(EventData event_data);

		// ��ȡ��ǰ״̬����
		std::string GetCurStateName();

	private:
		// ״̬�л�
		void TransForState(std::string name);

		// �ݹ�send
		void RecursiveSend(NodeState& node_state, EventData& event_data);

		std::unordered_map<std::string, NodeState> _states; // ״̬�б�
		NodeState _cur_node_state; // ��ǰ״̬��
		std::string _cur_name;

		std::string _root_name;    // ��״̬��
	};
}

#endif // !STATE_H_
