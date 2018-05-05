
#include "Palindrome.h"
#include <string>
#include <iostream>
bool is_palindrome(std::string str)
{
    std::string napis=str;
    int i,j;
    for (i = 0, j = napis.length()-1; i < j; i++, j--)
    {
    if (napis[i] == ' ') i++;
    if (napis[j] == ' ') j--;
    if (napis[i] != napis[j])
    break;
    }
    if (i < j)
        {
        return false;
        }
    else{
        return true;
        }
}
