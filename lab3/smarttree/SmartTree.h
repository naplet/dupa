#include <ostream>
#include <string>
#include <memory>
#include <sstream>


#ifndef JIMP_EXERCISES_SMARTTREE_H
#define JIMP_EXERCISES_SMARTTREE_H


namespace datastructures {
    using ::std::unique_ptr;
    using ::std::ostream;
    using ::std::string;
    using ::std::make_unique;

    struct SmartTree {


        int value;
        unique_ptr <SmartTree> left;
        unique_ptr <SmartTree> right;
    };

    unique_ptr <SmartTree> CreateLeaf(int value);
    unique_ptr <SmartTree> InsertLeftChild(unique_ptr<SmartTree> tree, unique_ptr<SmartTree> left_subtree);
    unique_ptr <SmartTree> InsertRightChild(unique_ptr<SmartTree> tree, unique_ptr<SmartTree> right_subtree);
    void PrintTreeInOrder(const unique_ptr<SmartTree> &unique_ptr, ostream *out);
    string DumpTree(const unique_ptr<SmartTree> &tree);
    unique_ptr <SmartTree> RestoreTree(const string &tree);
}


#endif //JIMP_EXERCISES_SMARTTREE_H