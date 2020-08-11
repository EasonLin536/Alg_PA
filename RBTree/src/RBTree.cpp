#include "RBTree.h"
using namespace std;

void
RBTree::leftRotate(Node* x) {
    // cerr << "Left-rotating at node(" << x->_key << ")" << endl;
    Node* y = x->_right;
    x->_right = y->_left;
    
    if (y->_left != _nil) { y->_left->_p = x; }
    y->_p = x->_p;

    if (x->_p == _nil) { _root = y; }
    else if (x == x->_p->_left) { x->_p->_left = y; }
    else { x->_p->_right = y; }

    y->_left = x;
    x->_p = y;
}

void
RBTree::rightRotate(Node* y) {
    // cerr << "Right-rotating at node(" << y->_key << ")" << endl;
    Node* x = y->_left;
    y->_left = x->_right;

    if (x->_right != _nil) { x->_right->_p = y; }
    x->_p = y->_p;
    
    if (y->_p == _nil) { _root = x; }
    else if (y == y->_p->_left) { y->_p->_left = x; }
    else { y->_p->_right = x; }

    x->_right = y;
    y->_p = x;
}

Node*
RBTree::treeInsert(const int& k) {
    // cerr << "Tree-insert node(" << k << ")" << endl;
    Node* z = new Node(k, RED, _nil, _nil, _nil);
    Node* y = _nil;
    Node* x = _root;

    while (x != _nil) {
        y = x;
        if (z->_key < x->_key) { x = x->_left; }
        else { x = x->_right; }
    }

    z->_p = y;
    if (y == _nil) { _root = z; }
    else if (z->_key < y->_key) { y->_left = z; }
    else { y->_right = z; }

    return z;
}

void
RBTree::RBInsert(const int& k) {
    // cerr << "Insert node(" << k << ")" << endl;
    Node* z = treeInsert(k);
    RBInsertFixup(z);
}

void
RBTree::RBInsertFixup(Node* z) {
    while (z->_p->_color == RED) {
        if (z->_p == z->_p->_p->_left) {
            Node * uncle = z->_p->_p->_right;
            // case 1: uncle is RED
            if (uncle->_color == RED) {
                z->_p->_color = BLACK;
                uncle->_color = BLACK;
                z->_p->_p->_color = RED;
                z = z->_p->_p;
            }
            else {
                // case 2
                if (z == z->_p->_right) {
                    z = z->_p;
                    leftRotate(z);
                }
                // case 3
                z->_p->_color = BLACK;
                z->_p->_p->_color = RED;
                rightRotate(z->_p->_p);
            }
        }
        // identical to upper if statement
        else {
            Node * uncle = z->_p->_p->_left;
            // case 1: uncle is RED
            if (uncle->_color == RED) {
                z->_p->_color = BLACK;
                uncle->_color = BLACK;
                z->_p->_p->_color = RED;
                z = z->_p->_p;
            }
            else {
                // case 2
                if (z == z->_p->_left) {
                    z = z->_p;
                    rightRotate(z);
                }
                // case 3
                z->_p->_color = BLACK;
                z->_p->_p->_color = RED;
                leftRotate(z->_p->_p);
            }
        }
    }
    _root->_color = BLACK;
}

Node*
RBTree::find(const int& k) {
    Node* n = _root;
    while (n != _nil) {
        if (n->_key < k) { n = n->_right; }
        else if (n->_key > k) { n = n->_left; }
        else { break; }
    }

    return n;
}

bool
RBTree::exist(const int& k) {
    Node* n = find(k);
    if (n != _nil) { return true; }
    else { return false; }
}

void
RBTree::RBTransplant(Node* u, Node* v) {
    if (u->_p == _nil) { _root = v; }
    else if (u == u->_p->_left) { u->_p->_left = v; }
    else { u->_p->_right = v; }

    v->_p = u->_p;
}

Node*
RBTree::treeMinimum(Node* subRoot) {
    Node* n = subRoot;
    while (n->_left != _nil) {
        n = n->_left;
    }

    return n;
}

