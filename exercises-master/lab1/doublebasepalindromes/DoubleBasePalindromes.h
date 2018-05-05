#include <iostream>
#include <string>
#include <cstdint>
#include <cctype>
using namespace std;
#ifndef JIMP_EXERCISES_DOUBLEBASEPALINDROMES_H
#define JIMP_EXERCISES_DOUBLEBASEPALINDROMES_H

uint64_t DoubleBasePalindromes(int max_vaule_exculsive);
bool checkIfDecimalPalindrome(int number);
bool checkIfBinaryPalindrome(int number);
string convertToBinary(int number);

#endif //JIMP_EXERCISES_DOUBLEBASEPALINDROMES_H