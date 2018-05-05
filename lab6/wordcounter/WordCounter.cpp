#include "WordCounter.h"

namespace datastructures{
    WordCounter::WordCounter(const std::initializer_list<Word> &argument) {
        for (auto value:argument){
            auto it=words_list_.begin();
            for (it; it!=words_list_.end(); ++it){
                if (it->first==value) break;
            }
            if (it != words_list_.end()){
                ++(it->second);
            }
            else{
                words_list_.emplace_back(std::make_pair(value,Counts()));
            }
        }
    }

    WordCounter::WordCounter(std::string path_to_file) {
        std::ifstream file;
        file.open(path_to_file, std::ios::in);
        if (file.good()){
            string str;
            while (!file.eof()){
                file >> str;
                string tmp="";
                for (char cur : str){
                    if (isalpha(cur)) tmp+=cur;
                }
                if (!tmp.empty()){
                    auto it=words_list_.begin();
                    for (it; it!=words_list_.end(); ++it){
                        if ((string)it->first==tmp) break;
                    }
                    if (it != words_list_.end()){
                        ++(it->second);
                    }
                    else{
                        words_list_.emplace_back(std::make_pair(Word(tmp),Counts()));
                    }
                }
                str = "";
            }
            file.close();
        }
        else{
            perror("Open error");
        }
    }

    int WordCounter::operator[](const string &key) {
        for (auto value:words_list_){
            if ((string)value.first==key) return (int)value.second;
        }
        return 0;
    }

    std::ostream &operator<<(std::ostream &os, WordCounter &wordCounter) {
        os << "Distinct words: " << wordCounter.DistinctWords() << "   " << "Total words: " << wordCounter.TotalWords() << std::endl;
        std::sort(wordCounter.words_list_.begin(),wordCounter.words_list_.end());
        for (auto n: wordCounter.words_list_)   os << (string)n.first << "  ";
        os << std::endl;
        return os;
    }

    int WordCounter::TotalWords() const {
        int sum=0;
        for (auto const &value : words_list_)  sum+=value.second;
        return sum;
    }

    int WordCounter::DistinctWords() const {
        return (int)words_list_.size();
    }

    set<Word> WordCounter::Words() const {
        set<Word> words;
        for (auto const &value : words_list_)  words.insert(value.first);
        return words;
    }

}