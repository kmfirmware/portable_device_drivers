#include "port.h"
#include "other.h"

#include <stdlib.h>
extern float led_dly_time;

void debounce_timer_init(void)
{
    /* Program the timer with the value 
	you want which is the number of counts into TCNT0. */

WRITEREG(TCCR0A, WGM01|WGM00);
WRITEREG(TCCR0B, WGM02);
WRITEREG(OCR0A, TMR_TICKS(DBNC_INT_CONV,DBNC_DLY_TIME,DEBOUNCE_TMR_PRESCALER));
WRITEREG(TIMSK0, TOIE0);

/* Make sure Timer Counter 0 is Disabled*/
DISABLE_DBNC_TMR();
btn_timeout=FALSE;
}

void btn_interrupt_init(void)
{
   /* enable pullups*/
   WRITEREG(MCUCR,~PUD & READREG(MCUCR));
 
   /* set data direction for pins 0-3 as inputs */
   WRITEREG(DDRD,~MAXVAL(3) & READREG(DDRD));

   /* set data direction for pins 7-4 as inputs */
   WRITEREG(DDRE,MAXVAL(3) & READREG(DDRD));

   /*interrupt on rising edge*/
   WRITEREG(EICRA,ISC31|ISC30|ISC21|ISC20|ISC11|ISC10|ISC01|ISC00);

   /*interrupt on rising edge*/
   WRITEREG(EICRB,ISC71|ISC70|ISC61|ISC60|ISC51|ISC50|ISC41|ISC40);
 
   /*turn on interrupts on change of pins 0-7*/
   WRITEREG(EIMSK,INT7|INT6|INT5|INT4|INT3|INT2|INT1|INT0);

   btn_pressed=FALSE;
}
void task_sched_tmr_init(void)
{
   WRITEREG(TIMSK2, TOIE2);
   WRITEREG(OCR2A, TMR_TICKS(SCHED_INT_CONV,SCHED_DLY_TIME,SCHED_TMR_PRESCALER));
   /*start timer */
   WRITEREG(TCCR2A, WGM21|WGM20);
   WRITEREG(TCCR2B, WGM22|CS21);
   /* sync timers */
   WRITEREG(GTCCR, TSM|PSRASY);
   WRITEREG(GTCCR, READREG(GTCCR)&~TSM);
}

void led_ports_init(void)
{
   WRITEREG(LEDS_DIR, 0xff);
   WRITEREG(LEDS,0x00);
   WRITEREG(TCCR1A, WGM11|WGM10);
   WRITEREG(TCCR1B, WGM13|WGM12);
   WRITEREG(TIMSK1, TOIE1);
   WRITEREG(OCR1A, TMR_TICKS(LED_INT_CONV,led_dly_time,LED_TMR_PRESCALER));
     
   /*don't start timer until ready*/
   DISABLE_LED_TMR();
}

void watchdog_init(void)
{
   /* init watchdog timer for button is not pressed */
   /* after period of time                          */

   __disable_interrupts();
   __watchdog_reset();
    WRITEREG(MCUSR,READREG(MCUSR) | WDRF); /*clear flag before clear watchdog enable*/
	WRITEREG(WDTCSR,READREG(WDTCSR)|(WDCE|WDE|WDP3|WDP0)); /* 8 sec delay */
	__enable_interrupts();
	WRITEREG(WDTCSR,READREG(WDTCSR)|(WDCE|WDE));
    WRITEREG(WDTCSR,(READREG(WDTCSR)|WDIE)&~WDE); /*interrupt enable mode only */
	__disable_interrupts();
}

