#include "port.h"
#include "core.h"

void signal(struct task_type** task)
{
   __disable_interrupts();

   (*task)->sem->count++;
   __enable_interrupts();
}
void wait_sched(void)
{
      		
		if (SchedTask->sem->count < 0)
			SchedTask->sem->count=0;
			/*block*/

		while (!SchedTask->sem->count);
		
			SchedTask->sem->count--;
		
}

struct msg_box* wait(struct task_type** task, boolean busy_wait)
{
   struct task_type* current_task=*task;
   
   if (current_task->sem->count <= 0)
   {
      current_task->sem->count=0;
	  /*block*/

     /* allow scheduler to jump in from time to time to allow other tasks to run */
	  while (!current_task->sem->count)
	  { 
		
		 SAVE_CONTEXT(current_task->env);		  
		 if (!JMP_OCCURED())
		    /* let other tasks run */
		     SCHEDULER_HOOK();
			 		 		  
	  }	            
   } 
      current_task->sem->count--;
	  
   return current_task->msg;
}



/*(volatile struct 
{
   struct msg_box * msg[MAX_MSG_CNT];
   UINT8 top_idx;
} msg_fifo;

UINT8 find_msg(struct msg_box* msg)
{
   for (UINT8 i=msg_fifo.top_idx;i >= 0; i--)
      if (msg_fifo.msg[i] == msg)
	  {
          return i;
      }
}*/
void init_task(struct task_type** task, void_func_ptr initializer)
{
   if (*task == NULLPTR)
   {
      *task=(struct task_type *)allocate_mem(sizeof(struct task_type));
      (*task)->msg=(struct msg_box*)allocate_mem(sizeof(struct msg_box));
      (*task)->sem=(struct semaphore*)allocate_mem(sizeof(struct semaphore));
   }
   (*task)->msg->val=0;
   (*task)->msg->sender=NULLPTR;
   (*task)->sem->count=0;
   (*task)->status=STOPPED;
   (*task)->initialize=initializer;
   (*task)->env=0;
}
void delete_task(struct task_type**task)
{
   deallocate_mem((*task)->msg);
   deallocate_mem((*task)->sem);
   deallocate_mem((*task));
}
/*
struct msg_box * top(void)
{
    return msg_fifo.msg[msg_fifo.top_idx];
}*/

/*void debounce_button_task(void)
{
   UINT8 Samples[NUM_SAMPLES];
   UINT8 index=0;

   make sure Samples is in a known good state 
   for (UINT8 i=0; i < NUM_SAMPLES; i++)
      Samples[i]=0;

   while (TRUE)
   {
      struct msg_box* msg=wait(&DbnceBtnTask,FALSE);
	  __disable_interrupts();
      UINT8 andTerm = msg->val;
      UINT8 orTerm = msg->val;

      Samples[index++] = msg->val;
      if (index >= NUM_SAMPLES)
         index = 0;

      for (int j = 1; j < NUM_SAMPLES; j++)
      {
         andTerm &= Samples[j];
         orTerm |= Samples[j];
      }
   
      msg->val = (msg->val & orTerm) | andTerm;
	  msg->sender = DbnceBtnTask;
	  send_msg(msg,BtnTask);
      __enable_interrupts();
   }
}*/

/* lock*/
void acquire_lock(void)
{
    int locked = 0;
	__disable_interrupts();
	do
	{
	    lockvar++;
		if (lockvar != 1)
		{
		   lockvar--;
		  
        }
		else
		{
		   locked=1;
        }
     }
	 while (!locked);
}

/* unlock */
void unlock(void)
{
   lockvar--;
   __enable_interrupts();
}
/*void remove_msg(struct msg_box* msg)
{
   UINT8 idx=find_msg(msg);
   deallocate_mem(msg_fifo.msg[idx]);
   msg_fifo.msg[idx]->val=0;
   msg_fifo.msg[idx]->msg_id=NONE;
   if (idx==msg_fifo.top_idx)
      msg_fifo.top_idx--;
}*/

void reset_task(struct task_type** task)
{
   (*task)->msg->val=0;
   (*task)->msg->sender=NULLPTR;
   (*task)->sem->count=0;
   (*task)->env=0;
}

void send_msg(volatile struct msg_box** msg,struct task_type** task)
{
   struct msg_box* new_msg=(struct msg_box *)allocate_mem(sizeof(struct msg_box));
   new_msg->val=(*msg)->val;
   new_msg->sender=(*msg)->sender;
   (*task)->msg=new_msg;

   /* put msg in fifo */
   /*msg_fifo.top_idx++;
   msg_fifo.msg[msg_fifo.top_idx]=new_msg;*/
   
   signal(task);
	         
}

