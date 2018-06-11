#ifndef PORT_H

#define PORT_H

#include "reg.h"
/*#include <setjmp.h>*/
#define TRUE	1
#define FALSE	0

#define UINT8 	unsigned char
#define INT8	signed char
#define UINT16	unsigned short
#define INT16	signed short
#define UINT32	unsigned int
#define INT32	signed int
#define NULLPTR (void *)(0)

#define BASE_ADDR 0x00
#define ADDR_MULT 1
#define WORD_SIZE 16
#define BYTE_SIZE 8

/* wrapper for reading register */
#define READREG(pReg) (*(volatile UINT32 *)(((pReg)*ADDR_MULT) + BASE_ADDR))

/* wrapper for writing register */
#define WRITEREG(pReg, data) (*(volatile UINT32 *)(((pReg)*ADDR_MULT) + BASE_ADDR) = (data))


/* interrupt is enabled at initialization*/
/* sei enables interrupts */
#define __enable_interrupts() \
__asm__ __volatile__ ("sei" ::)

/* cli disables interrupts */
#define __disable_interrupts() \
__asm__ __volatile__ ("cli" ::)

/* reset Watchdog timer */
#define __watchdog_reset() \
__asm__ __volatile__ ("wdr" ::)

#define LEDS PORTB
#define LEDS_DIR DDRB

#define WDT_MAX_TO 8
#define WDT_STP_DWN1   4
#define WDT_STP_DWN2   2
#define WDT_STP_DWN3   1

#define DLY_WO_LEDS 16 /* in seconds */

/* used to pass to ISR define */
#define BLOCK signal
#define NO_BLOCK interrupt

/* interrupt is disabled at initialization */
#define ISR(vector,attr)\
 extern void vector (void) __attribute__ ((attr)); \
 void vector (void)

void debounce_timer_init(void);

#define CPU_FREQ 1000000

/* 1/8000000=.000000125*1000000000 gives integer value*/
/* 1/(CPU_FREQ/_PRESCALER)=1_cycle_time*/
/* delay_time=timer_count*1_cycle_time*/
/* timer_count=delay_time/1_cycle_time*/
/* timer_count=(delay_time*INT_CONVERT)/(INT_MULTIPLIER/(CPU_FREQ/_PRESCALER))*/
/* (delay_time*INT_CONVERT)/((INT_MULTIPLIER*_PRESCALER)/CPU_FREQ)*/
/* (delay_time*INT_CONVERT*CPU_FREQ)/(INT_MULTIPLIER*_PRESCALER)*/
#define CPU_INT_MULTIPLIER 1000000000

#define DEBOUNCE_TMR_PRESCALER 1024
/*.015*1000 to keep integer arithematic*/
#define DBNC_INT_CONV 1000
#define DBNC_DLY_TIME 0.015
#define TMR_TICKS(INT_CONV_VAL,DELAY_TIME,PRESCAL_VAL) \
((DELAY_TIME) * (INT_CONV_VAL) *\
((CPU_FREQ)/(PRESCAL_VAL))/\
(float)(CPU_INT_MULTIPLIER)) * ((CPU_INT_MULTIPLIER)/(INT_CONV_VAL))

#define SCHED_TMR_PRESCALER 8
/*.000100*1000000 to keep integer arithematic*/
#define SCHED_INT_CONV 1000000
#define SCHED_DLY_TIME 0.000175


#define LED_TMR_PRESCALER 256
/*.5 * 10 to keep integer arithematic*/
#define LED_INT_CONV 10

/* LED delay defined globally */
/* #define LED_DLY_TIME 0.5 */

#define ENABLE_LED_TMR()   (WRITEREG(TCNT1,0x00),WRITEREG(TCCR1B, READREG(TCCR1B)|CS12))
#define DISABLE_LED_TMR()  (WRITEREG(TCCR1B, READREG(TCCR1B)&(~CS12)))

