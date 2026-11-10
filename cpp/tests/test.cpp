#include "core.hpp"
#include <cassert>
int main(){lord_sumi::RoundRobin r;assert(!r.add(0));assert(r.add(5)&&r.add(2));size_t id=99;uint32_t dt=0;assert(!r.tick(0,id,dt));assert(r.tick(2,id,dt)&&id==0&&dt==2);assert(r.tick(2,id,dt)&&id==1&&dt==2);assert(r.tick(2,id,dt)&&id==0&&dt==2);assert(r.tick(2,id,dt)&&id==0&&dt==1);assert(!r.tick(2,id,dt));}