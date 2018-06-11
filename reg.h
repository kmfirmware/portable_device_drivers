/* Copyright 2012 Kerry Murphy                          */
/* Define your registers and their bits and masks here  */
/* Follow the Datasheet's lead when possible            */

#ifndef DRVREG_H

#define DRVREG_H

/* STATUS register */
#define SREG 0x5f

/* STACK */
#define STACK 0x5D
#define SPH   0x5E
#define SPL   0x5D

/* MCU Control Register */
#define MCUCR 0x55
#define JTD    (1<<7)
#define PUD    (1<<4)
#define IVSEL  (1<<1)
#define IVCE   (1<<0)

/* MCU Status Register */
#define MCUSR 0x54
#define JTRF   (1<<4)
#define WDRF   (1<<3)
#define BORF   (1<<2)
#define EXTRF  (1<<1)
#define PORF   (1<<0)

/* Watchdog Timer Control Register */
#define WDTCSR 0x60
#define WDIF   (1<<7)
#define WDIE   (1<<6)
#define WDP3   (1<<5)
#define WDCE   (1<<4)
#define WDE    (1<<3)
#define WDP2   (1<<2)
#define WDP1   (1<<1)
#define WDP0   (1<<0)

/* Port registers, Data Direction Register(DDR), and PIN addresses */
#define PORTA 0x22
#define PORTA7 (1<<7)
#define PORTA6 (1<<6)
#define PORTA5 (1<<5)
#define PORTA4 (1<<4)
#define PORTA3 (1<<3)
#define PORTA2 (1<<2)
#define PORTA1 (1<<1)
#define PORTA0 (1<<0)

#define DDRA 0x21
#define DDA7 (1<<7)
#define DDA6 (1<<6)
#define DDA5 (1<<5)
#define DDA4 (1<<4)
#define DDA3 (1<<3)
#define DDA2 (1<<2)
#define DDA1 (1<<1)
#define DDA0 (1<<0)

#define PINA  0x20
#define PINB7 (1<<7)
#define PINB6 (1<<6)
#define PINB5 (1<<5)
#define PINB4 (1<<4)
#define PINB3 (1<<3)
#define PINB2 (1<<2)
#define PINB1 (1<<1)
#define PINB0 (1<<0)

#define PORTB 0x25
#define PORTB7 (1<<7)
#define PORTB6 (1<<6)
#define PORTB5 (1<<5)
#define PORTB4 (1<<4)
#define PORTB3 (1<<3)
#define PORTB2 (1<<2)
#define PORTB1 (1<<1)
#define PORTB0 (1<<0)

#define DDRB 0x24
#define DDB7 (1<<7)
#define DDB6 (1<<6)
#define DDB5 (1<<5)
#define DDB4 (1<<4)
#define DDB3 (1<<3)
#define DDB2 (1<<2)
#define DDB1 (1<<1)
#define DDB0 (1<<0)

#define PINB  0x23
#define PINB7 (1<<7)
#define PINB6 (1<<6)
#define PINB5 (1<<5)
#define PINB4 (1<<4)
#define PINB3 (1<<3)
#define PINB2 (1<<2)
#define PINB1 (1<<1)
#define PINB0 (1<<0)

#define PORTC 0x28
#define PORTC7 (1<<7)
#define PORTC6 (1<<6)
#define PORTC5 (1<<5)
#define PORTC4 (1<<4)
#define PORTC3 (1<<3)
#define PORTC2 (1<<2)
#define PORTC1 (1<<1)
#define PORTC0 (1<<0)

#define DDRC 0x27
#define DDC7 (1<<7)
#define DDC6 (1<<6)
#define DDC5 (1<<5)
#define DDC4 (1<<4)
#define DDC3 (1<<3)
#define DDC2 (1<<2)
#define DDC1 (1<<1)
#define DDC0 (1<<0)

#define PINC  0x26
#define PINC7 (1<<7)
#define PINC6 (1<<6)
#define PINC5 (1<<5)
#define PINC4 (1<<4)
#define PINC3 (1<<3)
#define PINC2 (1<<2)
#define PINC1 (1<<1)
#define PINC0 (1<<0)