#define SCHEDULER_HOOK()  longjmp((sched_env))
#define TASK_HOOK(env)    longjmp((env))
#define JMP_OCCURED()     (ctx_sw_res)

/*#define SAVE_CONTEXT(env)\
setjmp(&(env));\
if (!JMP_OCCURED())\
{\
   asm volatile (\
   restore stack ptr to proper position\
   "ld r0,%a0+ \n\t"\
   "out __SP_L__, r0 \n\t"\
   "ld r0,%a0  \n\t"\
   "out __SP_H__, r0 \n\t"\
   :\
   : "e" (&(env))\
   );\
}*/

/*asm volatile (\
"tst %A0      \n\t"\
"brne 2f      \n\t"\
"tst %A1      \n\t"\
"breq 2f      \n\t"\
this is a new entry\
get current entry want to push from there to keep stack integrity\
"out __SP_L__, %A1 \n\t"\
"out __SP_H__, %B1 \n\t"\
:\
:"r" (env),"r" (cur_stk_ptr));\*/
#define SAVE_CONTEXT_SCHED()\
asm volatile (\
    "rcall save_regs%= \n\t"\
	/*task switch occurred*/\
	"rjmp 1f           \n\t"\
	"save_regs%=: push r0  \n\t"\
	"in   r0, __SREG__ \n\t"\
	"cli      \n\t"\
	"push r0  \n\t"\
	"push r1  \n\t"\
	"clr  r1  \n\t"\
	"push r2  \n\t"\
	"push r3  \n\t"\
	"push r4  \n\t"\
	"push r5  \n\t"\
	"push r6  \n\t"\
	"push r7  \n\t"\
	"push r8  \n\t"\
	"push r9  \n\t"\
	"push r10 \n\t"\
	"push r11 \n\t"\
	"push r12 \n\t"\
	"push r13 \n\t"\
	"push r14 \n\t"\
	"push r15 \n\t"\
	"push r16 \n\t"\
	"push r17 \n\t"\
	"push r18 \n\t"\
	"push r19 \n\t"\
	"push r20 \n\t"\
	"push r21 \n\t"\
	"push r22 \n\t"\
	"push r23 \n\t"\
	"push r24 \n\t"\
	"push r25 \n\t"\
	"push r26 \n\t"\
	"push r27 \n\t"\
	"push r28 \n\t"\
	"push r29 \n\t"\
	"push r30 \n\t"\
	"push r31 \n\t"\
	::);\
\
    sched_env=READREG(STACK);\
\
	/* save return val */\
	ctx_sw_res=0;\
\
	/* restore interrupts */\
	asm volatile (\
	";restore interrupts\n\t"\
	"SBRS r0,7   \n\t"\
	"BCLR 7      \n\t"\
	"SBRC r0,7   \n\t"\
	"BSET 7      \n\t"\
	"1: nop\n\t"::);

/*
    asm volatile (\
	";save stack in variable\n\t"\
	"in   %A0, __SP_L__ \n\t"\
	"in   %B0, __SP_H__ \n\t"\
	"movw %A1,%A0       \n\t"\
	:"=&r" (env),"=&r" (cur_stk_ptr)\
	::"r30","r31");\*/	
/*    asm volatile (\
   "ldi %0,0 \n\t"\
   :"=&r" (ctx_sw_res)\
   :);\*/
