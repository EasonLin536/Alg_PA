#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
using namespace std;

class RBTree;

enum NodeColor {
    RED, BLACK
};

enum Traverse {
    INORDER, PREORDER, POSTORDER
};

class Node {
    friend class RBTree;

    Node(const int k, NodeColor c = RED, Node* p = 0, Node* l = 0, Node* r = 0):
    _key(k), _color(c), _p(p), _left(l), _right(r) {}

    int       _key;   // node's value
    NodeColor _color; // node's color
    Node*     _p;     // node's parent node
    Node*     _left;  // node's left child
    Node*     _right; // node's right child
};

class RBTree {

public:
    RBTree() { _root = _nil; }
    ~RBTree() { delete _nil; }

    // method for insert
    void RBInsert(const int&);

    // method for find
    bool exist(const int&);
    Node* find(const int&);

    // method for delete
    bool RBDelete(const int&);
    
    // method for print
    void printNode(Node*);
    void print(Traverse);

protected:
    // method for fixup
    void leftRotate(Node*);
    void rightRotate(Node*);

    // method for insert
    Node* treeInsert(const int&);
    void RBInsertFixup(Node*);

    // method for delete
    void RBTransplant(Node*, Node*);
    Node* treeMinimum(Node*);
    void RBDeleteFixup(Node*);

    // method for print
    void printInOrder(Node*);
    void printPreOrder(Node*);
    void printPostOrder(Node*);

private:
    Node* _root; // parent is _nil
    Node* _nil = new Node(0, BLACK, NULL, NULL, NULL);

};

#endif