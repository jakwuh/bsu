#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath> 

using namespace std;

int main()
{
    int start = clock();

    int i = 0;

    while (i < 1000000000)
    {
        i++;
    }


    int end = clock();
    cout << end - start;
    return 0;
}