
#ifndef JIMP_EXERCISES_TEXTPOOL_H
#define JIMP_EXERCISES_TEXTPOOL_H
#include <initializer_list>
#include <string>
#include <cstring>
#include <iostream>
#include <experimental/string_view>
#include <set>
#include <vector>
namespace pool {
    using ::std::string;
    using ::std::experimental::string_view;
    using ::std::size_t;
    using ::std::vector;
    using ::std::initializer_list;
    using ::std::move;
    using ::std::strcmp;
    using ::std::set;
    using ::std::cin;
    using ::std::cout;


    class TextPool {
    public:
        TextPool();

        TextPool(const initializer_list<string> &Ptr);

        TextPool(TextPool &&Ptr);

        ~TextPool();

        TextPool& operator=(TextPool &&Ptr);

        string_view Intern(const string &str);

        size_t StoredStringCount() const;

    private:
        set<string> pool;
    };
}

#endif //JIMP_EXERCISES_TEXTPOOL_H