#define PORTD 0x2B
#define PORTD7 (1<<7)
#define PORTD6 (1<<6)
#define PORTD5 (1<<5)
#define PORTD4 (1<<4)
#define PORTD3 (1<<3)
#define PORTD2 (1<<2)
#define PORTD1 (1<<1)
#define PORTD0 (1<<0)

#define DDRD 0x2A
#define DDD7 (1<<7)
#define DDD6 (1<<6)
#define DDD5 (1<<5)
#define DDD4 (1<<4)
#define DDD3 (1<<3)
#define DDD2 (1<<2)
#define DDD1 (1<<1)
#define DDD0 (1<<0)

#define PIND  0x29
#define PIND7 (1<<7)
#define PIND6 (1<<6)
#define PIND5 (1<<5)
#define PIND4 (1<<4)
#define PIND3 (1<<3)
#define PIND2 (1<<2)
#define PIND1 (1<<1)
#define PIND0 (1<<0)


#define PORTE 0x2E
#define PORTE7 (1<<7)
#define PORTE6 (1<<6)
#define PORTE5 (1<<5)
#define PORTE4 (1<<4)
#define PORTE3 (1<<3)
#define PORTE2 (1<<2)
#define PORTE1 (1<<1)
#define PORTE0 (1<<0)

#define DDRE 0x2D
#define DDE7 (1<<7)
#define DDE6 (1<<6)
#define DDE5 (1<<5)
#define DDE4 (1<<4)
#define DDE3 (1<<3)
#define DDE2 (1<<2)
#define DDE1 (1<<1)
#define DDE0 (1<<0)

#define PINE  0x2C
#define PINE7 (1<<7)
#define PINE6 (1<<6)
#define PINE5 (1<<5)
#define PINE4 (1<<4)
#define PINE3 (1<<3)
#define PINE2 (1<<2)
#define PINE1 (1<<1)
#define PINE0 (1<<0)

#define PORTF 0x31
#define PORTF7 (1<<7)
#define PORTF6 (1<<6)
#define PORTF5 (1<<5)
#define PORTF4 (1<<4)
#define PORTF3 (1<<3)
#define PORTF2 (1<<2)
#define PORTF1 (1<<1)
#define PORTF0 (1<<0)

#define DDRF 0x30
#define DDF7 (1<<7)
#define DDF6 (1<<6)
#define DDF5 (1<<5)
#define DDF4 (1<<4)
#define DDF3 (1<<3)
#define DDF2 (1<<2)
#define DDF1 (1<<1)
#define DDF0 (1<<0)

#define PINF  0x2F
#define PINF7 (1<<7)
#define PINF6 (1<<6)
#define PINF5 (1<<5)
#define PINF4 (1<<4)
#define PINF3 (1<<3)
#define PINF2 (1<<2)
#define PINF1 (1<<1)
#define PINF0 (1<<0)

#define PORTG 0x34
#define PORTG7 (1<<7)
#define PORTG6 (1<<6)
#define PORTG5 (1<<5)
#define PORTG4 (1<<4)
#define PORTG3 (1<<3)
#define PORTG2 (1<<2)
#define PORTG1 (1<<1)
#define PORTG0 (1<<0)

#define DDRG 0x33
#define DDG7 (1<<7)
#define DDG6 (1<<6)
#define DDG5 (1<<5)
#define DDG4 (1<<4)
#define DDG3 (1<<3)
#define DDG2 (1<<2)
#define DDG1 (1<<1)
#define DDG0 (1<<0)

#define PING  0x32
#define PING7 (1<<7)
#define PING6 (1<<6)
#define PING5 (1<<5)
#define PING4 (1<<4)
#define PING3 (1<<3)
#define PING2 (1<<2)
#define PING1 (1<<1)
#define PING0 (1<<0)


