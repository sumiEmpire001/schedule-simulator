#pragma once
#include <cstddef>
#include <climits>
namespace lord_sumi {
template<size_t N> class Scheduler {
 struct Job{unsigned arrival,burst,remaining,completion,first;};
 Job jobs_[N];size_t count_=0;bool fault_=false;
public:
 bool add(unsigned arrival,unsigned burst){if(fault_)return false;if(!burst||count_==N){fault_=true;return false;}jobs_[count_++]={arrival,burst,burst,0,UINT_MAX};return true;}
 bool fault()const{return fault_;}void reset(){count_=0;fault_=false;}
 struct Result{bool valid;unsigned completion[N];unsigned waiting[N];unsigned response[N];unsigned turnaround[N];};
 Result fcfs()const{
  Result r={false,{},{},{},{}};if(fault_)return r;
  unsigned time=0;
  for(size_t i=0;i<count_;++i){unsigned start=time>jobs_[i].arrival?time:jobs_[i].arrival;if(UINT_MAX-start<jobs_[i].burst)return r;time=start+jobs_[i].burst;r.completion[i]=time;r.response[i]=start-jobs_[i].arrival;r.turnaround[i]=time-jobs_[i].arrival;r.waiting[i]=r.turnaround[i]-jobs_[i].burst;}
  r.valid=true;return r;
 }
};
}