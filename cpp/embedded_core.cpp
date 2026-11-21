#include <stdint.h>
#include <stddef.h>
#include <limits.h>
namespace embedded_schedule {
enum Status { OK, INVALID, CAPACITY, OVERFLOW, DEADLOCK };
enum Policy { FCFS, SJF };
struct Job { uint16_t id; uint32_t arrival, burst; };
struct Result { uint16_t id; uint32_t start, finish, wait, turnaround; };
template<size_t N> class Scheduler {
 Job jobs_[N]; size_t count_; bool fault_;
public:
 Scheduler():count_(0),fault_(false){}
 bool add(Job j) { if(fault_)return false; if(!j.burst||count_>=N){fault_=true;return false;} for(size_t i=0;i<count_;++i)if(jobs_[i].id==j.id){fault_=true;return false;} jobs_[count_++]=j;return true; }
 Status run(Policy policy, Result* out,size_t capacity) {
  if(fault_)return INVALID;
  if(!out||capacity<count_||!(policy==FCFS||policy==SJF))return INVALID;
  bool used[N]={}; uint32_t clock=0;
  for(size_t k=0;k<count_;++k){
   size_t pick=N; uint32_t earliest=UINT32_MAX;
   for(size_t i=0;i<count_;++i)if(!used[i]&&jobs_[i].arrival<earliest)earliest=jobs_[i].arrival;
   if(earliest==UINT32_MAX)return DEADLOCK;
   if(clock<earliest)clock=earliest;
   for(size_t i=0;i<count_;++i)if(!used[i]&&jobs_[i].arrival<=clock){
    if(pick==N || (policy==FCFS ? (jobs_[i].arrival<jobs_[pick].arrival) : (jobs_[i].burst<jobs_[pick].burst || (jobs_[i].burst==jobs_[pick].burst&&jobs_[i].arrival<jobs_[pick].arrival))))pick=i;
   }
   if(pick==N)return DEADLOCK;
   const Job &j=jobs_[pick]; if(j.burst>UINT32_MAX-clock)return OVERFLOW;
   uint32_t finish=clock+j.burst;
   out[k]=Result{j.id,clock,finish,clock-j.arrival,finish-j.arrival};
   clock=finish;used[pick]=true;
  }
  return OK;
 }
 bool faulted()const{return fault_;}
 void reset(){count_=0;fault_=false;}
};
}
#ifdef EMBEDDED_TEST
#include <assert.h>
int main(){using namespace embedded_schedule; Scheduler<3> s;assert(s.add({1,0,5}));assert(s.add({2,1,1}));Result r[3];assert(s.run(SJF,r,3)==OK);assert(r[0].id==1&&r[1].id==2&&r[1].wait==4);assert(!s.add({1,0,1}));assert(s.faulted());s.reset();assert(s.add({7,UINT32_MAX,2}));assert(s.run(FCFS,r,3)==OVERFLOW);assert(s.run(FCFS,nullptr,0)==INVALID);return 0;}
#endif
