; ** @file HooksASM.asm
; ** @author Piotr Krupa (piotrkrupa06@gmail.com)
; ** @license MIT License
; **

IFDEF RAX

extern CameraEvent_Address: qword
extern CameraEvent_RetnAddress: qword

.code

Asm_CameraEvent PROC

	; backup registers
	push rax
	push rcx
	push rdx
	push r8

	; call library function
	call CameraEvent_Address

	; restore registers
	pop r8
	pop rdx
	pop rcx
	pop rax

	; jump to End
	jmp CameraEvent_RetnAddress
Asm_CameraEvent ENDP

ENDIF

End