/*asm volatile (\
"tst %A0      \n\t"\
"brne 2f      \n\t"\
"tst %A1      \n\t"\
"breq 2f      \n\t"\
"push r18     \n\t"\
"push r19     \n\t"\
"push r24     \n\t"\
"push r25     \n\t"\
"in r24, __SP_L__  \n\t"\
"in r25, __SP_H__  \n\t"\
"movw r18,r24      \n\t"\
"cpc r18,%A1       \n\t"\
"brmi curstkptr_gt%= \n\t"\
"breq equal%= \n\t"\
/*curstkptr less than current stack location
"sbiw r18,37 ; 37=33 registers + return addr \n\t"\
"cpc r18,%A1  \n\t"\
/*not enough room on stack-set cur_stk_ptr to lowest
"brlt set_curstkptr%= \n\t"\
/*curstkptr is right location 
"brge save_stack%= \n\t"\
"equal%=: cpc r19,%B1 \n\t"\
\
"sub r18,%A1  \n\t"\
"sbc r19,%B1  \n\t"\
\
/*this is a new entry
/*get current entry want to push from there to keep stack integrity
"out __SP_L__, %A1 \n\t"\
"out __SP_H__, %B1 \n\t"\
:\
:"r" (env),"r" (cur_stk_ptr));*/
#define SAVE_CONTEXT(env)\
{\
JMP_DATA save_stk_ptr=READREG(STACK);\
if (!(env))\
{\
   if (cur_stk_ptr)\
   {\
	  if ((ABS(cur_stk_ptr - save_stk_ptr) >= 37) || (cur_stk_ptr < save_stk_ptr))\
	     WRITEREG(STACK, cur_stk_ptr);\
	  else if(cur_stk_ptr >= save_stk_ptr)\
	     WRITEREG(STACK, save_stk_ptr);\
   }\
};\
asm volatile (\
    "rcall save_regs%= \n\t"\
	/*task switch occurred*/\
	"rjmp 1f           \n\t"\
	"save_regs%=: push r0  \n\t"\
	"in   r0, __SREG__ \n\t"\
	"cli      \n\t"\
	"push r0  \n\t"\
	"push r1  \n\t"\
	"clr  r1  \n\t"\
	"push r2  \n\t"\
	"push r3  \n\t"\
	"push r4  \n\t"\
	"push r5  \n\t"\
	"push r6  \n\t"\
	"push r7  \n\t"\
	"push r8  \n\t"\
	"push r9  \n\t"\
	"push r10 \n\t"\
	"push r11 \n\t"\
	"push r12 \n\t"\
	"push r13 \n\t"\
	"push r14 \n\t"\
	"push r15 \n\t"\
	"push r16 \n\t"\
	"push r17 \n\t"\
	"push r18 \n\t"\
	"push r19 \n\t"\
	"push r20 \n\t"\
	"push r21 \n\t"\
	"push r22 \n\t"\
	"push r23 \n\t"\
	"push r24 \n\t"\
	"push r25 \n\t"\
	"push r26 \n\t"\
	"push r27 \n\t"\
	"push r28 \n\t"\
	"push r29 \n\t"\
	"push r30 \n\t"\
	"push r31 \n\t"\
	::);\
\
	asm volatile (\
	";save stack in variable\n\t"\
	"in   %A0, __SP_L__ \n\t"\
	"in   %B0, __SP_H__ \n\t"\
	:"=&r" (env)\
	:);\
	cur_stk_ptr=env;\
\
	/* save return val */\
   asm volatile (\
   "ldi %0,0 \n\t"\
   :"=&r" (ctx_sw_res)\
   :);\
\
    /* restore stack */\
    WRITEREG(STACK, save_stk_ptr);\
\
	/* restore interrupts */\
	asm volatile (\
	";restore interrupts\n\t"\
	"SBRS r0,7   \n\t"\
	"BCLR 7      \n\t"\
	"SBRC r0,7   \n\t"\
	"BSET 7      \n\t"\
	"1: nop\n\t"::);\
}

#define JMP_DATA UINT16

/*#define __read_interrupt() ((READREG(SREG) & 0x80)>>7)*/
#define save_interrupt() (interrupt_stat=(READREG(SREG) & 0x80))
#define restore_interrupt() (WRITEREG(SREG,(READREG(SREG) & 0x7f) | interrupt_stat))



/*	"ld r26, %a0 \n\t"\
	"push r16    \n\t"\
	"ldi r16, %1 \n\t"\
	"mov r27,r26 \n\t"\
	"add r27, r16\n\t"\
	"pop r16     \n\t"\
"SBRS r1,7   \n\t" 
	"BCLR 7      \n\t" 
	"SBRC r1,7   \n\t" 
	"BSET 7      \n\t"*/ 
