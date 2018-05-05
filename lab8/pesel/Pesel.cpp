//
// Created by bobo on 25.04.18.
//

#include <iostream>
#include "Pesel.h"

using namespace std;
namespace academia {
    InvalidPeselChecksum::InvalidPeselChecksum(std::string pesel, int sum) {
        pesel_ = pesel;
        sum_ = sum;
    }
    void InvalidPeselChecksum::what() {
        cout << "Invalid PESEL(" << pesel_ << " ) checksum: " << sum_;
    }

    Pesel::Pesel(const string &pesel) {
        if()
    }

    void Pesel::validatePesel(const string &pesel) {
        if (pesel.length() != 11){
            if (pesel.length() < 11){
                throw InvalidPeselLength();
            } else{

            }
            throw   InvalidPeselLength();
        }

        for(auto x : pesel){
            if ( int(x) < 48 && int(x) > 57 ){
                throw InvalidPeselCharacter ();
            }
        }
        int suma = 0;
        int mnoznik = 9;
        string Pes = pesel;
        Pes.pop_back();
        for(char x : Pes){
            if (mnoznik == -1){
                mnoznik = 9;
            }

            suma += (int(x) - '0') * mnoznik;
            mnoznik -= 2;

            if(mnoznik == 5){
                mnoznik = 3;
            }
        }
        cout << suma % 10 << endl;
        cout << (int(pesel[10]) - '0') << endl;
        if(suma % 10 != (int(pesel[10]) - '0')){
            throw InvalidPeselChecksum();
        }

    }
}