#define PORTH 0x102
#define PORTH7 (1<<7)
#define PORTH6 (1<<6)
#define PORTH5 (1<<5)
#define PORTH4 (1<<4)
#define PORTH3 (1<<3)
#define PORTH2 (1<<2)
#define PORTH1 (1<<1)
#define PORTH0 (1<<0)

#define DDRH 0x101
#define DDH7 (1<<7)
#define DDH6 (1<<6)
#define DDH5 (1<<5)
#define DDH4 (1<<4)
#define DDH3 (1<<3)
#define DDH2 (1<<2)
#define DDH1 (1<<1)
#define DDH0 (1<<0)

#define PINH  0x100
#define PINH7 (1<<7)
#define PINH6 (1<<6)
#define PINH5 (1<<5)
#define PINH4 (1<<4)
#define PINH3 (1<<3)
#define PINH2 (1<<2)
#define PINH1 (1<<1)
#define PINH0 (1<<0)


#define PORTJ 0x105
#define PORTJ7 (1<<7)
#define PORTJ6 (1<<6)
#define PORTJ5 (1<<5)
#define PORTJ4 (1<<4)
#define PORTJ3 (1<<3)
#define PORTJ2 (1<<2)
#define PORTJ1 (1<<1)
#define PORTJ0 (1<<0)

#define DDRJ 0x104
#define DDJ7 (1<<7)
#define DDJ6 (1<<6)
#define DDJ5 (1<<5)
#define DDJ4 (1<<4)
#define DDJ3 (1<<3)
#define DDJ2 (1<<2)
#define DDJ1 (1<<1)
#define DDJ0 (1<<0)

#define PINJ  0x103
#define PINJ7 (1<<7)
#define PINJ6 (1<<6)
#define PINJ5 (1<<5)
#define PINJ4 (1<<4)
#define PINJ3 (1<<3)
#define PINJ2 (1<<2)
#define PINJ1 (1<<1)
#define PINJ0 (1<<0)


#define PORTK 0x108
#define PORTK7 (1<<7)
#define PORTK6 (1<<6)
#define PORTK5 (1<<5)
#define PORTK4 (1<<4)
#define PORTK3 (1<<3)
#define PORTK2 (1<<2)
#define PORTK1 (1<<1)
#define PORTK0 (1<<0)

#define DDRK 0x107
#define DDK7 (1<<7)
#define DDK6 (1<<6)
#define DDK5 (1<<5)
#define DDK4 (1<<4)
#define DDK3 (1<<3)
#define DDK2 (1<<2)
#define DDK1 (1<<1)
#define DDK0 (1<<0)

#define PINK  0x106
#define PINK7 (1<<7)
#define PINK6 (1<<6)
#define PINK5 (1<<5)
#define PINK4 (1<<4)
#define PINK3 (1<<3)
#define PINK2 (1<<2)
#define PINK1 (1<<1)
#define PINK0 (1<<0)

#define PORTL 0x10B
#define PORTL7 (1<<7)
#define PORTL6 (1<<6)
#define PORTL5 (1<<5)
#define PORTL4 (1<<4)
#define PORTL3 (1<<3)
#define PORTL2 (1<<2)
#define PORTL1 (1<<1)
#define PORTL0 (1<<0)

#define DDRL 0x10A
#define DDL7 (1<<7)
#define DDL6 (1<<6)
#define DDL5 (1<<5)
#define DDL4 (1<<4)
#define DDL3 (1<<3)
#define DDL2 (1<<2)
#define DDL1 (1<<1)
#define DDL0 (1<<0)

#define PINL  0x109
#define PINL7 (1<<7)
#define PINL6 (1<<6)
#define PINL5 (1<<5)
#define PINL4 (1<<4)
#define PINL3 (1<<3)
#define PINL2 (1<<2)
#define PINL1 (1<<1)
#define PINL0 (1<<0)

/* Timer/Counter Control Register A */
#define TCCR0A 0x44
#define COM0A1 (1<<7)
#define COM0A0 (1<<6)
#define COM0B1 (1<<5)
#define COM0B0 (1<<4)
#define WGM01  (1<<1)
#define WGM00  (1<<0)

