

 
//////////////////////////////////////////////////////////////////////////////////////
//Используя стандартную библиотеку шаблонов STL и класс list по работе 
//с двунаправленным списком
//Даны натуральные числа m и n символы s1,s2,...,sn,(m<n). 
//Получить последовательность символов.
//A)S(m+1),S(m+2),...,Sn,S1...,Sm
//A)S(m+1),S(m+2),...,Sn,Sm...,S1
//////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
 
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////
typedef std::list<char>  T_char_list;
//////////////////////////////////////////////////////////////////////////////////////
void  print_list(const T_char_list&  char_list)
{
    std::copy(char_list.begin(), char_list.end(), 
              std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::locale::global(std::locale(""));
    const int  N_MIN  = 2;
    const int  N_MAX  = 26;
    int        n      = 0;
    do
    {
        std::cout << N_MIN
                  << " <= n <= "
                  << N_MAX
                  << ": ";
 
        std::cin >> n;
    }while(   n < N_MIN
           || N_MAX < n);
 
    const int  M_MIN = N_MIN - 1;
    const int  M_MAX = n - 1;
    int  m = 0;
    do
    {
        std::cout << M_MIN
                  << " <= m <= "
                  << M_MAX
                  << ": ";
 
        std::cin >> m;
    }while(   m < M_MIN
           || M_MAX < m);
 
    struct T_generate_alph
    {
        char  symb_cur_;
        T_generate_alph() : symb_cur_('a')
        {}
        //----------------------------------------------------------------------------
        char  operator() ()
        {
            return  symb_cur_++; 
        }
    };
 
    T_char_list  char_list(n);
    std::generate(char_list.begin(), char_list.end(), T_generate_alph());
    std::cout << "Исходный список:"
              << std::endl;
    print_list(char_list);    
 
    T_char_list::iterator  new_begin(char_list.begin());
    std::advance(new_begin, m);
    std::rotate(char_list.begin(), new_begin, char_list.end());
    std::cout << "Список, циклически сдвинутый на "
              << m 
              << " элементов:"
              << std::endl;
    print_list(char_list);
    
    T_char_list::iterator  tail_begin(char_list.end());
    std::advance(tail_begin, -m);
    std::reverse(tail_begin, char_list.end());
    std::cout << "Последние "
              << m
              << " элементов переставлены в обратном порядке:"
              << std::endl;
    print_list(char_list);        
}

