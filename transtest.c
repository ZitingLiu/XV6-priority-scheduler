//ZitingLiu 002981429 GuanqiLi 001585017
#include "types.h"
#include "stat.h"
#include "user.h"

int main(){
  int x = 3;
  printf(1,"physical address of variable in stack\n");
  int a1 = translate((int)x);
  printf(1,"virtual address of stack var\n");
  rtranslate(a1);

  int *arr = (int*) malloc(200*sizeof(int));
  printf(1,"physical address of heap variable arr[0]\n");
  int a2 = translate((int)arr);
  printf(1,"virtual address of heap var\n");
  rtranslate(a2);
  
  printf(1,"physical address of heap variable arr[1]\n");
  int a3 = translate((int)arr+1);
  printf(1,"virtual address of heap(+1) var\n");
  rtranslate(a3);

  printf(1,"physical address of address: 0x80000000\n");
  translate(0x80000000);
  printf(1,"physical address of address: 0x800000001\n");
  translate(0x80000001);
  printf(1,"physical address of address: 0x900000000\n");
  translate(0x90000000);
  printf(1,"virtual address of: 0x0\n");
  rtranslate(0x0);
  printf(1,"virtual address of: 0x1\n");
  rtranslate(0x1);

  free(arr);
  exit();
  return 0;
}