/* Timer/Counter Control Register B */
#define TCCR0B 0x45
#define FOC0A  (1<<7)
#define FOC0B  (1<<6)
#define WGM02  (1<<3)
#define CS02   (1<<2)
#define CS01   (1<<1)
#define CS00   (1<<0)

/* Timer/Counter Interrupt Mask Register */
#define TIMSK0 0x6e
#define OCIE0B (1<<2)
#define OCIE0A (1<<1)
#define TOIE0  (1<<0)

/* Timer/Counter 0 Interrupt Flag Register */
#define TIFR0 0x35
#define OCF0B (1<<2)
#define OCF0A (1<<1)
#define TOV0  (1<<0)

/* Output Compare Register A*/
#define OCR0A 0x47

/* Timer/Counter Register 0*/
#define TCNT0 0x46

/* Timer/Counter 1 Control Register A */
#define TCCR1A 0x80
#define COM1A1 (1<<7)
#define COM1A0 (1<<6)
#define COM1B1 (1<<5)
#define COM1B0 (1<<4)
#define COM1C1 (1<<3)
#define COM1C0 (1<<2)
#define WGM11  (1<<1)
#define WGM10  (1<<0)

/* Timer/Counter Register 0*/
#define TCNT1 0x84

/* Timer/Counter 3 Control Register A */
#define TCCR3A 0x90
#define COM3A1 (1<<7)
#define COM3A0 (1<<6)
#define COM3B1 (1<<5)
#define COM3B0 (1<<4)
#define COM3C1 (1<<3)
#define COM3C0 (1<<2)
#define WGM31  (1<<1)
#define WGM30  (1<<0)

/* Output Compare Register 3 A*/
#define OCR3A  0x98
#define OCR3AH 0x99
#define OCR3AL 0x98
/* Timer/Counter 4 Control Register A */
#define TCCR4A 0xA0
#define COM4A1 (1<<7)
#define COM4A0 (1<<6)
#define COM4B1 (1<<5)
#define COM4B0 (1<<4)
#define COM4C1 (1<<3)
#define COM4C0 (1<<2)
#define WGM41  (1<<1)
#define WGM40  (1<<0)

/* Timer/Counter 5 Control Register A */
#define TCCR5A 0x120
#define COM5A1 (1<<7)
#define COM5A0 (1<<6)
#define COM5B1 (1<<5)
#define COM5B0 (1<<4)
#define COM5C1 (1<<3)
#define COM5C0 (1<<2)
#define WGM51  (1<<1)
#define WGM50  (1<<0)

/* Timer/Counter 1 Control Register B */
#define TCCR1B 0x81
#define ICNC1  (1<<7)
#define ICES1  (1<<6)
#define WGM13  (1<<4)
#define WGM12  (1<<3)
#define CS12   (1<<2)
#define CS11   (1<<1)
#define CS10   (1<<0)

/* Timer/Counter 3 Control Register B */
#define TCCR3B 0x91
#define ICNC3  (1<<7)
#define ICES3  (1<<6)
#define WGM33  (1<<4)
#define WGM32  (1<<3)
#define CS32   (1<<2)
#define CS31   (1<<1)
#define CS30   (1<<0)

/* Timer/Counter 4 Control Register B */
#define TCCR4B 0xA1
#define ICNC4  (1<<7)
#define ICES4  (1<<6)
#define WGM43  (1<<4)
#define WGM42  (1<<3)
#define CS42   (1<<2)
#define CS41   (1<<1)
#define CS40   (1<<0)

/* Timer/Counter 5 Control Register B */
#define TCCR5B 0x121
#define ICNC5  (1<<7)
#define ICES5  (1<<6)
#define WGM53  (1<<4)
#define WGM52  (1<<3)
#define CS52   (1<<2)
#define CS51   (1<<1)
#define CS50   (1<<0)

/* Timer/Counter 1 Control Register C */
#define TCCR1C 0x82
#define FOC1A  (1<<7)
#define FOC1B  (1<<6)
#define FOC1C  (1<<5)

