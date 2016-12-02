#include "timerquest.h"
#include <vector>

TimerQuestItem::TimerQuestItem(unsigned int id, TimerQuest* quest, func quest_func,double delay_time)
	:m_id(id)
	,m_parent(quest)
	,m_timer_func(quest_func)
	,m_delay_time(delay_time)
{

}

TimerQuestItem::~TimerQuestItem()
{

}

bool TimerQuestItem::Run()
{
	// 由外界自主控制声明周期的任务
	if(!m_parent->_IsQuestAlive(m_id))
		return true;
	
	m_timer_func(NULL);
	if(m_is_always_run){
		m_next_run_time += m_delay_time;
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////
TimerQuest* TimerQuest::getInstance()
{
	static TimerQuest* _instance;
	if(_instance == NULL)
		_instance = new TimerQuest;
	return _instance;
}
TimerQuest::TimerQuest()
	:m_id_count(0)
	,m_now_time(0.0)
{

}

TimerQuest::~TimerQuest()
{
	Stop();
}

bool TimerQuest::_IsQuestAlive(unsigned int id)
{
	if(m_keep_id_set.find(id) != m_keep_id_set.end())
		return true;
	return false;
}

void TimerQuest::Stop()
{
	for(TimerQuestItemMap::iterator ihandle = m_timer_quest_map.begin(); ihandle != m_timer_quest_map.end(); ihandle++)
	{
		delete ihandle->second;
	}
	m_timer_quest_map.clear();
}

unsigned int TimerQuest::AddDelayQuest(func quest_func, double delay_time,  bool run_forever)
{
	// 延迟执行任务
	TimerQuestItem* quest = new TimerQuestItem(++m_id_count,this,quest_func,delay_time);
	quest->m_is_always_run = run_forever;
	quest->m_next_run_time = m_now_time + delay_time;

	m_timer_quest_map.insert(std::make_pair(quest->m_next_run_time,quest));
	m_keep_id_set.insert(quest->m_id);

	return quest->m_id;
}

void TimerQuest::Update(double now_time, double elapse_time)
{
	m_now_time = now_time;
	TimerQuestItemMap::iterator iquest = m_timer_quest_map.upper_bound(now_time);
	typedef std::vector<TimerQuestItem*> TimerQuestItemVector;
	TimerQuestItemVector tmp_quest_array;
	if(iquest == m_timer_quest_map.begin())
	{
		return;
	}
	for(TimerQuestItemMap::iterator i = m_timer_quest_map.begin(); i != iquest; ++i)
	{
		tmp_quest_array.push_back(i->second);
	}

	/// 删除到时间的item
	m_timer_quest_map.erase(m_timer_quest_map.begin(),iquest);

	// 逐项对到时间的任务进行处理
	for(size_t i = 0; i < tmp_quest_array.size(); i++)
	{
		TimerQuestItem* quest = tmp_quest_array[i];
		bool need_delete = quest->Run();
		if(!need_delete)
		{
			m_timer_quest_map.insert(std::make_pair(quest->m_next_run_time,quest));
		}
		else
		{
			CancelQuest(quest->m_id);
			delete quest;
		}
	}
}

void TimerQuest::CancelQuest(unsigned int id)
{
	m_keep_id_set.erase(id);
}