void init_hardware(void)
{
   btn_interrupt_init();
   debounce_timer_init();
   led_ports_init();
   task_sched_tmr_init();
   watchdog_init();
   __disable_interrupts();
}
/*"movw r26,r0     \n\t"
"mov r0 ,%A1        \n\t"
"adiw r26,33 ; to get to return address\n\t"
"clr r1           \n\t"
"cpse r0,r1        \n\t"
"rjmp restore_pc \n\t"
"; save program counter to global variable \n\t"
"save_pc: ld r0, X+ \n\t"
"ld r1, X+          \n\t"
"movw %A1, r0     \n\t"
"ld r0, X        \n\t"
"mov %C1, r0      \n\t"
"rjmp pop_stack  \n\t"
";restore program counter to place on stack for ret\n\t"
"restore_pc: out __SP_L__, r26 \n\t"
"out __SP_H__, r27 \n\t"
"movw r0,%A1        \n\t"
"mov r2,%C1         \n\t"
"push r0           \n\t"
"push r1           \n\t"
"push r2           \n\t"
"ld  r0, %a2+     \n\t"
"out __SP_L__, r0 \n\t"
"ld  r0, %a2     \n\t"
"out __SP_H__, r0 \n\t"
"clr r1           \n\t"*/
void longjmp(JMP_DATA buf)
{
	/* save interrupts */
	UINT8 interrupt;
	/* set return val */
	/**(buf+2)=val;*/
	/* restore stack ptr */
	asm volatile (
	"in %0, __SREG__   \n\t"
	"andi %0, 0x80     \n\t"
	"cli               \n\t"
	/* load stack ptr */ 
	"out __SP_L__, %A1 \n\t" 
	"out __SP_H__, %B1 \n\t"
	: "=&r" (interrupt),"+r" (buf)
	:);
	
	/* set return val */
	asm volatile (
	"ldi %0, 1 \n\t"
	:"=&r" (ctx_sw_res)
	:);

    /* pop stack */
    asm volatile (   
	"pop r31         \n\t"
	"pop r30         \n\t"
	"pop r29         \n\t"
	"pop r28         \n\t"
	"pop r27         \n\t"
	"pop r26         \n\t"
	"pop r25         \n\t"
	"pop r24         \n\t"
	"pop r23         \n\t"
	"pop r22         \n\t"
	"pop r21         \n\t"
	"pop r20         \n\t"
	"pop r19         \n\t"
	"pop r18         \n\t"
	"pop r17         \n\t"
	"pop r16         \n\t"
	"pop r15         \n\t"
	"pop r14         \n\t"
	"pop r13         \n\t"
	"pop r12         \n\t"
	"pop r11         \n\t"
	"pop r10         \n\t"
	"pop r9          \n\t"
	"pop r8          \n\t"
	"pop r7          \n\t"
	"pop r6          \n\t"
	"pop r5          \n\t"
	"pop r4          \n\t"
	"pop r3          \n\t"
	"pop r2          \n\t"
	"pop r1          \n\t"
	"pop r0          \n\t"
	"out __SREG__, r0\n\t"
	"pop r0          \n\t"::);
	
	asm volatile ("push r24 \n\t"::);
	
	/* restore interrupts */
	asm volatile (
	"sbrc %0,7       \n\t"
	"sei             \n\t"
	:
	:"r" (interrupt));
	
	asm volatile (
	"pop r24        \n\t"
	"ret            \n\t"
	::);
	/*WRITEREG(SREG,(READREG(SREG) & 0x7f) | interrupt);*/
}

void setjmp(JMP_DATA* buf)
{
	asm volatile (
	"push r0  \n\t"
	"in   r0, __SREG__ \n\t"
	"cli      \n\t"
	"push r0  \n\t"
	"push r1  \n\t"
	"clr  r1  \n\t"
	"push r2  \n\t"
	"push r3  \n\t"
	"push r4  \n\t"
	"push r5  \n\t"
	"push r6  \n\t"
	"push r7  \n\t"
	"push r8  \n\t"
	"push r9  \n\t"
	"push r10 \n\t"
	"push r11 \n\t"
	"push r12 \n\t"
	"push r13 \n\t"
	"push r14 \n\t"
	"push r15 \n\t"
	"push r16 \n\t"
	"push r17 \n\t"
	"push r18 \n\t"
	"push r19 \n\t"
	"push r20 \n\t"
	"push r21 \n\t"
	"push r22 \n\t"
	"push r23 \n\t"
	"push r24 \n\t"
	"push r25 \n\t"
	"push r26 \n\t"
	"push r27 \n\t"
	"push r28 \n\t"
	"push r29 \n\t"
	"push r30 \n\t"
	"push r31 \n\t"	
	::);
		asm volatile (
	";save stack in variable\n\t"
	"in    r24, __SP_L__ \n\t"
	"in    r25, __SP_H__ \n\t"
	"st    %a0, r24       \n\t"
	"std   %a0+1, r25     \n\t"
	"adiw r24,33 ; get back to before manual\n\t"
		
	"; reset stack to before manual pushes \n\t"
	"out __SP_L__, r24  \n\t"
	"out __SP_H__, r25  \n\t"
	";stack should now before manual pushes \n\t"
	:
	:"z" (buf));
	
	/* save return val */ 
    asm volatile (
	"ldi %0,0 \n\t"
	:"=r" (ctx_sw_res)
	:);
	
	/* restore interrupts */
	asm volatile (
	";restore interrupts\n\t"
	"SBRS r0,7   \n\t"
	"BCLR 7      \n\t"
	"SBRC r0,7   \n\t"
	"BSET 7      \n\t"::);
}

