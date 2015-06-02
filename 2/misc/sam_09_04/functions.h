// Вычисляет длину строки
extern "C" int __cdecl len(char*);

// Находит расстояние до средней цифры
extern "C" int __cdecl middle_offset(char*);

// Копирует цифры начиная с середины числа
extern "C" void __cdecl copy_from_the_middle(char* /*src*/, char* /*dest*/);

extern "C" int __cdecl mystoi(char*);

float mysqrt(float x)
{
	__asm
	{
			finit
			fld x
			fsqrt
			fstp x
	}
	return x;
}