/* Timer/Counter 3 Control Register C */
#define TCCR3C 0x92
#define FOC3A  (1<<7)
#define FOC3B  (1<<6)
#define FOC3C  (1<<5)

/* Timer/Counter 4 Control Register C */
#define TCCR4C 0xA2
#define FOC4A  (1<<7)
#define FOC4B  (1<<6)
#define FOC4C  (1<<5)

/* Timer/Counter 5 Control Register C */
#define TCCR5C 0x122
#define FOC5A  (1<<7)
#define FOC5B  (1<<6)
#define FOC3C  (1<<5)

/* Timer/Counter 1 */
#define TCNT1H 0x85
#define TCNT1L 0x84

/* Timer/Counter 3 */
#define TCNT3H 0x95
#define TCNT3L 0x94

/* Timer/Counter 4 */
#define TCNT4H 0xA5
#define TCNT4L 0xA4

/* Timer/Counter 5 */
#define TCNT5H 0x125
#define TCNT5L 0x124

/* Timer/Counter 1 Interrupt Mask Register */
#define TIMSK1 0x6F
#define ICIE1  (1<<5)
#define OCIE1C (1<<3)
#define OCIE1B (1<<2)
#define OCIE1A (1<<1)
#define TOIE1  (1<<0)

/* Timer/Counter 3 Interrupt Mask Register */
#define TIMSK3 0x71
#define ICIE3  (1<<5)
#define OCIE3C (1<<3)
#define OCIE3B (1<<2)
#define OCIE3A (1<<1)
#define TOIE3  (1<<0)

/* Timer/Counter 4 Interrupt Mask Register */
#define TIMSK4 0x72
#define ICIE4  (1<<5)
#define OCIE4C (1<<3)
#define OCIE4B (1<<2)
#define OCIE4A (1<<1)
#define TOIE4  (1<<0)

/* Timer/Counter 5 Interrupt Mask Register */
#define TIMSK5 0x73
#define ICIE5  (1<<5)
#define OCIE5C (1<<3)
#define OCIE5B (1<<2)
#define OCIE5A (1<<1)
#define TOIE5  (1<<0)

/* Timer/Counter1 Interrupt Flag Register */
#define TIFR1 0x36
#define ICF1   (1<<5)
#define OCF1C  (1<<3)
#define OCF1B  (1<<2)
#define OCF1A  (1<<1)
#define TOV1   (1<<0)

/*Output Compare Register 1 A*/
#define OCR1A  0x88
#define OCR1AH 0x89
#define OCR1AL 0x88

/* Timer/Counter3 Interrupt Flag Register */
#define TIFR3 0x38
#define ICF3   (1<<5)
#define OCF3C  (1<<3)
#define OCF3B  (1<<2)
#define OCF3A  (1<<1)
#define TOV3   (1<<0)

/* Timer/Counter4 Interrupt Flag Register */
#define TIFR4 0x39
#define ICF4   (1<<5)
#define OCF4C  (1<<3)
#define OCF4B  (1<<2)
#define OCF4A  (1<<1)
#define TOV4   (1<<0)

/* Timer/Counter5 Interrupt Flag Register */
#define TIFR5 0x3A
#define ICF5   (1<<5)
#define OCF5C  (1<<3)
#define OCF5B  (1<<2)
#define OCF5A  (1<<1)
#define TOV5   (1<<0)

/* General Timer/Counter Control Register */
#define GTCCR 0x43
#define TSM    (1<<7)
#define PSRASY (1<<1)
#define PSRSYNC (1<<0)

/* Timer/Counter Control Register A */
#define TCCR2A 0xB0
#define COM2A1 (1<<7)
#define COM2A0 (1<<6)
#define COM2B1 (1<<5)
#define COM2B0 (1<<4)
#define WGM21  (1<<1)
#define WGM20  (1<<0)

/* Timer/Counter Control Register B */
#define TCCR2B 0xB1
#define FOC2A  (1<<7)
#define FOC2B  (1<<6)
#define WGM22  (1<<3)
#define CS22   (1<<2)
#define CS21   (1<<1)
#define CS20   (1<<0)

