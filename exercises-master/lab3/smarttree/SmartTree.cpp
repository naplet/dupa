#include "SmartTree.h"
using namespace datastructures;

unique_ptr <SmartTree> datastructures::CreateLeaf(int value) {
    unique_ptr <SmartTree> leaf = make_unique<SmartTree>();
    leaf->value = value;
    leaf->left = nullptr;
    leaf->right = nullptr;

    return leaf;
}

unique_ptr <SmartTree> datastructures::InsertLeftChild(unique_ptr<SmartTree> tree,
                                                       unique_ptr<SmartTree> left_subtree) {
    tree->left = std::move(left_subtree);

    return tree;
}

unique_ptr <SmartTree> datastructures::InsertRightChild(unique_ptr<SmartTree> tree,
                                                        unique_ptr<SmartTree> right_subtree) {
    tree->right = std::move(right_subtree);

    return tree;
}

void datastructures::PrintTreeInOrder(const unique_ptr<SmartTree> &unique_ptr, ostream *out) {

    if(unique_ptr == nullptr)
        return;
    PrintTreeInOrder(unique_ptr->left, out);
    *out << unique_ptr->value << ", ";
    PrintTreeInOrder(unique_ptr->right, out);
}

string datastructures::DumpTree(const unique_ptr<SmartTree> &tree) {
    if (!tree)
        return "[none]";
    else {
        string value = "";
        value += std::to_string(tree->value);
        return "[" + value + " " + DumpTree(tree->left) + " " + DumpTree(tree->right) + "]";
    }

}