bool
RBTree::RBDelete(const int& k) {
    cout << "Delete node " << k << endl;
    Node* z = find(k);
    if (z == _nil) {
        cout << "node not found" << endl;
        return false;
    }

    Node* x = NULL;
    Node* y = z;
    NodeColor y_original_color = y->_color;

    // case 1 & 2: 0 or 1 child
    if (z->_left == _nil) {
        x = z->_right;
        RBTransplant(z, z->_right);
    }

    else if (z->_right == _nil) {
        x = z->_left;
        RBTransplant(z, z->_left);
    }

    // case 3: 2 children
    else {
        y = treeMinimum(z->_right);
        y_original_color = y->_color;
        x = y->_right;

        if (y->_p == z) { x->_p= y; }
        else {
            RBTransplant(y, y->_right);
            y->_right = z->_right;
            y->_right->_p = y;
        }

        RBTransplant(z, y);
        y->_left = z->_left;
        y->_left->_p = y;
        y->_color = z->_color;
    }

    if (y_original_color == BLACK) { RBDeleteFixup(x); }

    delete z;

    return true;
}

void
RBTree::RBDeleteFixup(Node* x) {
    Node* sibling = NULL;
    while (x != _root && x->_color == BLACK) {
        if (x == x->_p->_left) {
            sibling = x->_p->_right;
            
            if (sibling->_color == RED) {
                sibling->_color = BLACK;
                x->_p->_color = RED;
                leftRotate(x->_p);
                sibling = x->_p->_right;
            }
            
            if (sibling->_left->_color == BLACK && sibling->_right->_color == BLACK) {
                sibling->_color = RED;
                x = x->_p;
            }
            
            else {
                if (sibling->_right->_color == BLACK) {
                    sibling->_left->_color = BLACK;
                    sibling->_color = RED;
                    rightRotate(sibling);
                    sibling = x->_p->_right;
                }

                sibling->_color = x->_p->_color;
                x->_p->_color = BLACK;
                sibling->_right->_color = BLACK;
                leftRotate(x->_p);
                x = _root;
            }
        }

        else {
            sibling = x->_p->_left;
            
            if (sibling->_color == RED) {
                sibling->_color = BLACK;
                x->_p->_color = RED;
                rightRotate(x->_p);
                sibling = x->_p->_left;
            }
            
            if (sibling->_right->_color == BLACK && sibling->_left->_color == BLACK) {
                sibling->_color = RED;
                x = x->_p;
            }
            
            else {
                if (sibling->_left->_color == BLACK) {
                    sibling->_right->_color = BLACK;
                    sibling->_color = RED;
                    leftRotate(sibling);
                    sibling = x->_p->_left;
                }

                sibling->_color = x->_p->_color;
                x->_p->_color = BLACK;
                sibling->_left->_color = BLACK;
                rightRotate(x->_p);
                x = _root;
            }
        }
    }

    x->_color = BLACK;
}

void
RBTree::printNode(Node* n) {
    if (n == _nil) {
        cout << "nil" << endl;
        return;
    }
    cout << "node: k(" << n->_key << ") c(";
    if (n->_color == RED) { cout << "R) "; }
    else { cout << "B) "; }

    cout << "p(";
    if (n->_p == _nil) { cout << "nil) "; }
    else { cout << n->_p->_key << ") "; }

    cout << "l(";
    if (n->_left == _nil) { cout << "nil) "; }
    else { cout << n->_left->_key << ") "; }

    cout << "r(";
    if (n->_right == _nil) { cout << "nil)" << endl; }
    else { cout << n->_right->_key << ")" << endl; }
}

void
RBTree::printInOrder(Node* curr_node) {
    if (curr_node == _nil) { return; }

    if (curr_node->_left) { printInOrder(curr_node->_left); }
    printNode(curr_node);
    if (curr_node->_right) { printInOrder(curr_node->_right); }
}

void
RBTree::printPreOrder(Node* curr_node) {
    if (curr_node == _nil) { return; }

    printNode(curr_node);
    if (curr_node->_left) { printPreOrder(curr_node->_left); }
    if (curr_node->_right) { printPreOrder(curr_node->_right); }
}

void
RBTree::printPostOrder(Node* curr_node) {
    if (curr_node == _nil) { return; }

    if (curr_node->_left) { printPostOrder(curr_node->_left); }
    if (curr_node->_right) { printPostOrder(curr_node->_right); }
    printNode(curr_node);
}

void
RBTree::print(Traverse t) {
    if (t == INORDER) { printInOrder(_root); }
    else if (t == PREORDER) { printPreOrder(_root); }
    else { printPostOrder(_root); }
}