.text

.global __avr_setup
.global __avr_interrupt_vectors
.global __avr_unexpected_interrupt
.global main

.org 0x0000

__avr_interrupt_vectors:
  jmp __avr_setup
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt
  jmp __avr_unexpected_interrupt

__avr_unexpected_interrupt:
  jmp __avr_interrupt_vectors

__avr_stack_pointer_h = 0x3e
__avr_stack_pointer_l = 0x3d
__avr_status_register = 0x3f

__avr_setup:
  # Clear the status register
  ldi r16,0x0
  out __avr_status_register,r16

  # Configure the stack pointer to start at 0x08ff
  ldi r16,0x08
  out __avr_stack_pointer_h,r16
  ldi r16,0xff
  out __avr_stack_pointer_l,r16

  # Execute main
  call main

pause:
  ldi r16,1
.LZ:
  cpi r16,100
  breq .LZend
  inc r16
  ldi r17,0
.LY:
  cpi r17,100
  breq .LYend
  inc r17
  ldi r18,0
.LX:
  cpi r18,100
  breq .LXend
  inc r18
  jmp .LX
.LXend:
  jmp .LY
.LYend:
  jmp .LZ
.LZend:
  ret

__DDRB = 0x04
__PORTB = 0x05

main:
  ldi r16,1
  out __DDRB,r16
.LED_ON:
  ldi r16,1
  out __PORTB,r16
  call pause
  ldi r16,0
  out __PORTB,r16
  call pause
  jmp .LED_ON

