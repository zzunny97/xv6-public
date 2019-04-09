#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_halt(void)
{
  outw(0x604, 0x2000);
  return 0;
}

int
sys_getnice(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return getnice(pid);
}

int
sys_setnice(void)
{
	int pid, value;
	
	if(argint(0, &pid) < 0)
		return -1;
	if(argint(1, &value) < 0)
		return -1;
	return setnice(pid, value);
}

void
sys_ps(void)
{
	int pid;

	if(argint(0, &pid) >= 0){
    ps(pid);
  }
}

int
sys_thread_create(void)
{
  cprintf("func: sys_thread_create\n");
  //void *(*function)(void*), *arg, *stack;
  /*
  if(argptr(0, (void*)&function, sizeof(void* (*)(void*)) < 0)){
    cprintf("111\n");
    return -1;
  }
  */
  /*
  if(argptr(0, (void*)&function, sizeof(void*)) < 0){
    cprintf("111\n");
    return -1;
  }
  if(argptr(1, (void*)&arg, sizeof(void*)) < 0){
    cprintf("222\n");
    return -1;
  }
  if(argptr(2, (void*)&stack, sizeof(void*)) < 0){
    cprintf("333\n");
    return -1;
  }
  */
  int function, arg, stack;
  if(argint(0, &function) < 0)
    return -1;
  if(argint(1, &arg) < 0)
    return -1;
  if(argint(2, &stack) < 0)
    return -1;
  return thread_create((void*)function, (void*)arg, (void*)stack);
}

void
sys_thread_exit(void)
{
  //void* retval;
  int retval;
  /*
  if(argptr(0, (void*)&retval, sizeof(void*)) < 0)
    return -1;
  */
  if(argint(0, &retval) < 0)
    return -1;
  thread_exit((void*)retval);
}

int
sys_thread_join(void)
{
  int tid;
  //void** retval;
  int retval;
  if(argint(0, &tid) < 0)
    return -1;
    /*
  if(argptr(1, (void**)&retval, sizeof(void**)) < 0)
    return -1;*/
  if(argint(1, &retval) < 0)
    return -1;
  return thread_join(tid, (void*)retval);
}

int
sys_gettid(void)
{
  int tid;
  if(argint(0, &tid) < 0)
    return -1;
  return gettid(tid);
}

