// SPDX-License-Identifier: MPL-2.0
/*
 * ws2812b.S -- WS2812B driver
 * Copyright (C) 2025  Jacob Koziej <jacobkoziej@gmail.com>
 */

#if F_CPU != 16000000ULL
#error "F_CPU must be 16 MHz"
#endif

#include <avr/io.h>

	.section .text.ws2812b_tx, "ax", %progbits

#define COLORS 3
#define MASK   (1 << 7)

#define port_l   r26
#define port_h   r27
#define port     X
#define buffer_l r28
#define buffer_h r29
#define buffer   Y
#define pixels_l r30
#define pixels_h r31
#define pixels   Z

#define nport_mask r24
#define port_mask  r25
#define port_low   r24
#define port_high  r25

#define restore_int r23
#define color_index r22
#define color       r21
#define port_value  r20
#define mask        r19
#define bit_set     r18

	.type   ws2812b_tx, %function
	.global ws2812b_tx
ws2812b_tx:
	push r28
	push r29

	movw port,   r24
	movw buffer, r20
	movw pixels, r18

	ldi port_mask, 1

.Lconstruct_port_mask:
	tst  r22
	breq .Lcompute_nport_mask

	dec  r22
	lsl  port_mask
	rjmp .Lconstruct_port_mask

.Lcompute_nport_mask:
	mov nport_mask, port_mask
	com nport_mask

	// Since we need to bang out bits at 800 kHz, and our clock
	// is running at only 16 MHz, we have no room for interrupts!
	clr  restore_int
	brid .Lcompute_high_and_low_values
	cli
	ser  restore_int

.Lcompute_high_and_low_values:
	ld  port_value, port
	or  port_mask,  port_value  // or  port_high, port_value
	and nport_mask, port_value  // and port_low,  port_value

	adiw pixels, 1
.Ltx_pixel:
	sbiw pixels, 1
	breq .Ltx_done

	ldi color_index, COLORS + 1
.Lnext_color:
	dec  color_index
	breq .Ltx_pixel

	ld color, buffer+

	ldi mask, MASK

.Lnext_bit:
	st port, port_high   // T0H =   0.0 ns, T1H =   0.0 ns

	mov  bit_set, color  // T0H = 125.0 ns, T1H = 125.0 ns
	and  bit_set, mask   // T0H = 187.5 ns, T1H = 187.5 ns
	breq .Lzero_code     // T0H = 250.0 ns, T1H = 250.0 ns

.Lone_code:
	nop                  //                 T1H = 312.5 ns
	nop                  //                 T1H = 375.0 ns
	nop                  //                 T1H = 437.5 ns
	nop                  //                 T1H = 500.0 ns
	nop                  //                 T1H = 562.5 ns
	nop                  //                 T1H = 625.0 ns
	nop                  //                 T1H = 687.5 ns
	nop                  //                 T1H = 750.0 ns
	nop                  //                 T1H = 812.5 ns

	st port, port_low    //                 T1H = 875.0 ns

	lsr  mask            //                 T1L = 125.0 ns
	breq .Lnext_color    //                 T1L = 187.5 ns
	rjmp .Lnext_bit      //                 T1L = 250.0 ns


.Lzero_code:
	st port, port_low    // T0H = 375.0 ns

	nop                  // T0L = 125.0 ns
	nop                  // T0L = 187.5 ns
	nop                  // T0L = 250.0 ns
	nop                  // T0L = 312.5 ns
	nop                  // T0L = 375.0 ns
	nop                  // T0L = 437.5 ns
	nop                  // T0L = 500.0 ns
	nop                  // T0L = 562.5 ns

	lsr  mask            // T0L = 625.0 ns
	breq .Lnext_color    // T0L = 687.5 ns
	rjmp .Lnext_bit      // T0L = 750.0 ns

.Ltx_done:
	cpse restore_int, r1
	sei

	pop r29
	pop r28

	ret
