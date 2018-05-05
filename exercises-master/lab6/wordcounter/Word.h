

#include<string>
using std::string;

namespace datastructures {
    class Word {
    public:

        Word();
        Word(string str);

        string GetWord() const;

        bool operator==(const Word &other) const;
        bool operator<(const Word &other) const;
        bool operator>(const Word &other) const;;
        operator string() const;

    private:
        std::string word_;
    };
}