/* Timer/Counter Register */
#define TCNT2 0xB2

/* Output Compare Register 2A*/
#define OCR2A 0xB3

/* Timer/Counter2 Interrupt Mask Register */
#define TIMSK2 0x70
#define OCIE2B (1<<2)
#define OCIE2A (1<<1)
#define TOIE2  (1<<0)

/* Timer/Counter2 Interrupt Flag Register */
#define TIFR2 0x37
#define OCF2B  (1<<2)
#define OCF2A  (1<<1)
#define TOV2   (1<<0)

/* USART I/O Data Register 3 */
#define UDR3 0x136

/* USART Control and Status Register 3 A */
#define UCSR3A 0x130
#define RXC3   (1<<7)
#define TXC3   (1<<6)
#define UDRE3  (1<<5)
#define FE3    (1<<4)
#define DOR3   (1<<3)
#define UPE3   (1<<2)
#define U2X3   (1<<1)
#define MPCM3  (1<<0)

/* USART Control and Status Register 3 B */
#define UCSR3B 0x131
#define RXCIE3 (1<<7)
#define TXCIE3 (1<<6)
#define UDRIE3 (1<<5)
#define RXEN3  (1<<4)
#define TXEN3  (1<<3)
#define UCSZ32 (1<<2)
#define RXB83  (1<<1)
#define TXB83  (1<<0)

/* USART Control and Status Register 3 C */
#define UCSR3C 0x132
#define UMSEL31 (1<<7)
#define UMSEL30 (1<<6)
#define UPM31   (1<<5)
#define UPM30   (1<<4)
#define USBS3   (1<<3)
#define UCSZ31  (1<<2)
#define UCSZ30  (1<<1)
#define UCPOL3  (1<<0)

/* USART Baud Rate Registers */
#define UBRR3L 0x134 
#define UBRR3H 0x135

/* USART I/O Data Register 2 */
#define UDR2 0xD6

/* USART Control and Status Register 2 A */
#define UCSR2A 0xD0
#define RXC2   (1<<7)
#define TXC2   (1<<6)
#define UDRE2  (1<<5)
#define FE2    (1<<4)
#define DOR2   (1<<3)
#define UPE2   (1<<2)
#define U2X2   (1<<1)
#define MPCM2  (1<<0)

/* USART Control and Status Register 2 B */
#define UCSR2B 0xD1
#define RXCIE2 (1<<7)
#define TXCIE2 (1<<6)
#define UDRIE2 (1<<5)
#define RXEN2  (1<<4)
#define TXEN2  (1<<3)
#define UCSZ22 (1<<2)
#define RXB82  (1<<1)
#define TXB82  (1<<0)

/* USART Control and Status Register 2 C */
#define UCSR2C 0xD2
#define UMSEL21 (1<<7)
#define UMSEL20 (1<<6)
#define UPM21   (1<<5)
#define UPM20   (1<<4)
#define USBS2   (1<<3)
#define UCSZ21  (1<<2)
#define UCSZ20  (1<<1)
#define UCPOL2  (1<<0)

/* USART Baud Rate Registers */
#define UBRR2L 0xD4 
#define UBRR2H 0xD5

/* USART I/O Data Register 1 */
#define UDR1 0xCE

/* USART Control and Status Register 1 A */
#define UCSR1A 0xC8
#define RXC1   (1<<7)
#define TXC1   (1<<6)
#define UDRE1  (1<<5)
#define FE1    (1<<4)
#define DOR1   (1<<3)
#define UPE1   (1<<2)
#define U2X1   (1<<1)
#define MPCM1  (1<<0)

/* USART Control and Status Register 1 B */
#define UCSR1B 0xC9
#define RXCIE1 (1<<7)
#define TXCIE1 (1<<6)
#define UDRIE1 (1<<5)
#define RXEN1  (1<<4)
#define TXEN1  (1<<3)
#define UCSZ12 (1<<2)
#define RXB81  (1<<1)
#define TXB81  (1<<0)

