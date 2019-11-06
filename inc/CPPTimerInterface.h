#pragma once
#ifndef SRC_CPPTIMERINTERFACE_H_
#define SRC_CPPTIMERINTERFACE_H_


class TimersTask
{
public:
	void TimerStart(void)
	{

	}
};



class TimerTask:public TimersTask
{

private:

	int m_int;
	int m_int1;

public:


	TimerTask(int t_int) :
		m_int(t_int),
		m_int1(0)
	{

	}

	int GetInt()
	{
		return this->m_int;
	}



	TimerTask() 
	{
	}



	/* Destructor */
	~TimerTask() 
	{
	}


	void Init(void);


	/*! Getter and Setter functions. */
	int getTimeMs() const 
	{
		return m_int;
	}

	void setTimeMs(int timeMs) 
	{
		m_int = timeMs;
	}
};
//
class CPPTimerInterface : public TimerTask {

private:
		TimerTask* tasks[10];
public:

	/* Constructor */
	CPPTimerInterface()
	{
	}


//		for (int i = 0; i < MAX_TIMER; i++)
//		{
//			this->tasks[i] = sc_null;
//		}
//	}
//
	/* Destructor */
	virtual ~CPPTimerInterface()
	{
//		cancel();
	}
//
//	/*!
//		This function will be called for each time event that is relevant for a state when a state will be entered.
//		\param evid An unique identifier of the event.
//		\time_ms The time in milli seconds
//		\periodic Indicates the the time event must be raised periodically until the timer is unset
//	*/
//	virtual void setTimer(TimedStatemachineInterface* statemachine,
//		sc_eventid event,
//		sc_integer time,
//		sc_boolean isPeriodic);
//
//	/*!
//		This function will be called for each time event that is relevant for a state when a state will be left.
//		\param evid An unique identifier of the event.
//	*/
//	virtual void unsetTimer(TimedStatemachineInterface* statemachine,
//		sc_eventid event);
//
//	/*!
//		This function must be called by the user. The elapsed time must be calculated every time, the function gets
//		gets called.
//	 */
//	void updateActiveTimer(TimedStatemachineInterface* statemachine,
//		long elapsed_ms);
//
//	/* ! Cancel timer service. */
//	virtual void cancel();
};
//
//
#endif /* SRC_CPPTIMERINTERFACE_H_ */