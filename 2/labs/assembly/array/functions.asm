.486
.model flat
include malloc.inc
; /////////////////////////////////////////////////////////
public _transpose
.code
_transpose proc
		push ebp
		mov ebp, esp
		mov ecx, [ebp + 12]
	ln :
		dec ecx
		mov edx, [ebp + 16]
	lm :
		dec edx
		cmp edx, ecx
		jge nex

		mov esi, [ebp + 8]
		mov esi, [esi + 4 * edx]

		mov edi, [ebp + 8]
		mov edi, [edi + 4 * ecx]

		mov eax, [esi + 4 * ecx]
		mov ebx, [edi + 4 * edx]
		mov[esi + 4 * ecx], ebx
		mov[edi + 4 * edx], eax
	nex :
		test edx, edx
		jnz lm
		test ecx, ecx
		jnz ln
		pop ebp
		ret
_transpose endp
; /////////////////////////////////////////////////////////
public _find_max_sequence
.code
_find_max_sequence proc
		push ebp
		mov ebp, esp
		mov esi, [ebp + 8]
		mov edx, [ebp + 12]
		xor ecx, ecx
		mov eax, 1

	lp:
		cmp ecx, eax
		jge nmax
		mov ecx, eax
	nmax:
		dec edx
		test edx, edx
		jz finish
		
		mov ebx, [esi]
		cmp ebx, [esi + 4]
		je equa
		xor eax, eax
	equa:
		inc eax
		add esi, 4
		jmp lp
	finish:
		mov eax, ecx	
		pop ebp
		ret
_find_max_sequence endp
; /////////////////////////////////////////////////////////
public _unique_array
.code
_unique_array proc
		push ebp
		mov ebp, esp
		mov esi, [ebp + 8] ; int *a_src
		mov edi, [ebp + 16] ; int *a_dest
		mov edx, [ebp + 12] ; int n
		mov ebx, 0

	lpedx:
		dec edx
		mov eax, [esi + 4 * edx]
		mov ecx, [ebp + 12]
	lpecx:
		dec ecx
		cmp ecx, edx
		jz nexx
		cmp eax, [esi + 4 * ecx]
		jnz nexx
		jmp nuni
	nexx:
		test ecx, ecx
		jnz lpecx

		mov [edi + 4 * ebx], eax
		inc ebx
	nuni:
		test edx, edx
		jnz lpedx

		mov eax, [ebp + 20]
		mov [eax], ebx

		pop ebp
		ret
_unique_array endp
; /////////////////////////////////////////////////////////
public _count_unique
.code
_count_unique proc
		push ebp
		mov ebp, esp
		mov esi, [ebp + 8] ; int *a
		mov ebx, [ebp + 12] ; int n
		mov edx, ebx ; int n
	lpedx:
		dec edx
		mov eax, [esi + 4 * edx]
		mov ecx, [ebp + 12]
	lpecx:
		dec ecx
		cmp ecx, edx
		jz nexx
		cmp eax, [esi + 4 * ecx]
		jnz nexx
		dec ebx
		jmp tedx
	nexx:
		test ecx, ecx
		jnz lpecx
	tedx:
		test edx, edx
		jnz lpedx
		mov eax, ebx
		pop ebp
		ret
_count_unique endp
; /////////////////////////////////////////////////////////
public _sort_array
.code
_sort_array proc
		push ebp
		mov ebp, esp
		mov esi, [ebp + 8] ; int *as
		mov edx, [ebp + 12] ; int n

	lpedx:
		dec edx
		mov eax, [esi + 4 * edx]
		mov ecx, edx
	lpecx:
		dec ecx
		cmp eax, [esi + 4 * ecx]
		jge tecx
		xchg [esi + 4 * ecx], eax ; swap
		mov [esi + 4 * edx], eax
	tecx:
		test ecx, ecx
		jnz lpecx
		cmp edx, 1
		jg lpedx

		pop ebp
		ret
