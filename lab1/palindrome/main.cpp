#include<iostream>
#include <string>
#include "Palindrome.h"
int main()
{
    std::string zdanie;
    int a=0;
    while(a!=1)
    {
        std::cout << "Wpisz 2 jeśli chcesz sprawdzic palindrom, wpisz 1 jeśli chcesz wyjść";
        std::cin >> a;
        if(a==2)
        {
            std::cout << "Wpisz zdanie";
            getline(std::cin,zdanie);
            is_palindrome(zdanie);
            a=0;
        }
    }
    return 0;
}