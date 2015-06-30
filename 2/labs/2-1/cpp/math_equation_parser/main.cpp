// Аквух Джеймс
// 13.02.2015
// Парсер математических выражений с ипользованием постфиксной записи

#include <iostream>
#include "parser.h"
#include <clocale>

#define BUFFER_LENGTH 1024

int main() {
 
  setlocale(LC_ALL, "RU");
  setlocale(LC_NUMERIC,"C");
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  
  std::cout << "\nВас приветствует Парсер 1.0!";
  std::cout << "\nНаберите \"exit\" для выхода";
  std::cout << "\nВы можете использовать:";
  std::cout << "\n\tЧисла в формате \"1\", \"3.14\" или \"3,14\", и кроме того знаки \"-+/*^\"";
  std::cout << "\n\tПеременные в формате \"a\", \"var\" или даже \"BSU\"";
  std::cout << "\n\tСкобки двух типов: \"([])\"";
  std::cout << "\n\tФункции вида f(x) такие как sin, cos, tan, asin, acos, atan, "
               "log, ln, log10, sqrt (позже добавяться новые...)";
  printf("\n\nВведите выражение:\t");

  char buffer[BUFFER_LENGTH];
  while (gets(buffer) != NULL && strstr(buffer, "exit") == NULL) {
    if (strlen(buffer) == 0 || strstr(buffer, "//") != NULL) continue;
    try {
      Parser* parser = new Parser;
      parser->parse(buffer);
      printf("\n\nYour equation:   %s\nPostfix notation:   %s\nResult:   %G",
             parser->getEquation().c_str(), parser->getPolishNotation().c_str(),
             static_cast<float>(parser->calculate()));
    } catch (utils::BaseException& e) {
      printf("\nERROR:\t%s\n", e.getDescription().c_str());
    } catch (std::exception& e) {
      std::cerr << "exception caught: " << e.what() << '\n';
    }
    printf("\n\nВведите выражение:\t");
  }
  return 0;
}