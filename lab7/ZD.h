//
// Created by mwypych on 23/04/18.
//

#ifndef JIMP_EXERCISES_ZD_H
#define JIMP_EXERCISES_ZD_H
#include <string>
#include <vector>
#include<memory>
class IterableIterator {
 public:
  virtual std::pair<int, std::string> Dereference() const = 0;
  virtual IterableIterator &Next() = 0;
  virtual bool NotEquals(const IterableIterator &other) const = 0;

  virtual ~IterableIterator() = default;

};

class ZipperIterator : public IterableIterator {
 public:
  std::pair<int, std::string> Dereference() const override;
  IterableIterator &Next() override;
  bool NotEquals(const IterableIterator &other) const override;
  explicit ZipperIterator(std::vector<int>::const_iterator left,
                          std::vector<std::string>::const_iterator right,
                          std::vector<int>::const_iterator left_end,
                          std::vector<std::string>::const_iterator right_end);
 private:
  std::vector<int>::const_iterator current_left;
  std::vector<std::string>::const_iterator current_right;
  std::vector<int>::const_iterator left_end;
  std::vector<std::string>::const_iterator right_end;
  int getLeftValue() const;
  std::string getRightValue() const;
};

class IterableIteratorWrapper{
 public:
  IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator);
  bool operator!=(const IterableIteratorWrapper &other) const;
  std::pair<int, std::string> operator*()const;
  IterableIteratorWrapper &operator++();
 private:
  std::unique_ptr<IterableIterator> iterator;
};
class Iterable{
 protected:
  virtual std::unique_ptr<IterableIterator> ConstBegin() const =0;
  virtual std::unique_ptr<IterableIterator> ConstEnd() const =0;
 public:
  IterableIteratorWrapper cbegin() const;
  IterableIteratorWrapper cend() const;
  IterableIteratorWrapper begin() const;
  IterableIteratorWrapper end() const;
};
class Zipper : public Iterable {
 protected:
  std::unique_ptr<IterableIterator> ConstBegin() const override;
  std::unique_ptr<IterableIterator> ConstEnd() const override;
 public:
  Zipper(const std::vector<int>&,const std::vector<std::string>&);
 private:
  ZipperIterator prototype_begin;
  ZipperIterator prototype_end;
};

#endif //JIMP_EXERCISES_ZD_H
