

#ifndef JIMP_EXERCISES_WORDCOUNTER_H
#define JIMP_EXERCISES_WORDCOUNTER_H

#include "Word.h"
#include "Counts.h"
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <initializer_list>
#include <string>
using std::string;
using std::vector;
using std::pair;
using std::set;

namespace datastructures{
    class WordCounter {
    public:
        WordCounter() = default;
        WordCounter(const std::initializer_list<Word> &argument);
        WordCounter(string path_to_file);

        int operator[](const string &key);
        friend std::ostream &operator<<(std::ostream &os, WordCounter &wordCounter);
        int TotalWords() const;
        int DistinctWords() const;
        set<Word> Words() const;

    private:
        vector<pair<Word,Counts>> words_list_;

    };
    std::ostream &operator<<(std::ostream &os, WordCounter &wordCounter);
}

#endif //JIMP_EXERCISES_WORDCOUNTER_H
