#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, const T& e) const {
        if (n == nullptr)
            throw std::runtime_error("Element not found!");
        if (e < n->elem)
            return search(n->left, e);
        if (e > n->elem)
            return search(n->right, e);
        return n;
    }

    BSNode<T>* insert(BSNode<T>* n, const T& e) {
        if (n == nullptr) {
            ++nelem;
            return new BSNode<T>(e);
        }
        if (e == n->elem)
            throw std::runtime_error("Duplicated element!");
        if (e < n->elem)
            n->left = insert(n->left, e);
        else
            n->right = insert(n->right, e);
        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    T max(BSNode<T>* n) const {
        if (n == nullptr)
            throw std::runtime_error("Element not found!");
        while (n->right != nullptr)
            n = n->right;
        return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* left = n->left;
            delete n;
            return left;
        }
        n->right = remove_max(n->right);
        return n;
    }

    BSNode<T>* remove(BSNode<T>* n, const T& e) {
        if (n == nullptr)
            throw std::runtime_error("Element not found!");

        if (e < n->elem)
            n->left = remove(n->left, e);
        else if (e > n->elem)
            n->right = remove(n->right, e);
        else {
            --nelem;
            if (n->left != nullptr && n->right != nullptr) {
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            } else {
                BSNode<T>* child =
                    (n->left != nullptr) ? n->left : n->right;
                delete n;
                return child;
            }
        }
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    BSTree() : nelem(0), root(nullptr) {}

    ~BSTree() {
        delete_cascade(root);
    }

    int size() const {
        return nelem;
    }

    T search(const T& e) const {
        return search(root, e)->elem;
    }

    T operator[](const T& e) const {
        return search(e);
    }

    void insert(const T& e) {
        root = insert(root, e);
    }

    void remove(const T& e) {
        root = remove(root, e);
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& tree) {
        tree.print_inorder(out, tree.root);
        return out;
    }
};

#endif
