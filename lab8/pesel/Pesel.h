//
// Created by bobo on 25.04.18.
//

#ifndef JIMP_EXERCISES_PESEL_H
#define JIMP_EXERCISES_PESEL_H

#include <string>

namespace academia {
    class InvalidPeselLength{

    };
    class InvalidPeselCharacter{

    };

    class TooShortPeselThrowsInvalidPeselLenghtException : InvalidPeselLength{

    };
    class TooLongPeselThrowsInvalidPeselLenghtExceptio : InvalidPeselLength{

    };
    class InvalidPeselChecksum : public invalid_argument{
    public:
        InvalidPeselChecksum();
        InvalidPeselChecksum(std::string pesel, int sum);
        void what();

    private:
        std::string pesel_;
        int sum_;
    };

    class AcademiaDataValidationError{

    };


    class Pesel {
    private:
        std::string pes_;
    public:
        Pesel(const std::string &pesel);

        void validatePesel(const std::string &pesel);


    };

}
#endif //JIMP_EXERCISES_PESEL_H
