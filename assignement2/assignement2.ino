#include "Scheduler.h"
#include "ReadyTask.h"
#include "InitTask.h"
#include "SelectTask.h"
#include "MakeTask.h"
#include "ProdReadyTask.h"
#include "Display.h"
#include "CheckTask.h"
#define MAX_PROD 10

Scheduler scheduler;
Task* task0;
Task* task1;
Task* task2;
Task* task3;
Task* task4;
Task* task5;
void setup(){
  Serial.begin(9600);
  scheduler.init(25);
  task0 = new InitTask();
  task1 = new ReadyTask(7);
  task2 = new SelectTask(13,12,11,A1);
  task3 = new MakeTask(6);
  task4 = new ProdReadyTask(5,4);
  task5 = new CheckTask(A0,6);

  ((ReadyTask*) task1)->setDependencies(((SelectTask*)task2)->getDisplaying(),((InitTask*)task0)->getInitEnd(),((MakeTask*)task3)->getMaking(),((ProdReadyTask*)task4)->getWaiting(),((ProdReadyTask*)task4)->getRemoved());
  ((SelectTask*)task2)->setDependencies(((InitTask*)task0)->getInitEnd(),((ProdReadyTask*)task4)->getRemoved());
  ((MakeTask*)task3)->setDependencies(((SelectTask*)task2)->getSelectEnd(),((ProdReadyTask*)task4)->getRemoved());
  ((ProdReadyTask*)task4)->setDependencies(((MakeTask*)task3)->getProdReady(),((ReadyTask*)task1)->getReadyOn());

  task0->init(100);
  task1->init(100);
  task2->init(100);
  task3->init(25);
  task4->init(100);
  task5->init(100);
  
  scheduler.addTask(task0);
  scheduler.addTask(task1); 
  scheduler.addTask(task2);
  scheduler.addTask(task3);
  scheduler.addTask(task4);
  scheduler.addTask(task5);
  
  //5/TMAKING
}

void loop(){

  scheduler.schedule();
}

