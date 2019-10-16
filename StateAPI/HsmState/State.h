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

		// ����״̬ʱ���ã�������д
		virtual void start(){}

		// ����״̬���������ⲿ�����Ե���
		virtual void update(){}

		// ֹͣ״̬�ǵ��ã�������д
		virtual void stop(){}

		// �����¼���Ӧ�ص�����
		void set_event_func(std::function<EventDeal(EventData&)> func);

		EventDeal RunEventFunc(EventData& event_data); 

		void SetContext(Context* context);

		// �л�״̬
		// [in] name ״̬����
		void TransState(std::string name);

	private:
		std::function<EventDeal(EventData&)> _event_func;
		Context *_context;
	};
}
#endif // !STATE_H_



