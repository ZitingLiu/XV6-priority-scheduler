
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

int sys_date(void)
{
  struct rtcdate* d;
  argptr(0,(void *)&d, sizeof(*d));
  cmostime(d);
  return 0;

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
sys_getrpid(void)
{
  return getrpid();
}

int
sys_chpr(void)
{
  int pid, pr;
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &pr) < 0)
    return -1;

  return chpr(pid, pr);
}


int 
sys_translate(void)
{
  int Va;
  if (argint(0, &Va) <0) return -1;
  struct proc* p = myproc();
  uint Pa;
  pde_t *pgdir , *pgtab, *pde;
  pgdir = p->pgdir;
  pde = &pgdir[PDX(Va)];
  if(*pde & PTE_P){
    pgtab = (pte_t*)P2V(PTE_ADDR(*pde));
  }
  else{
    cprintf("invalid !\n\n");
    return -2;
  }
  if(!(*pde & PTE_U)){
    cprintf("Not user-available\n");
  }
  
  pte_t *pte;
  pte = &pgtab[PTX(Va)];
  Pa = (int)(PTE_ADDR(*pte))+(Va&0xFFF);
  cprintf("Virtual Address: 0x%x\n", Va);
  cprintf("Physical Address: 0x%x\n\n", Pa);
  return Pa;
}

int 
sys_rtranslate(void){
  int Pa;
  if (argint(0, &Pa) <0) return -1;
  struct proc* p = myproc();
  int Va;
  pde_t *pgdir, *pgtab, *pde;
  pgdir = p->pgdir;
  pde = &pgdir[0];
  pgtab = P2V(PTE_ADDR(*pde));
  int i=0;
  while(PTX(pgtab[i]) !=PTX(Pa)){
     ++i;
     if (pgtab[i] == 0){
       cprintf("No matching virtual address\n");
       cprintf("But in cheating, the physical address of 0x%x is 0x%x\n\n",Pa, P2V(Pa));
       return 0;
     }
  }
  Va =(i<<12) + (Pa & 0xFFF);
  cprintf("Physical Address: 0x%x\n", Pa);
  cprintf("Virtual Address: 0x%x\n\n", Va);
  return 0;
}

