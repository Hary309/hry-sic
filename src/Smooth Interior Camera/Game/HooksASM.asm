

extern CameraEvent_Address: qword

.code

Asm_CameraEvent PROC

	; backup registers
	push rax
	push rcx
	push rdx
	push r8

	; call library function
	mov rax, CameraEvent_Address
	call rax

	; restore registers
	pop r8
	pop rdx
	pop rcx
	pop rax

	add rsp, 38h
	ret

Asm_CameraEvent ENDP

End
