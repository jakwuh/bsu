.486
.model flat
;//////////////////////////////////////////////////////////
public _len
.code
_len proc
        push ebp
        mov ebp, esp
        mov eax, 0
        mov ecx, 0FFFFFFFFh
        mov edi, [ebp + 8]
        cld

        repnz scasb
        mov eax, 0FFFFFFFEh
        sub eax, ecx

        pop ebp
        ret
_len endp
;//////////////////////////////////////////////////////////
public _middle_offset
.code
_middle_offset proc
		push ebp
		mov ebp, esp
		mov esi, [ebp + 8]

		push edi
		push esi
		call _len
		pop esi
		pop edi

		xor edx, edx
		mov ebx, 2
		idiv ebx

		pop ebp
		ret
_middle_offset endp
;//////////////////////////////////////////////////////////
public _min
.code
_min proc
		push ebp
		mov ebp, esp
		mov eax, [ebp + 8]; int a
		mov ebx, [ebp + 12]; int b

		cmp eax, ebx
		jbe m_end
		mov eax, ebx

	m_end:
		pop ebp
		ret
_min endp
;//////////////////////////////////////////////////////////
public _copy_from_the_middle
.data
	middle dd 0
	zero db 060o
.code
_copy_from_the_middle proc
		push ebp
		mov ebp, esp
		mov esi, [ebp + 8] ; char* source
		mov edi, [ebp + 12] ; char* destination

		push edi
		push esi
		call _middle_offset
		mov middle, eax
		pop esi
		pop edi

		add esi, middle
		xor eax, eax
		mov al, [esi]
		sub al, zero
		mov ebx, middle
		inc ebx
		
		push edi
		push esi
		push eax
		push ebx
		call _min
		mov ecx, eax
		pop eax
		pop eax
		pop esi
		pop edi

		rep movsb

		mov [edi], ecx

		pop ebp
		ret
_copy_from_the_middle endp
;//////////////////////////////////////////////////////////
public _mystoi
.code
_mystoi proc
		push ebp
		mov ebp, esp
		mov esi, [ebp + 8]

		push esi
		call _len
		pop esi

		mov ecx, eax
		add esi, eax
		dec esi

		mov edx, 0
		mov ebx, 1

	lp:
		xor eax, eax
		mov al, [esi]
		sub al, zero

		push edx
		mul ebx
		pop edx
		add edx, eax

		push edx
		mov eax, ebx
		mov ebx, 10
		mul ebx
		mov ebx, eax
		pop edx

		dec esi
		loop lp

		mov eax, edx
		pop ebp
		ret
_mystoi endp
;//////////////////////////////////////////////////////////
end