_sort_array endp
; /////////////////////////////////////////////////////////
public _merge
.code
_merge proc
.data
	m_ptr dd 0
	n dd 0
	tmp dd 0
.code
	push ebp
	mov ebp, esp
	mov esi, [ebp + 8] ; int *a1
	mov edi, [ebp + 16] ; int *a2
	mov ebx, [ebp + 12] ; int n1
	mov edx, [ebp + 20] ; int n2
	mov eax, [ebp + 24] ; int *m_ptr
	mov m_ptr, eax
	mov eax, [ebp + 28] ; int &n
	mov n, eax
	mov ecx, 0

	pushad

	push ebx
	push esi
	call _sort_array
	pop esi
	pop ebx

	popad
	pushad

	push edx
	push edi
	call _sort_array
	pop edx
	pop edi

	popad

	dec edx
	dec ebx

lp:
	cmp edx, 0
	jl emp_di
	cmp ebx, 0
	jl emp_si
	
	mov eax, [esi + 4 * ebx]
	mov tmp, eax
	mov eax, [edi + 4 * edx]
	cmp tmp, eax
	jg mov_si
	jmp mov_di

emp_di:
	cmp ebx, 0
	jl m_end
	jmp mov_si

emp_si:
	cmp edx, 0
	jl m_end
	jmp mov_di

mov_si:
	push ebp
	mov eax, [esi + 4 * ebx]
	mov ebp, m_ptr
	mov [ebp + 4 * ecx], eax
	inc ecx
	pop ebp
	dec ebx
	jmp lp

mov_di:
	push ebp
	mov eax, [edi + 4 * edx]
	mov ebp, m_ptr
	mov [ebp + 4 * ecx], eax
	inc ecx
	pop ebp
	dec edx
	jmp lp

m_end:
	mov esi, n
	mov [esi], ecx
	pop ebp
	ret
_merge endp
; /////////////////////////////////////////////////////////
public _find 
.code
_find proc
		push ebp
		mov ebp, esp
		mov edi, [ebp + 8] ; int *a
		mov ecx, [ebp + 12] ; int n
		mov eax, [ebp + 16] ; int f
		cmp ecx, 0
		jle m_last
		
		repnz scasd
		jnz m_last
		mov eax, 1
		jmp m_end
	m_last:
		mov eax, 0
	m_end:
		pop ebp
		ret
_find endp
; /////////////////////////////////////////////////////////
public _array_conjuction
.data
	curr dd 0
.code
_array_conjuction proc
		push ebp
		mov ebp, esp
		mov esi, [ebp + 8] ; int *a1
		mov edi, [ebp + 16] ; int *a2
		mov ebx, [ebp + 12] ; int n1
		mov edx, [ebp + 20] ; int n2
		mov eax, [ebp + 24] ; int *a
		mov m_ptr, eax
		mov eax, [ebp + 28] ; int n
		mov n, eax
		mov ecx, 0

	lp:
		cmp ebx, 0
		jle f_edi

	f_esi:
		mov eax, [esi]
		mov curr, eax
		add esi, 4
		dec ebx
		jmp m_f
	f_edi:
		cmp edx, 0
		jle m_end
		mov eax, [edi]
		mov curr, eax
		add edi, 4
		dec edx
	
	m_f:

		pushad
		push eax
		push edx
		push edi
		call _find
		mov tmp, eax
		pop edi
		pop edx
		pop eax
		popad

		mov eax, tmp
		test eax, eax
		jnz m_nadd

		pushad
		push eax
		push ebx
		push esi
		call _find
		mov tmp, eax
		pop esi
		pop ebx
		pop eax
		popad

		mov eax, tmp
		test eax, eax
		jnz m_nadd

		push ebx
		mov ebx, m_ptr
		mov eax, curr
		mov [ebx + 4 * ecx], eax
		inc ecx
		pop ebx

	m_nadd:
		jmp lp

	m_end:
		mov eax, n
		mov [eax], ecx
		pop ebp
		ret
_array_conjuction endp
; /////////////////////////////////////////////////////////

end