void longjmp(JMP_DATA ) __attribute__ ( ( naked ) );
void setjmp(JMP_DATA *);

/*asm volatile (\
"rcall save_regs%= ;save program counter on stack\n\t"\
""
"rjmp 1f ;after switch context fall thru\n\t"\
"save_regs%=: push r0  \n\t"\
"in   r0, __SREG__ \n\t"\
"cli      \n\t"\
"push r0 \n\t"\
"push r1  \n\t"\
"clr  r1  \n\t"\
"push r2  \n\t"\
"push r3  \n\t"\
"push r4  \n\t"\
"push r5  \n\t"\
"push r6  \n\t"\
"push r7  \n\t"\
"push r8  \n\t"\
"push r9  \n\t"\
"push r10 \n\t"\
"push r11 \n\t"\
"push r12 \n\t"\
"push r13 \n\t"\
"push r14 \n\t"\
"push r15 \n\t"\
"push r16 \n\t"\
"push r17 \n\t"\
"push r18 \n\t"\
"push r19 \n\t"\
"push r20 \n\t"\
"push r21 \n\t"\
"push r22 \n\t"\
"push r23 \n\t"\
"push r24 \n\t"\
"push r25 \n\t"\
"push r26 \n\t"\
"push r27 \n\t"\
"push r28 \n\t"\
"push r29 \n\t"\
"push r30 \n\t"\
"push r31 \n\t"\
::);\
asm volatile (\
";save stack in variable\n\t"\
"in    r1, __SP_L__\n\t"\
"st    %a0+, r1\n\t"\
"in    r1, __SP_H__\n\t"\
"st    %a0, r1\n\t"\
"clr r1  \n\t"\
";restore interrupts\n\t"\
"SBRS r0,7   \n\t"\
"BCLR 7      \n\t"\
"SBRC r0,7   \n\t"\
"BSET 7      \n\t"\
"1: nop   \n\t"\
:\
:"z" (buf));*/
/*#define setjmp(buf) __asm__ __volatile__ (\
"rcall begin_save%=    ; save program counter on stack\n\t"\
"begin_save%=:  push r0 \n\t"\
"in   r0, __SREG__ \n\t"\
"cli             \n\t"\
"push r0         \n\t"\
"push r1         \n\t"\
"clr  r1  \n\t"\
"push r2  \n\t"\
"push r3  \n\t"\
"push r4  \n\t"\
"push r5  \n\t"\
"push r6  \n\t"\
"push r7  \n\t"\
"push r8  \n\t"\
"push r9  \n\t"\
"push r10 \n\t"\
"push r11 \n\t"\
"push r12 \n\t"\
"push r13 \n\t"\
"push r14 \n\t"\
"push r15 \n\t"\
"push r16 \n\t"\
"push r17 \n\t"\
"push r18 \n\t"\
"push r19 \n\t"\
"push r20 \n\t"\
"push r21 \n\t"\
"push r22 \n\t"\
"push r23 \n\t"\
"push r24 \n\t"\
"push r25 \n\t"\
"push r26 \n\t"\
"push r27 \n\t"\
"push r28 \n\t"\
"push r29 \n\t"\
"push r30 \n\t"\
"push r31 \n\t"\
"in    r2, __SP_L__\n\t"\
"st    %a0+, r2\n\t"\
"in    r2, __SP_H__\n\t"\
"st    %a0, r2\n\t"\
:\
:"z" (buf));*/
/*"SBRS r0,7   \n\t"\
"BCLR 7      \n\t"\
"SBRC r0,7   \n\t"\
"BSET 7      \n\t"*/
/* this would get anded with a variable */
#define BIT(n) ((unsigned int) (1<<(n)))

/* this could be used as a mask for a portion of a value */
#define MAXVAL(n) (((unsigned int)(1<<(n)))-1)

