

#include "Counts.h"

namespace datastructures {
    Counts::Counts() {
        counter_ = 1;
    }

    Counts::Counts(int number) {
        counter_ = number;
    }

    int Counts::GetCounts() const {
        return counter_;
    }

    Counts::operator int() const {
        return counter_;
    }

    bool Counts::operator<(const Counts &other) {
        return GetCounts() < other.GetCounts();
    }

    bool Counts::operator==(const Counts &other) {
        return GetCounts() == other.GetCounts();
    }

    bool Counts::operator>(const Counts &other) {
        return GetCounts() > other.GetCounts();
    }

    Counts &Counts::operator++() {
        counter_++;
        return *this;
    }

    Counts Counts::operator++(int foo) {
        Counts tmp(counter_);
        ++counter_;
        return tmp;
    }
}