; ** @file HooksASM.asm
; ** @author Piotr Krupa (piotrkrupa06@gmail.com)
; ** @license MIT License
; **

IFDEF RAX

extern CameraEvent_CallAddress: qword
extern CameraEvent_RetnAddress: qword

.code

Asm_CameraEvent_V1 PROC

	; backup registers
	push rax
	push rcx
	push rdx
	push r8

	; call library function
	call CameraEvent_CallAddress

	; restore registers
	pop r8
	pop rdx
	pop rcx
	pop rax

	; jump to End
	jmp CameraEvent_RetnAddress
Asm_CameraEvent_V1 ENDP

Asm_CameraEvent_V2 PROC

	; backup registers
	push rax
	push rdx
	push r8

	; call library function
	push rcx
	mov rcx, rdi
	call CameraEvent_CallAddress
	pop rcx

	; restore registers
	pop r8
	pop rdx
	pop rax

	; jump to End
	jmp CameraEvent_RetnAddress
Asm_CameraEvent_V2 ENDP

ENDIF

End