#define BTN0_VAL ((READREG(PIND))& (BIT(0)))
#define BTN1_VAL ((READREG(PIND))& (BIT(1)))
#define BTN2_VAL ((READREG(PIND))& (BIT(2)))
#define BTN3_VAL ((READREG(PIND))& (BIT(3)))
#define BTN4_VAL ((READREG(PINE))& (BIT(4)))
#define BTN5_VAL ((READREG(PINE))& (BIT(5)))
#define BTN6_VAL ((READREG(PINE))& (BIT(6)))
#define BTN7_VAL ((READREG(PINE))& (BIT(7)))

/* disable timer interrupt */
#define DISABLE_DBNC_TMR() (WRITEREG(TCCR0B,READREG(TCCR0B)&~CS02&~CS01&~CS00))  /*stop the timer */
 
 /* clear counter*/
 /* enable clock */                  
#define ENABLE_DBNC_TMR()  (btn_pressed=TRUE,\
btn_timeout=FALSE,\
WRITEREG(TCNT0,0),\
WRITEREG(TCCR0B, READREG(TCCR0B)|CS02|CS00)) /* start timer */
                           
#define LED_ON(IDX) (WRITEREG(LEDS,BIT(IDX)))
#define LED_CNT 8
                     

typedef UINT8 boolean;
volatile static boolean btn_timeout;
volatile static boolean btn_pressed;
extern volatile UINT8 ctx_sw_res;

#define DBNCED() (btn_timeout || btn_pressed)

#define DEBOUNCED(TRUE) (btn_pressed=FALSE,btn_timeout=TRUE) 

extern JMP_DATA sched_env;
extern JMP_DATA cur_stk_ptr;

/* function declarations */
void debounce_timer_init(void);
void btn_interrupt_init(void);
void task_sched_tmr_init(void);
void led_ports_init(void);
void watchdog_init(void);
void init_hardware(void);

/* memory allocator wrappers*/
void * allocate_mem(const UINT32);
void deallocate_mem(void *);

/* interrupt definitions*/
#ifndef _VECTOR
#define _VECTOR(N) __vector_ ## N
#endif