/*void setjmp(JMP_DATA* buf)
{
	asm volatile (
	"push r0  \n\t"
	"in   r0, __SREG__ \n\t"
	"cli      \n\t"
	"push r0  \n\t"
	"push r1  \n\t"
	"clr  r1  \n\t"
	"push r2  \n\t"
	"push r3  \n\t"
	"push r4  \n\t"
	"push r5  \n\t"
	"push r6  \n\t"
	"push r7  \n\t"
	"push r8  \n\t"
	"push r9  \n\t"
	"push r10 \n\t"
	"push r11 \n\t"
	"push r12 \n\t"
	"push r13 \n\t"
	"push r14 \n\t"
	"push r15 \n\t"
	"push r16 \n\t"
	"push r17 \n\t"
	"push r18 \n\t"
	"push r19 \n\t"
	"push r20 \n\t"
	"push r21 \n\t"
	"push r22 \n\t"
	"push r23 \n\t"
	"push r24 \n\t"
	"push r25 \n\t"
	"push r26 \n\t"
	"push r27 \n\t"
	"push r28 \n\t"
	"push r29 \n\t"
	"push r30 \n\t"
	"push r31 \n\t"	
	::);
	
	
	asm volatile (
	";save stack in variable\n\t"
	"in    r24, __SP_L__ \n\t"
	"in    r25, __SP_H__ \n\t"
	"st    %a0, r24       \n\t"
	"std   %a0+1, r25     \n\t"
	"adiw r24,33 ; get back to ret ptr\n\t"
		
	"; reset stack to return address \n\t"
	"out __SP_L__, r24  \n\t"
	"out __SP_H__, r25  \n\t"
	";stack should now be at ret ptr \n\t"
	:
	:"z" (buf));
	
	 save return val 
    asm volatile (
	"ldi %0,0 \n\t"
	:"=r" (ctx_sw_res)
	:);
	

	
	restore interrupts 
	asm volatile (
	";restore interrupts\n\t"
	"SBRS r0,7   \n\t"
	"BCLR 7      \n\t"
	"SBRC r0,7   \n\t"
	"BSET 7      \n\t"
	"ret         \n\t"::);
}*/

/* memory allocator wrappers*/
void * allocate_mem(const UINT32 bytes)
{
    return malloc(bytes);
}
void deallocate_mem(void * mem_ptr)
{
   free(mem_ptr);
   mem_ptr=NULLPTR;
}

ISR(INT0_vect,BLOCK)
{ 
   if (!DBNCED())
   {
      message->val=0;
      message->sender=NULLPTR;
      send_msg(&message,&BtnTask);
   }
}

ISR(INT1_vect,BLOCK)
{  
   if (!DBNCED())
   { 
      message->val=1;
      message->sender=NULLPTR;
      send_msg(&message,&BtnTask);
   }
}

ISR(INT2_vect,BLOCK)
{  
   if (!DBNCED())
   {
      message->val=2;
      message->sender=NULLPTR;
      send_msg(&message,&BtnTask);
   }
}

ISR(INT3_vect,BLOCK)
{  
   if (!DBNCED())
   {
      message->val=3;
      message->sender=NULLPTR;
      send_msg(&message,&BtnTask);
   }
	  
}

ISR(INT4_vect,BLOCK)
{  
   if (!DBNCED())
   {
      message->val=4;
      message->sender=NULLPTR;
      send_msg(&message,&BtnTask);
   }
}

ISR(INT5_vect,BLOCK)
{  
   if (!DBNCED())
   {
      message->val=5;
      message->sender=NULLPTR;
      send_msg(&message,&BtnTask);
   }
}

ISR(INT6_vect,BLOCK)
{  
   if (!DBNCED())
   {
      message->val=6;
      message->sender=NULLPTR;
      send_msg(&message,&BtnTask);
   }
}

ISR(INT7_vect,BLOCK)
{  
   if (!DBNCED())
   {
      message->val=7;
      message->sender=NULLPTR;
      send_msg(&message,&BtnTask);
   }
}
    
ISR(TIM0_OVF_vect,BLOCK)
{
   /* timeout for debouncing */
   DEBOUNCED(TRUE);
   DISABLE_DBNC_TMR();
  
}

ISR(TIM2_OVF_vect,BLOCK)
{
   signal(&SchedTask);
}

ISR(TIM1_OVF_vect,BLOCK)
{
   signal(&LEDTask);
}

ISR(WDT_vect,BLOCK)
{
   signal(&WDTTask);
}   

ISR(BADISR_vect, BLOCK)
{
   message->val=1;
}