void button_pushed_task(void)
{

   /* wait for proper message*/
   while(TRUE)
   {
      struct msg_box* msg=wait(&BtnTask,FALSE);
         __disable_interrupts();
	     /* from interrupt */
         __watchdog_reset();
         ENABLE_DBNC_TMR();
		 message->val=msg->val;
		 message->sender=BtnTask;
         
         send_msg(&message, &LEDTask);
         ENABLE_LED_TMR();
      __enable_interrupts();
   }
}

void start_sched(void)
{
    message=(struct msg_box*)allocate_mem(sizeof(struct msg_box));
    init_task(&BtnTask, &button_pushed_task);
    init_task(&LEDTask, &LED_cycle_task);
	init_task(&WDTTask, &WDT_LED_cycle_task);
    init_task(&SchedTask, &sched_task);


	/*for (UINT8 i=0; i < MAX_TASK_CNT; i++)
       task_list[i]=(struct task_state*)allocate_mem(sizeof(struct task_state));*/
	
	task_list[0]=BtnTask;
	task_list[1]=LEDTask;
	task_list[2]=WDTTask;

	init_hardware();
	
	/* initialize ctx_sw_res to known good val */
	ctx_sw_res=0;
    sched_env=0;
	cur_stk_ptr=0;
		
	/* start scheduler */
	sched_task();
}

void sched_task(void)
{
	UINT8 tsk_idx=0;
	 
  while (tsk_idx < MAX_TASK_CNT)
  {
      SAVE_CONTEXT_SCHED();
	  if (!JMP_OCCURED())
      (task_list[tsk_idx++])->initialize();
  }   
   
   __enable_interrupts();
       
   while (TRUE)
   {  
	  wait_sched();
	  
	  if (tsk_idx >= MAX_TASK_CNT)
	     tsk_idx=0;  
	 
	  SAVE_CONTEXT_SCHED();
	 
	  /* check this task */
	  TASK_HOOK(task_list[tsk_idx++]->env);		     	     		 
   }        
}

void LED_cycle_task(void)
{
    UINT8 led_offset_below=1;
    UINT8 led_offset_above=1;

	UINT8 btn_idx=0;
    while (TRUE)
	{
	   struct msg_box* msg=wait(&LEDTask,FALSE);
       __disable_interrupts();

	   /* check what kind of msg is this*/
       if (msg->sender == BtnTask)
	   {
	   
	      /* start LED cycle again at button press*/
		  LED_ON(msg->val);
		  btn_idx=msg->val;
		  led_offset_above=1;
		  led_offset_below=1;
		  reset_task(&LEDTask);
       }
	   else if (msg->sender == WDTTask)
	   {
	      btn_idx=msg->val;
		  LED_ON(msg->val);
		  led_offset_above=1;
		  led_offset_below=0;
		  reset_task(&LEDTask);
		  ENABLE_LED_TMR();
	   } 
	   else if (msg->sender == NULLPTR)
	   {
	      if (btn_idx-led_offset_below < 0)
		  {
		     led_offset_below=0;
          }
		  else
		  {
		     LED_ON(btn_idx - led_offset_below);
		     led_offset_below++;
          }
		  if (btn_idx+led_offset_above > LED_CNT-1)
		  {
		     led_offset_above=0;
          }
		  else
		  {
             LED_ON(btn_idx + led_offset_above);
             led_offset_above++;
          }

       }
	   __enable_interrupts();
    }
}

void WDT_LED_cycle_task (void)
{
   UINT8 temp_dly=WDT_MAX_TO;
   UINT8 WDT_cur_dly=DLY_WO_LEDS;
   const UINT8 WDT_delays[]={WDT_MAX_TO,WDT_STP_DWN1,
                             WDT_STP_DWN2,WDT_STP_DWN3};
   while (TRUE)
   {
      wait(&WDTTask,FALSE);
	  __disable_interrupts();
      for (UINT8 i=0; i < sizeof(WDT_delays)/sizeof(WDT_delays[0]); i++)
         temp_dly=MIN(ABS(WDT_cur_dly-WDT_delays[i]),temp_dly);
      WDT_cur_dly=temp_dly;
	  if (!WDT_cur_dly)
	  {
	     /* delay has elasped */
		 WDT_cur_dly=DLY_WO_LEDS;
         
		 DISABLE_LED_TMR();

		 /* cycle all leds */
		 message->val=0;
		 message->sender=WDTTask;
		 send_msg(&message,&LEDTask);
      }
      temp_dly=WDT_MAX_TO;
	  __enable_interrupts();
   }
} 