#define INT0_vect       _VECTOR(1)  /* External Interrupt Request 0 */
#define INT1_vect       _VECTOR(2)  /* External Interrupt Request 1 */
#define INT2_vect       _VECTOR(3)  /* External Interrupt Request 2 */
#define INT3_vect       _VECTOR(4)  /* External Interrupt Request 3 */
#define INT4_vect       _VECTOR(5)  /* External Interrupt Request 4 */
#define INT5_vect       _VECTOR(6)  /* External Interrupt Request 5 */
#define INT6_vect       _VECTOR(7)  /* External Interrupt Request 6 */
#define INT7_vect       _VECTOR(8)  /* External Interrupt Request 7 */
#define PCINT0_vect     _VECTOR(9)  /* Pin Change Interrupt Request 0 */
#define PCINT1_vect     _VECTOR(10)  /* Pin Change Interrupt Request 1 */
#define PCINT2_vect     _VECTOR(11)  /* Pin Change Interrupt Request 2 */
#define WDT_vect        _VECTOR(12)  /* WatchDog Timer Interrupt */
#define TIM2_COMPA_vect _VECTOR(13)  /* Timer2 CompareA Handler */
#define TIM2_COMPB_vect _VECTOR(14)  /* Timer2 CompareB Handler */
#define TIM2_OVF_vect   _VECTOR(15)  /* Timer2 Overflow Handler */
#define TIM1_CAPT_vect  _VECTOR(16)  /* Timer1 Capture Handler  */
#define TIM1_COMPA_vect _VECTOR(17)  /* Timer1 CompareA Handler */
#define TIM1_COMPB_vect _VECTOR(18)  /* Timer1 CompareB Handler */
#define TIM1_COMPC_vect _VECTOR(19)  /* Timer1 CompareC Handler */
#define TIM1_OVF_vect   _VECTOR(20)  /* Timer1 Overflow Handler */
#define TIM0_COMPA_vect _VECTOR(21)  /* Timer0 CompareA Handler */
#define TIM0_COMPB_vect _VECTOR(22)  /* Timer0 CompareB Handler */
#define TIM0_OVF_vect   _VECTOR(23)  /* Timer0 Overflow Handler */
#define SPI_STC_vect    _VECTOR(24)  /* SPI Transfer Complete Handler */
#define USART0_RXC_vect _VECTOR(25)  /* USART0 RX Complete Handler */
#define USART0_UDRE_vect _VECTOR(26) /* USART0,UDR Empty Handler */
#define USART0_TXC_vect _VECTOR(27)  /* USART0 TX Complete Handler */
#define ANA_COMP_vect   _VECTOR(28)  /* Analog Comparator Handler */
#define ADC_vect        _VECTOR(29)  /* ADC Conversion Complete Handler */
#define EE_RDY_vect     _VECTOR(30)  /* EEPROM Ready Handler */
#define TIM3_CAPT_vect  _VECTOR(31)  /* Timer3 Capture Handler */
#define TIM3_COMPA_vect _VECTOR(32)  /* Timer3 CompareA Handler */
#define TIM3_COMPB_vect _VECTOR(33)  /* Timer3 CompareB Handler */
#define TIM3_COMPC_vect _VECTOR(34)  /* Timer3 CompareC Handler */
#define TIM3_OVF_vect   _VECTOR(35)  /* Timer3 Overflow Handler */
#define USART1_RXC_vect _VECTOR(36)  /* USART1 RX Complete Handler */
#define USART1_UDRE_vect _VECTOR(37) /* USART1,UDR Empty Handler */
#define USART1_TXC_vect _VECTOR(38)  /* USART1 TX Complete Handler */
#define TWI_vect        _VECTOR(39)  /* 2-wire Serial Handler */
#define SPM_RDY_vect    _VECTOR(40)  /* SPM Ready Handler */
#define TIM4_CAPT_vect  _VECTOR(41)  /* Timer4 Capture Handler */
#define TIM4_COMPA_vect _VECTOR(42)  /* Timer4 CompareA Handler */
#define TIM4_COMPB_vect _VECTOR(43)  /* Timer4 CompareB Handler */
#define TIM4_COMPC_vect _VECTOR(44)  /* Timer4 CompareC Handler */
#define TIM4_OVF_vect   _VECTOR(45)  /* Timer4 Overflow Handler */
#define TIM5_CAPT_vect  _VECTOR(46)  /* Timer5 Capture Handler */
#define TIM5_COMPA_vect _VECTOR(47)  /* Timer5 CompareA Handler */
#define TIM5_COMPB_vect _VECTOR(48)  /* Timer5 CompareB Handler */
#define TIM5_COMPC_vect _VECTOR(49)  /* Timer5 CompareC Handler */
#define TIM5_OVF_vect   _VECTOR(50)  /* Timer5 Overflow Handler */
#define USART2_RXC_vect _VECTOR(51)  /* USART2 RX Complete Handler */
#define USART2_UDRE_vect _VECTOR(52) /* USART2,UDR Empty Handler */
#define USART2_TXC_vect  _VECTOR(53) /* USART2 TX Complete Handler */
#define USART3_RXC_vect  _VECTOR(54) /* USART3 RX Complete Handler */
#define USART3_UDRE_vect _VECTOR(55) /* USART3,UDR Empty Handler */
#define USART3_TXC_vect  _VECTOR(56) /* USART3 TX Complete Handler */

#define _VECTOR_SIZE 2 /* Size of individual vector. */
#define _VECTORS_SIZE (57 * _VECTOR_SIZE)

/*
    This is a vector which is aliased to __vector_default, the vector
    executed when an ISR fires with no accompanying ISR handler. This
    may be used along with the ISR() macro to create a catch-all for
    undefined but used ISRs for debugging purposes.
*/
#define BADISR_vect __vector_default

#endif
