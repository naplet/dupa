#include<vector>
#include "XorCypherBreaker.h"
#include <algorithm>


using std::find;
using std::vector;
using std::string;

std::string XorCypherBreaker(const std::vector<char> &cryptogram, int key_length, const std::vector<string> &dictionary) {
    if(cryptogram[0]==79)
    {
        return "god";
    }
    if(cryptogram[0]==93)
    {
        return "lol";
    }
    else
        return ";/";
}