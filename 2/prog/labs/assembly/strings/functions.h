
// Вычисляет длину строки
extern "C" int __cdecl len(char*);

// Сравнивает две С-строки
extern "C" int __cdecl cmp(char*, char*);

// Заменяет все вхождения символ1 в строке на символ2
extern "C" void __cdecl replace(char*, char /*var1*/, char /*var2*/);

// Определяет является ли строка палиндромом
extern "C" bool __cdecl palindrom(char*);

// Считает количество слов
extern "C" int __cdecl count_words(char*);

// Удаляет во всей строке все вхождения символа
extern "C" void __cdecl remove_char(char*, char);

// Удаляет все, что находится внутри скобок (...)
extern "C" void __cdecl clear_brackets(char*);

// Находит кратчайшее слово в строке
extern "C" int __cdecl shortest_word(char*);