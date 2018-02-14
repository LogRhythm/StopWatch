/**

Example usage: 
TriggerTimeStats is a helper for TimeStats
It is a scope triggered "save" that makes it easy to use without code bloat. 
The TriggerTimeStats and TimeStats adds overhead so it should only be used
when comparing relative speed of one operation vs another. It should not be
used in production code

TimeStats stats;
while(thread_loop) {
   ...
   { // scope around a function call that we want to instrument
      TriggerTimeStats trigger(stats);
      func(); 
   } // scope exits and `func` is measured. 
}


*/
#include "TimeStats.h"
#include "StopWatch.h"

class TriggerTimeStats {


 public:
   TriggerTimeStats(TimeStats& timeStats) : mTimeStats(timeStats) {
      mStopWatch.Restart();
   }

   ~TriggerTimeStats() {
      mTimeStats.Save(mStopWatch.ElapsedNs());
   }


 private:
   TimeStats& mTimeStats;
   StopWatch mStopWatch;
};