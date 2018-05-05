#include "Word.h"

namespace datastructures{
    Word::Word() {
        word_="";
    }

    Word::Word(string str) {
        word_=str;
    }

    string Word::GetWord() const {
        return word_;
    }

    bool Word::operator<(const Word &other) const {
        return word_ < other.GetWord();
    }

    bool Word::operator>(const Word &other) const {
        return word_ > other.GetWord();
    }

    bool Word::operator==(const Word &other) const {
        return word_ == other.GetWord();
    }

    Word::operator string() const {
        return word_;
    }
}