/* USART Control and Status Register 1 C */
#define UCSR1C 0xCA
#define UMSEL11 (1<<7)
#define UMSEL10 (1<<6)
#define UPM11   (1<<5)
#define UPM10   (1<<4)
#define USBS1   (1<<3)
#define UCSZ11  (1<<2)
#define UCSZ10  (1<<1)
#define UCPOL1  (1<<0)

/* USART Baud Rate Registers */
#define UBRR1L 0xCC
#define UBRR1H 0xCD

/* USART I/O Data Register 0 */
#define UDR0 0xC6

/* USART Control and Status Register 0 A */
#define UCSR0A 0xC0
#define RXC0   (1<<7)
#define TXC0   (1<<6)
#define UDRE0  (1<<5)
#define FE0    (1<<4)
#define DOR0   (1<<3)
#define UPE0   (1<<2)
#define U2X0   (1<<1)
#define MPCM0  (1<<0)

/* USART Control and Status Register 0 B */
#define UCSR0B 0xC1
#define RXCIE0 (1<<7)
#define TXCIE0 (1<<6)
#define UDRIE0 (1<<5)
#define RXEN0  (1<<4)
#define TXEN0  (1<<3)
#define UCSZ02 (1<<2)
#define RXB80  (1<<1)
#define TXB80  (1<<0)

/* USART Control and Status Register 0 C */
#define UCSR0C 0xC2
#define UMSEL01 (1<<7)
#define UMSEL00 (1<<6)
#define UPM01   (1<<5)
#define UPM00   (1<<4)
#define USBS0   (1<<3)
#define UCSZ01  (1<<2)
#define UCSZ00  (1<<1)
#define UCPOL0  (1<<0)

/* USART Baud Rate Registers */
#define UBRR0L 0xC4 
#define UBRR0H 0xC5

/* EEPROM Address Register */
#define EEARH 0x42
#define EEAR11 (1<<3)
#define EEAR10 (1<<2)
#define EEAR9  (1<<1)
#define EEAR8  (1<<0)
#define EEARL 0x41
#define EEAR7  (1<<7)
#define EEAR6  (1<<6)
#define EEAR5  (1<<5)
#define EEAR4  (1<<4)
#define EEAR3  (1<<3)
#define EEAR2  (1<<2)
#define EEAR1  (1<<1)
#define EEAR0  (1<<0)

#define EEDR 0x40

/* The EEPROM Control Register */
#define EECR 0x3F
#define EEPM1  (1<<5)
#define EEPM0  (1<<4)
#define EERIE  (1<<3)
#define EEMPE  (1<<2)
#define EEPE   (1<<1)
#define EERE   (1<<0)

/* External Interrupt Registers */
/* External Interrupt Registers 0-3 */
#define EICRA 0x69
#define ISC31  (1<<7)
#define ISC30  (1<<6)
#define ISC21  (1<<5)
#define ISC20  (1<<4)
#define ISC11  (1<<3)
#define ISC10  (1<<2)
#define ISC01  (1<<1)
#define ISC00  (1<<0)

/* External Interrupt Registers 4-7 */
#define EICRB 0x6A
#define ISC71  (1<<7)
#define ISC70  (1<<6)
#define ISC61  (1<<5)
#define ISC60  (1<<4)
#define ISC51  (1<<3)
#define ISC50  (1<<2)
#define ISC41  (1<<1)
#define ISC40  (1<<0)

/* External Interrupt Request 7 - 0 Enable */
#define EIMSK 0x3D
#define INT7   (1<<7)
#define INT6   (1<<6)
#define INT5   (1<<5)
#define INT4   (1<<4)
#define INT3   (1<<3)
#define INT2   (1<<2)
#define INT1   (1<<1)
#define INT0   (1<<0)

/*External Interrupt Flag Register */
#define EIFR  0x3C
#define INTF7  (1<<7)
#define INTF6  (1<<6)
#define INTF5  (1<<5)
#define INTF4  (1<<4)
#define INTF3  (1<<3)
#define INTF2  (1<<2)
#define INTF1  (1<<1)
#define INTF0  (1<<0)
#endif

