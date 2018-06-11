#ifndef OTHER_H
#define OTHER_H

volatile struct msg_box
{
    int val;
	struct task_type* sender;
} *message;


struct task_type* BtnTask;
struct task_type* DbnceBtnTask;
struct task_type* LEDTask;
struct task_type* SchedTask;
struct task_type* WDTTask;

void signal(struct task_type **);
void send_msg(volatile struct msg_box **,struct task_type **);

#endif
