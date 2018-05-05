

#include "TinyUrl.h"


std::unique_ptr<tinyurl::TinyUrlCodec> tinyurl::Init() {
    std::unique_ptr<tinyurl::TinyUrlCodec> newPointer = std::make_unique<tinyurl::TinyUrlCodec>();
    return newPointer;
}

void tinyurl::NextHash(std::array<char, 6> *state) {
    int i = 5;
    bool finished = false;

    while(!finished) {
        int actualValue = (int)(*state)[i];
        if(actualValue == 122) {
            (*state)[i] = '0';
            i--;
        }
        if(actualValue < 122)
        {
            if(actualValue+1 > 90 && actualValue+1<97 )
                (*state)[i] = char(actualValue+7);
            else
                (*state)[i] = char(actualValue + 1);
            if(actualValue+1 > 57 && actualValue+1<65)
                (*state)[i] = char(actualValue+8);
            finished = true;
        }

    }
}

std::string tinyurl::Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec) {
    string encodedUrl =string("");
    (*codec)->fullUrl = url;
    NextHash( &((*codec)->state));
    for(int i=0; i<6; i++)
        encodedUrl += (*codec)->state[i];

    return encodedUrl;
}

std::string tinyurl::Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash) {
    return codec->fullUrl;
}