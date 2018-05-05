#include <string>
#include <iostream>
#include <fstream>
#include"Polybius.h"
using namespace std;

int main(std::string in, std::string out , int parametr)
{
    std::string tekst;
    if(parametr!=1&&parametr!=0)
    {
        return -1;
    }
    if(parametr==1)
    {
        ifstream myfile(in);
        if(!myfile)
        {
            cout << "Nie można otworzyć pliku!" << endl;
            return -1;
        }
        while(myfile >> tekst){}
        myfile.close();
        ifstream myfile2(out);
        if(!myfile2) {
            cout << "Nie można otworzyć pliku!" << endl;
            return -1;
        }
        myfile2 << PolybiusCrypt(tekst) <<endl;
        myfile2.close();
    }
    if(parametr==0)
    {
        ifstream myfile(in);
        if(!myfile)
        {
            cout << "Nie można otworzyć pliku!" << endl;
            return -1;
        }
        while(myfile >> tekst){}

        ifstream myfile2(out);
        if(!myfile2) {
            cout << "Nie można otworzyć pliku!" << endl;
            return -1;
        }
        myfile2 << PolybiusDecrypt(tekst) <<endl;
        myfile2.close();
    }
    return 0;
}