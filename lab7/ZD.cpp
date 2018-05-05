//
// Created by mwypych on 23/04/18.
//

#include "ZD.h"

using std::move;
using std::pair;
using std::make_unique;
using std::unique_ptr;

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
bool ZipperIterator::NotEquals(const IterableIterator &other) const {
  const ZipperIterator *s = dynamic_cast<const ZipperIterator *>(&other);
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
  return this->iterator->NotEquals(*other.iterator);
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
