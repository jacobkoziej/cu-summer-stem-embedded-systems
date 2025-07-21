	.file	"static.cc"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
 ;  GNU C++17 (GCC) version 14.3.0 (avr)
 ; 	compiled by GNU C version 14.3.0, GMP version 6.3.0, MPFR version 4.2.2, MPC version 1.3.1, isl version isl-0.20-GMP

 ;  GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 ;  options passed: -mn-flash=1 -mdouble=32 -mlong-double=64 -mmcu=avr5 -O2 -O0 -std=gnu++17 -fstack-clash-protection -fzero-call-used-regs=used-gpr -fno-strict-overflow -fno-omit-frame-pointer -fdata-sections -ffunction-sections -fno-threadsafe-statics -fpermissive -frandom-seed=ali4jncyjg -mn-flash=1 -mno-skip-bug -fno-rtti -fno-enforce-eh-specs -fno-exceptions
	.text
	.section	.rodata._ZL21PIN_ENCODER_CHANNEL_A,"a"
	.type	_ZL21PIN_ENCODER_CHANNEL_A, @object
	.size	_ZL21PIN_ENCODER_CHANNEL_A, 1
_ZL21PIN_ENCODER_CHANNEL_A:
	.byte	2
	.section	.rodata._ZL21PIN_ENCODER_CHANNEL_B,"a"
	.type	_ZL21PIN_ENCODER_CHANNEL_B, @object
	.size	_ZL21PIN_ENCODER_CHANNEL_B, 1
_ZL21PIN_ENCODER_CHANNEL_B:
	.byte	3
	.section	.bss._ZL5steps,"aw",@nobits
	.type	_ZL5steps, @object
	.size	_ZL5steps, 4
_ZL5steps:
	.zero	4
	.section	.bss._ZZ13channel_a_isrvE1A,"aw",@nobits
	.type	_ZZ13channel_a_isrvE1A, @object
	.size	_ZZ13channel_a_isrvE1A, 1
_ZZ13channel_a_isrvE1A:
	.zero	1
	.section	.bss._ZGVZ13channel_a_isrvE1A,"aw",@nobits
	.type	_ZGVZ13channel_a_isrvE1A, @object
	.size	_ZGVZ13channel_a_isrvE1A, 8
_ZGVZ13channel_a_isrvE1A:
	.zero	8
	.section	.bss._ZZ13channel_a_isrvE1B,"aw",@nobits
	.type	_ZZ13channel_a_isrvE1B, @object
	.size	_ZZ13channel_a_isrvE1B, 1
_ZZ13channel_a_isrvE1B:
	.zero	1
	.section	.bss._ZGVZ13channel_a_isrvE1B,"aw",@nobits
	.type	_ZGVZ13channel_a_isrvE1B, @object
	.size	_ZGVZ13channel_a_isrvE1B, 8
_ZGVZ13channel_a_isrvE1B:
	.zero	8
	.section	.text._Z13channel_a_isrv,"ax",@progbits
.global	_Z13channel_a_isrv
	.type	_Z13channel_a_isrv, @function
_Z13channel_a_isrv:
	push r28		 ; 
	push r29		 ; 
	in r28,__SP_L__	 ; 
	in r29,__SP_H__	 ; 
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
 ;  static.cc:13:   static bool A = digitalRead(PIN_ENCODER_CHANNEL_A);
	ldi r24,lo8(_ZGVZ13channel_a_isrvE1A)	 ;  _ZGVZ13channel_a_isrvE1A.0_1,
	ldi r25,hi8(_ZGVZ13channel_a_isrvE1A)	 ;  _ZGVZ13channel_a_isrvE1A.0_1,
	movw r30,r24	 ; , _ZGVZ13channel_a_isrvE1A.0_1
	ld r24,Z		 ;  _2, MEM[(char *)_ZGVZ13channel_a_isrvE1A.0_1]
	cp r24, __zero_reg__	 ;  _2
	brne .L2		 ; ,
 ;  static.cc:13:   static bool A = digitalRead(PIN_ENCODER_CHANNEL_A);
	ldi r24,lo8(2)	 ; ,
	call digitalRead	 ; 
	ldi r18,lo8(1)	 ;  _4,
	sbiw r24,0	 ;  _3,
	brne .L3		 ; ,
	ldi r18,0		 ;  _4
.L3:
 ;  static.cc:13:   static bool A = digitalRead(PIN_ENCODER_CHANNEL_A);
	sts _ZZ13channel_a_isrvE1A,r18	 ;  A, _4
	ldi r24,lo8(_ZGVZ13channel_a_isrvE1A)	 ;  _ZGVZ13channel_a_isrvE1A.1_5,
	ldi r25,hi8(_ZGVZ13channel_a_isrvE1A)	 ;  _ZGVZ13channel_a_isrvE1A.1_5,
	ldi r18,lo8(1)	 ;  tmp59,
	movw r30,r24	 ; , _ZGVZ13channel_a_isrvE1A.1_5
	st Z,r18		 ;  MEM[(char *)_ZGVZ13channel_a_isrvE1A.1_5], tmp59
