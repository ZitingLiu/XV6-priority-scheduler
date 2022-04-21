//ZitingLiu 002981429 GuanqiLi 001585017
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[]) //pass argument & call change priority function
{
  int priority, pid;
  pid = atoi(argv[1]);
  priority = atoi(argv[2]);
  chpr(pid, priority);
  exit();
}