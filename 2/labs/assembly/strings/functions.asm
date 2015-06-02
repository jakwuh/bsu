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
public _cmp
.data 
    m_len dd 0
.code
_cmp proc
        push ebp
        mov ebp, esp
        mov esi, [ebp + 8] ; char *s1
        cld

        push esi
        call _len
        pop esi

        mov edi, [ebp + 12] ; char *s2
        mov m_len, eax ; m_len = len(s1)

        push esi
        push edi
        call _len
        pop edi
        pop esi
        
        cmp eax, m_len
        jae m_less
        mov m_len, eax ; m_len = min(m_len, len(s2))
    m_less:

        mov ecx, m_len
        inc ecx

        repe cmpsb
        jz m_equ
        ja m_abo
        jb m_bel

    m_abo:
        mov eax, 1
        jmp m_end
    m_bel:
        mov eax, -1
        jmp m_end
    m_equ:
        mov eax, 0
        jmp m_end
    m_end:
        pop ebp
        ret
_cmp endp
;//////////////////////////////////////////////////////////
public _replace
.code
_replace proc
        push ebp
        mov ebp, esp
        mov edi, [ebp + 8] ; char *s
        cld

        push edi
        call _len
        pop edi
        mov ecx, eax

        mov al, [ebp + 12] ; char from
        mov bl, [ebp + 16] ; char to

    lp:
        test ecx, ecx
        jz m_end

        repnz scasb
        jnz lp

        mov byte ptr [edi - 1], bl
        jmp lp

    m_end:
        pop ebp
        ret
_replace endp
;//////////////////////////////////////////////////////////
public _palindrom
.code
_palindrom proc
        push ebp
        mov ebp, esp
        mov edi, [ebp + 8] ; char *s
        cld

        push edi
        call _len
        pop edi

        mov esi, edi
        add esi, eax
        mov ebx, 2
        xor edx, edx
        div ebx
        dec esi

    lp:
        test eax, eax
        jz m_pal
        dec eax

        cmpsb ; cmpsb increases edi esi but we don't need
        jnz m_npal
        
        sub esi, 2

        jmp lp

    m_npal:
        mov eax, 0
        jmp m_end
    m_pal:
        mov eax, 1
    m_end:
        pop ebp
        ret
_palindrom endp
;//////////////////////////////////////////////////////////
public _count_words
.data
    spc db 040o
.code
_count_words proc
        push ebp
        mov ebp, esp
        mov edi, [ebp + 8] ; char *s
        cld

        push edi
        call _len
        pop edi

        mov ecx, eax ; ecx = len(s)
        mov al, spc ; ' '
        xor ebx, ebx

    lp:
        test ecx, ecx
        jz m_end

        repne scasb
        jnz lp
        inc ebx

        jmp lp

    m_end:
        mov eax, ebx
        inc eax
        pop ebp
        ret
_count_words endp
;//////////////////////////////////////////////////////////
public _remove_char
.code
_remove_char proc
        push ebp
        mov ebp, esp
        mov edi, [ebp + 8] ; char *s
        cld

        push edi
        call _len
        pop edi

        mov ecx, eax ; len(s)
        mov al, [ebp + 12] ; char c

    lp:
        test ecx, ecx
        jz m_end

        repne scasb
        jnz m_end

        dec edi
        inc ecx

        push ecx
        push edi
        call _shls
        pop edi
        pop ecx

        dec ecx
        jmp lp

    m_end:
        pop ebp
        ret
_remove_char endp
;//////////////////////////////////////////////////////////
public _shls
.code
_shls proc
        push ebp
        mov ebp, esp
        mov edi, [ebp + 8] ; char *s
        mov ecx, [ebp + 12] ; int number_of_bytes to shl
        mov esi, edi
        inc esi
        cld

        rep movsb

        pop ebp        
        ret
_shls endp
;//////////////////////////////////////////////////////////
public _clear_brackets
.data
    op_brack db 050o
    cl_brack db 051o
    endl db 0o
.code
_clear_brackets proc
        push ebp
        mov ebp, esp
        mov edi, [ebp + 8] ; char *s
        cld

        push edi
        call _len
        pop edi

        mov ecx, eax ; len(s)

    lp:

        mov al, op_brack
        repnz scasb
        jnz m_end

        pushad
		mov edx, 1
    lp2:
        mov al, byte ptr [edi]

		cmp al, op_brack
		jnz m_jmp
		inc edx
	m_jmp:
        cmp al, cl_brack
		jnz m_jmp2
		dec edx
		test edx, edx
        jz m_next
	m_jmp2:
        cmp al, endl
        jz m_end

        push ecx
        push edi
        call _shls
        pop edi
        pop ecx
        dec ecx

        jmp lp2
    
    m_next:
        popad

        loop lp

    m_end:
        pop ebp
        ret
_clear_brackets endp
;//////////////////////////////////////////////////////////
public _shortest_word
.code
_shortest_word proc
        push ebp
        mov ebp, esp
        mov esi, [ebp + 8] ; char *s
        xor ebx, ebx
        mov ecx, 0FFFFFFFFh

    lp:
        lodsb
        cmp al, endl
        jz m_end
        cmp al, spc
        jz m_spc
        
    m_nspc:
        inc ebx
        jmp lp
    m_spc:
        call m_cmp
        xor ebx, ebx
        jmp lp
    m_end:
        call m_cmp
        mov eax, ecx
        pop ebp
        ret

    m_cmp:
        cmp ecx, ebx
        jbe nmin
        mov ecx, ebx
    nmin:
        ret


_shortest_word endp
;//////////////////////////////////////////////////////////

end