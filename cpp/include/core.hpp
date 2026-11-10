#pragma once
#include <cstddef>
#include <cstdint>
namespace lord_sumi {
struct Job { uint32_t remaining; uint32_t executed; };
class RoundRobin {
 Job jobs_[16]{};size_t count_=0;size_t cursor_=0;bool valid_=true;
public:
 bool add(uint32_t burst){if(!burst||count_==16)return false;jobs_[count_++]={burst,0};return true;}
 bool tick(uint32_t quantum,size_t& jobId,uint32_t& elapsed){
  if(!quantum||!valid_)return false;
  for(size_t n=0;n<count_;++n){size_t i=(cursor_+n)%count_;if(jobs_[i].remaining){
   jobId=i;elapsed=jobs_[i].remaining<quantum?jobs_[i].remaining:quantum;
   jobs_[i].remaining-=elapsed;jobs_[i].executed+=elapsed;cursor_=(i+1)%count_;return true;
  }}return false;
 }
 uint32_t remaining(size_t i) const {return i<count_?jobs_[i].remaining:0;}
};
}