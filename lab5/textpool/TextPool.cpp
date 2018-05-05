

#include "TextPool.h"

using namespace pool;

TextPool::TextPool() {
}

TextPool::TextPool(const initializer_list<string> &Ptr) {
    for(auto &i : Ptr)
        this->pool.insert(i);
}

TextPool::TextPool(TextPool &&Ptr) {
    std::swap(this->pool, Ptr.pool);
}

TextPool::~TextPool() {}

TextPool& TextPool::operator=(TextPool &&Ptr) {
    if(this == &Ptr)
    {
        return *this;
    }
    this->pool.clear();
    std::swap(this->pool,Ptr.pool);
    return *this;
}

//#############################################################################################

size_t TextPool::StoredStringCount() const {
    return this->pool.size();
}

string_view TextPool::Intern(const string &str) {
    bool already_in = false;

    for(auto i = pool.begin(); i != pool.end(); i++)
        if(*i == str) {
            already_in = true;
            return *i;
        }

    if(!already_in) {
        this->pool.insert(str);
        return str;
    }
}