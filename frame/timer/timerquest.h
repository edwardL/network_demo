#ifndef TIMERQUEST_H
#define TIMERQUEST_H
#include <set>
#include <map>

typedef  void (*func)(void* arg);
class TimerQuest;
class TimerQuestItem
{
public:
	TimerQuestItem(unsigned int id, TimerQuest* quest, func quest_func,double delay_time);
	~TimerQuestItem();
	
	/* 执行对应Quest 一次
	@Return true 表示运行结束后被删除
	*/
	 bool Run();

public:
	unsigned int m_id;
	TimerQuest* m_parent;
	func m_timer_func;

	bool m_is_always_run;
	double m_next_run_time;
	double m_delay_time;
};

class TimerQuest
{
private:
	TimerQuest();
	~TimerQuest();

public:
	static TimerQuest* getInstance();
	void Update(double now_time, double elapse_time);

	bool _IsQuestAlive(unsigned int id);

	unsigned int AddDelayQuest(func quest_func, double delay_time, bool run_forever = false);
	void CancelQuest(unsigned int id);
	void Stop();

private:
	unsigned int m_id_count;
	double m_now_time;
	std::set<unsigned int> m_keep_id_set;

	typedef std::multimap<double,TimerQuestItem*> TimerQuestItemMap;
	TimerQuestItemMap m_timer_quest_map;
};


#endif