#include <utility>
#include <string>
#include <array>
#include <memory>
#include <regex>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#ifndef JIMP_EXERCISES_TINYURL_H
#define JIMP_EXERCISES_TINYURL_H

namespace tinyurl {
using ::std::array;
using ::std::string;
using ::std::regex;
using ::std::cout;
using ::std::cin;
using ::std::unique_ptr;

    struct TinyUrlCodec {
        array<char, 6> state;
        string fullUrl;
    };

    std::unique_ptr<TinyUrlCodec> Init();
    void NextHash(std::array<char, 6> *state);
    std::string Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec);
    std::string Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash);
}


#endif //JIMP_EXERCISES_TINYURL_H