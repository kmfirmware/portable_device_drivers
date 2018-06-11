#ifndef CORE_H
#define CORE_H
#include "other.h"


#define MAX_TASK_CNT 3
#define HASH_CODE(ptr) (ptr%(MAX_TASK_CNT+1))
#define MIN(x1,x2) ((x1) > (x2) ? (x2):(x1))
#define MAX(x1,x2) ((x1) > (x2) ? (x1):(x2))
#define ABS(x) ((x)>=0 ?(x):-(x))


typedef void (*void_func_ptr) (void);

/*boolean (*set_mutex)(struct task_type**);*/

/* data structures */
volatile UINT8 lockvar;
volatile UINT8 ctx_sw_res;
JMP_DATA sched_env;
JMP_DATA cur_stk_ptr;


volatile struct semaphore
{
   int count;
};

enum task_state_type {STOPPED,WAITING,RUNNING};
volatile struct task_type
{
   struct msg_box * msg;
   struct semaphore * sem;
   enum task_state_type status;
   void_func_ptr initialize;
   JMP_DATA env;
};


/*struct task_state
{
   struct task_type * task;
   enum task_state_type status;
};*/
struct task_type* task_list[MAX_TASK_CNT];

/* function declarations */
struct msg_box* wait(struct task_type **, boolean);
void init_task(struct task_type **, void_func_ptr);
void delete_task(struct task_type **);
void debounce_button_task(void);
void acquire_lock(void);
void unlock(void);
void reset_task(struct task_type **);
void button_pushed_task(void);
void start_sched(void);
void LED_cycle_task(void);
void WDT_LED_cycle_task (void);
void wait_sched(void);
void sched_task(void);
/*
boolean no_lock_sched(struct task_type **);
boolean lock_sched(struct task_type **);*/

#endif
