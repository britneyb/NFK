/* Count Down Timer */
#ifndef CountDownTimer_h
#define CountDownTimer_h

#include<Arduino.h>

class CountDownTimer
{
  public:
    CountDownTimer() {}
	
	boolean Timer()
	{
	  static unsigned long duration = 1000000; // 1 second
	  timeFlag = false;
	  if (!Stop && !Paused) // if not Stopped or Paused, run timer
	  {
		if ((_micro = micros()) - time > duration ) // check the time difference and see if 1 second has elapsed
		{
		  Clock--;
		  timeFlag = true;

		  if (Clock == 0) // check to see if the clock is 0
			Stop = true; // If so, stop the timer
			
		  _micro < time ? time = _micro : time += duration; // check to see if micros() has rolled over, if not, then increment "time" by duration
		}
	  }
	  return !Stop; // return the state of the timer
	}

	void ResetTimer()
	{
	  SetTimer(R_clock);
	  Stop = false;
	}

	void StartTimer()
	{
	  Watch = micros();
	  Stop = false;
	  Paused = false;
	}

	void StopTimer()
	{
	  Stop = true;
	}

	void StopTimerAt(unsigned long hours, unsigned long minutes, unsigned long seconds)
	{
	  if (TimeCheck(hours, minutes, seconds) )
		Stop = true;
	}

	void PauseTimer()
	{
	  Paused = true;
	}

	void ResumeTimer() // You can resume the timer if you ever stop it.
	{
	  Paused = false;
	}

	void SetTimer(unsigned long hours, unsigned long minutes, unsigned long seconds)
	{
	  // This handles invalid time overflow ie 1(H), 0(M), 120(S) -> 1, 2, 0
	  unsigned long _S = (seconds / 60), _M = (minutes / 60);
	  if(_S) minutes += _S;
	  if(_M) hours += _M;
	  
	  Clock = (hours * 3600) + (minutes * 60) + (seconds % 60);
	  R_clock = Clock;
	  Stop = false;
	}

	void SetTimer(unsigned long seconds)
	{
	 // StartTimer(seconds / 3600, (seconds / 3600) / 60, seconds % 60);
	  Clock = seconds;
	  R_clock = Clock;
	  Stop = false;
	}

	long ShowHours()
	{
	  return Clock / 3600;
	}

	long ShowMinutes()
	{
	  return (Clock / 60) % 60;
	}

	long ShowSeconds()
	{
	  return Clock % 60;
	}

	unsigned long ShowMilliSeconds()
	{
	  return (_micro - Watch)/ 1000.0;
	}

	unsigned long ShowMicroSeconds()
	{
	  return _micro - Watch;
	}

	boolean TimeHasChanged()
	{
	  return timeFlag;
	}

	boolean TimeCheck(unsigned long hours, unsigned long minutes, unsigned long seconds) // output true if timer equals requested time
	{
	  return (hours == ShowHours() && minutes == ShowMinutes() && seconds == ShowSeconds());
	}
	
    private:
		unsigned long Watch, _micro, time = micros();
		unsigned long Clock = 0, R_clock;
		boolean Reset = false, Stop = false, Paused = false;
		volatile boolean timeFlag = false;
};

#endif
