#include <stdio.h>
#include <malloc.h>
#include <cstring>
#include <iostream>
using namespace std;

char *Malloc()
{
  char *p=(char*)malloc(10);
  return p;
}

/*example1 There is a branch leaked in IfStmt*/
void BranchLeak(int nSize)
{
  char *p = Malloc();
  if(rand()%2)
  {
    //free(p);
    return;
  }
  cout<<*p;
  free(p);
}

/*example2 There is a branch leaked in IfStmt*/
void test_if_continue()
{
  for(int n=0;n<100;n++){
    void *a=malloc(10);
    if(a!=NULL){
      if(rand()%2){
        //free(a);
        continue;
      }
      else
        free(a);
    }
  }
}

/*example3*/
void test_example2()
{
  char *strb;
  strb=Malloc();
  //free(strb);
  strb=(char*)malloc(4);
  free(strb);
  return;
}

/*example4 aliasMissing*/
void test_aliasMissing()
{
  void *p=malloc(10);
  void *q=malloc(4);
  if(rand()%2){
    //free(p);
    p=q;
  }
  else
    free(q);
  free(p);
}

/*example5 exception*/
void test_exception()
{
  int *a = (int *)malloc(sizeof(int));
  try
  {
    if(a!=NULL)
    *a=1;
    //free(a);
    throw 1;
  }
  catch(int i){}
  free(a);
  return;
}

/*example6 memory_leak in a loop*/
int test_loop()
{
  int *a=(int *)malloc(sizeof(int));
  int p=2;
  while(a!=NULL&&p!=0)
  {
    if(a!=NULL)
    cout<<*a;
    p--;
  }
  //free(a);
  return 0;
}
void test11(void *q)
{
 if(rand()%2 == 0)
 free(q);
}
int test10()
{
  void *p=malloc(10);
 test11(p);
 if(rand()%2 == 0)
 free(p);
return 0;
}
