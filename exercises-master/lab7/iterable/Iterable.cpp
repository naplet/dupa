//
// Created by Noxianin on 2018-04-24.
//

#include "Iterable.h"
using std::move;
using std::pair;
using std::make_unique;
using std::unique_ptr;
using namespace utility;

std::pair<int, std::string> ZipperIterator::Dereference() const {
    int left_value = getLeftValue();
    std::string right_value = getRightValue();
    return std::make_pair(left_value, right_value);
}
std::string ZipperIterator::getRightValue() const {
    std::string right_value;
    if (current_right != right_end) {
        right_value = *current_right;
    } else {
        right_value = *(current_right - 1);
    }
    return right_value;
}
int ZipperIterator::getLeftValue() const {
    int left_value;
    if (current_left != left_end) {
        left_value = *current_left;
    } else {
        left_value = *(current_left - 1);
    }
    return left_value;
}
IterableIterator &ZipperIterator::Next() {
    if (current_left != left_end) {
        ++current_left;
    }
    if (current_right != right_end) {
        ++current_right;
    }
    return *this;
}
bool ZipperIterator::NotEquals(const std::unique_ptr<utility::IterableIterator>&other) const {
    const ZipperIterator *s = dynamic_cast<const ZipperIterator *>(other.get());
    return !(current_left == s->current_left
             && current_right == s->current_right
             && left_end == s->left_end
             && right_end == s->right_end);

}
ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left,
                               std::vector<std::string>::const_iterator right,
                               std::vector<int>::const_iterator left_end,
                               std::vector<std::string>::const_iterator right_end) {
    this->current_left = left;
    this->left_end = left_end;
    this->current_right = right;
    this->right_end = right_end;
}
IterableIteratorWrapper::IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator) {
    this->iterator = move(iterator);
}
bool IterableIteratorWrapper::operator!=(const IterableIteratorWrapper &other) const {
    return this->iterator->NotEquals(other.iterator);
}
std::pair<int, std::string> IterableIteratorWrapper::operator*() const {

    return this->iterator->Dereference();
}
IterableIteratorWrapper &IterableIteratorWrapper::operator++() {
    this->iterator->Next();
    return *this;
}
IterableIteratorWrapper Iterable::cbegin() const {
    std::unique_ptr<IterableIterator> p = ConstBegin();
    return IterableIteratorWrapper(move(p));
}
IterableIteratorWrapper Iterable::cend() const {
    std::unique_ptr<IterableIterator> p = ConstEnd();
    return IterableIteratorWrapper(move(p));
}
IterableIteratorWrapper Iterable::begin() const {
    return cbegin();
}
IterableIteratorWrapper Iterable::end() const {
    return cend();
}
std::unique_ptr<IterableIterator> Zipper::ConstBegin() const {
    unique_ptr<IterableIterator> p = make_unique<ZipperIterator>(prototype_begin);
    //IterableIterator *p = new ZipperIterator(v);
    return move(p);
}
std::unique_ptr<IterableIterator> Zipper::ConstEnd() const {
    unique_ptr<IterableIterator> p = make_unique<ZipperIterator>(prototype_end);
    //IterableIterator *p = new ZipperIterator(v);
    return move(p);
}
Zipper::Zipper(const std::vector<int> &vi, const std::vector<std::string> &vs)
        : prototype_begin{vi.begin(), vs.begin(), vi.end(), vs.end()},
          prototype_end{vi.end(), vs.end(), vi.end(), vs.end()}
{
    //this->v = ZipperIterator(vi.begin(),vs.begin(),vi.end(),vs.end());
}


EnumerateIterator::EnumerateIterator(std::vector<std::string>::const_iterator begin,
                                     std::vector<std::string>::const_iterator end) {
    this->begin=begin;
    this->end = end;

}


std::pair<int, std::string> EnumerateIterator::Dereference() const {
    return std::make_pair(getIndex(),getString()) ;
}

IterableIterator &EnumerateIterator::Next() {
    if (begin != end) {
        ++begin;
        ++index;
    }

    return *this;
}

bool EnumerateIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
    const EnumerateIterator *s = dynamic_cast<const EnumerateIterator *>(other.get());
    return !(begin == s->begin
             && end == s->end);
}

int EnumerateIterator::getIndex() const {
    return index;
}

std::string EnumerateIterator::getString() const {
    return *this->begin;
}


Enumerate::Enumerate(const std::vector<std::string> & vs) : enumerate_begin{vs.begin(), vs.end()},
enumerate_end{vs.end(),vs.end()}
{
}

std::unique_ptr<IterableIterator> Enumerate::ConstBegin() const {
    unique_ptr<IterableIterator> p = make_unique<EnumerateIterator>(enumerate_begin);
    return move(p);
}

std::unique_ptr<IterableIterator> Enumerate::ConstEnd() const {
    unique_ptr<IterableIterator> p = make_unique<EnumerateIterator>(enumerate_end);
    return move(p);
}

std::pair<int, std::string> ProductIterator::Dereference() const {
    int left_value = getLeftProd();
    std::string right_value = getRightProd();
    return std::make_pair(left_value, right_value);
}

IterableIterator & ProductIterator::Next() {
    if (current_left != left_end) {
        ++current_right;
        if(current_right==right_end){
            ++current_left;
            current_right=right_start;
        }

    }
    if(current_left==left_end){
        current_right=right_end;
        current_left=left_end;
    }
    return *this;
}

bool ProductIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
    const ProductIterator *s = dynamic_cast<const ProductIterator *>(other.get());
    return !(current_left == s->current_left
             && current_right == s->current_right
             && left_end == s->left_end
             && right_end == s->right_end);
}

ProductIterator::ProductIterator(std::vector<int>::const_iterator left, std::vector<std::string>::const_iterator right,
                                 std::vector<int>::const_iterator left_end,
                                 std::vector<std::string>::const_iterator right_end) {
    this->current_left = left;
    this->left_end = left_end;
    this->current_right = right;
    this->right_end = right_end;
    this->left_start = left;
    this->right_start = right;
}

int ProductIterator::getLeftProd() const {
    int left_value;
    if (current_left != left_end) {
        left_value = *current_left;
    } else {
        left_value = *(current_left - 1);
    }
    return left_value;
}

std::string ProductIterator::getRightProd() const {
    std::string right_value;
    if (current_right != right_end) {
        right_value = *current_right;
    } else {
        right_value = *(current_right - 1);
    }
    return right_value;
}

std::unique_ptr<IterableIterator> Product::ConstBegin() const {
    unique_ptr<IterableIterator> p = make_unique<ProductIterator>(product_begin);
    return move(p);
}

std::unique_ptr<IterableIterator> Product::ConstEnd() const {
    unique_ptr<IterableIterator> p = make_unique<ProductIterator>(product_end);
    return move(p);
}

Product::Product(const std::vector<int> & vi, const std::vector<std::string> & vs): product_begin{vi.begin(), vs.begin(), vi.end(), vs.end()},
                                                                              product_end{vi.end(), vs.end(), vi.end(), vs.end()} {

}
