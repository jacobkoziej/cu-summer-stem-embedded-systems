	.file	"int.cc"
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
	.section	.text._Z13channel_a_isrv,"ax",@progbits
.global	_Z13channel_a_isrv
	.type	_Z13channel_a_isrv, @function
_Z13channel_a_isrv:
	push r28		 ; 
	push r29		 ; 
	 ; SP -= 4	 ; 
	rcall .	
	rcall .	
	in r28,__SP_L__	 ; 
	in r29,__SP_H__	 ; 
/* prologue: function */
/* frame size = 4 */
/* stack size = 6 */
.L__stack_usage = 6
 ;  int.cc:13:   int A = digitalRead(PIN_ENCODER_CHANNEL_A);
	ldi r24,lo8(2)	 ; ,
	call digitalRead	 ; 
	std Y+2,r25	 ;  A,
	std Y+1,r24	 ;  A,
 ;  int.cc:14:   int B = digitalRead(PIN_ENCODER_CHANNEL_B);
	ldi r24,lo8(3)	 ; ,
	call digitalRead	 ; 
	std Y+4,r25	 ;  B,
	std Y+3,r24	 ;  B,
 ;  int.cc:16:   steps += A ^ B ? 1 : -1;
	ldd r18,Y+1	 ;  tmp46, A
	ldd r19,Y+2	 ;  tmp46, A
	ldd r24,Y+3	 ;  tmp47, B
	ldd r25,Y+4	 ;  tmp47, B
	cp r18,r24	 ;  tmp46, tmp47
	cpc r19,r25	 ;  tmp46, tmp47
	breq .L2		 ; ,
 ;  int.cc:16:   steps += A ^ B ? 1 : -1;
	ldi r24,lo8(1)	 ;  iftmp.0_3,
	ldi r25,0		 ;  iftmp.0_3
	ldi r26,0		 ;  iftmp.0_3
	ldi r27,0		 ;  iftmp.0_3
	rjmp .L3		 ; 
.L2:
 ;  int.cc:16:   steps += A ^ B ? 1 : -1;
	ldi r24,lo8(-1)	 ;  iftmp.0_3,
	ldi r25,lo8(-1)	 ;  iftmp.0_3,
	movw r26,r24	 ;  iftmp.0_3
.L3:
 ;  int.cc:16:   steps += A ^ B ? 1 : -1;
	lds r20,_ZL5steps	 ;  steps.1_1, steps
	lds r21,_ZL5steps+1	 ;  steps.1_1, steps
	lds r22,_ZL5steps+2	 ;  steps.1_1, steps
	lds r23,_ZL5steps+3	 ;  steps.1_1, steps
	add r24,r20	 ;  _2, steps.1_1
	adc r25,r21	 ;  _2, steps.1_1
	adc r26,r22	 ;  _2, steps.1_1
	adc r27,r23	 ;  _2, steps.1_1
	sts _ZL5steps,r24	 ;  steps, _2
	sts _ZL5steps+1,r25	 ;  steps, _2
	sts _ZL5steps+2,r26	 ;  steps, _2
	sts _ZL5steps+3,r27	 ;  steps, _2
 ;  int.cc:17: }
	nop	
/* epilogue start */
	 ; SP += 4	 ; 
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29		 ; 
	pop r28		 ; 
	ldi r18,0		 ; 
	ldi r19,0		 ; 
	ldi r20,0		 ; 
	ldi r21,0		 ; 
	ldi r22,0		 ; 
	ldi r23,0		 ; 
	ldi r24,0		 ; 
	ldi r25,0		 ; 
	ldi r26,0		 ; 
	ldi r27,0		 ; 
	ret	
	.size	_Z13channel_a_isrv, .-_Z13channel_a_isrv
	.ident	"GCC: (GNU) 14.3.0"
.global __do_copy_data
.global __do_clear_bss