.L2:
 ;  static.cc:14:   static bool B = digitalRead(PIN_ENCODER_CHANNEL_B);
	ldi r24,lo8(_ZGVZ13channel_a_isrvE1B)	 ;  _ZGVZ13channel_a_isrvE1B.2_6,
	ldi r25,hi8(_ZGVZ13channel_a_isrvE1B)	 ;  _ZGVZ13channel_a_isrvE1B.2_6,
	movw r30,r24	 ; , _ZGVZ13channel_a_isrvE1B.2_6
	ld r24,Z		 ;  _7, MEM[(char *)_ZGVZ13channel_a_isrvE1B.2_6]
	cp r24, __zero_reg__	 ;  _7
	brne .L4		 ; ,
 ;  static.cc:14:   static bool B = digitalRead(PIN_ENCODER_CHANNEL_B);
	ldi r24,lo8(3)	 ; ,
	call digitalRead	 ; 
	ldi r18,lo8(1)	 ;  _9,
	sbiw r24,0	 ;  _8,
	brne .L5		 ; ,
	ldi r18,0		 ;  _9
.L5:
 ;  static.cc:14:   static bool B = digitalRead(PIN_ENCODER_CHANNEL_B);
	sts _ZZ13channel_a_isrvE1B,r18	 ;  B, _9
	ldi r24,lo8(_ZGVZ13channel_a_isrvE1B)	 ;  _ZGVZ13channel_a_isrvE1B.3_10,
	ldi r25,hi8(_ZGVZ13channel_a_isrvE1B)	 ;  _ZGVZ13channel_a_isrvE1B.3_10,
	ldi r18,lo8(1)	 ;  tmp61,
	movw r30,r24	 ; , _ZGVZ13channel_a_isrvE1B.3_10
	st Z,r18		 ;  MEM[(char *)_ZGVZ13channel_a_isrvE1B.3_10], tmp61
.L4:
 ;  static.cc:16:   steps += A ^ B ? 1 : -1;
	lds r25,_ZZ13channel_a_isrvE1A	 ;  A.5_11, A
	lds r24,_ZZ13channel_a_isrvE1B	 ;  B.6_12, B
 ;  static.cc:16:   steps += A ^ B ? 1 : -1;
	cp r25,r24		 ;  A.5_11, B.6_12
	breq .L6		 ; ,
 ;  static.cc:16:   steps += A ^ B ? 1 : -1;
	ldi r24,lo8(1)	 ;  iftmp.4_15,
	ldi r25,0		 ;  iftmp.4_15
	ldi r26,0		 ;  iftmp.4_15
	ldi r27,0		 ;  iftmp.4_15
	rjmp .L7		 ; 
.L6:
 ;  static.cc:16:   steps += A ^ B ? 1 : -1;
	ldi r24,lo8(-1)	 ;  iftmp.4_15,
	ldi r25,lo8(-1)	 ;  iftmp.4_15,
	movw r26,r24	 ;  iftmp.4_15
.L7:
 ;  static.cc:16:   steps += A ^ B ? 1 : -1;
	lds r20,_ZL5steps	 ;  steps.7_13, steps
	lds r21,_ZL5steps+1	 ;  steps.7_13, steps
	lds r22,_ZL5steps+2	 ;  steps.7_13, steps
	lds r23,_ZL5steps+3	 ;  steps.7_13, steps
	add r24,r20	 ;  _14, steps.7_13
	adc r25,r21	 ;  _14, steps.7_13
	adc r26,r22	 ;  _14, steps.7_13
	adc r27,r23	 ;  _14, steps.7_13
	sts _ZL5steps,r24	 ;  steps, _14
	sts _ZL5steps+1,r25	 ;  steps, _14
	sts _ZL5steps+2,r26	 ;  steps, _14
	sts _ZL5steps+3,r27	 ;  steps, _14
 ;  static.cc:17: }
	nop	
/* epilogue start */
	pop r29		 ; 
	pop r28		 ; 
	ldi r18,0		 ; 
	ldi r20,0		 ; 
	ldi r21,0		 ; 
	ldi r22,0		 ; 
	ldi r23,0		 ; 
	ldi r24,0		 ; 
	ldi r25,0		 ; 
	ldi r26,0		 ; 
	ldi r27,0		 ; 
	ldi r30,0		 ; 
	ldi r31,0		 ; 
	ret	
	.size	_Z13channel_a_isrv, .-_Z13channel_a_isrv
	.ident	"GCC: (GNU) 14.3.0"
.global __do_copy_data
.global __do_clear_bss
