#include "DoubleBasePalindromes.h"

uint64_t DoubleBasePalindromes(int max_value_exculsive) {
    uint64_t result;

    for(int i=0; i<= max_value_exculsive; i++) {
        if(checkIfBinaryPalindrome(i) && checkIfDecimalPalindrome(i))   result += i;
    }
    return result;
}

bool checkIfDecimalPalindrome(int number) {
    string numberInString = to_string(number);
    string reversed = "";
    size_t length = numberInString.size();

    for(int i=length-1; i>=0; i--)  reversed += numberInString[i];

    if(reversed == numberInString)  return true;
    else                            return false;
}

bool checkIfBinaryPalindrome(int number) {
    string binaryNumber = convertToBinary(number);
    string reversedBinaryNumber = "";
    size_t length = binaryNumber.size();

    for(int i=length-1; i>=0; i--)  reversedBinaryNumber += binaryNumber[i];
    if(reversedBinaryNumber == binaryNumber)    return true;
    else                                        return false;
}

string convertToBinary(int number) {
    string binaryNumber;
    int tmp;

    while(number>0) {
        tmp = number%2;
        binaryNumber = to_string(tmp) + binaryNumber;
        number /= 2;
    }
    return binaryNumber;
}