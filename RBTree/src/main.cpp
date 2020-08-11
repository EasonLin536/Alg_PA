#include <iostream>
#include "RBTree.h"

using namespace std;

int main() {
    RBTree rbt;

    for (int i=1;i<100;i++) {
        rbt.RBInsert(i);
    }

    rbt.print(INORDER);

    for (int i=2;i<100;i+=2) {
        rbt.RBDelete(i);
    }
    
    rbt.print(INORDER);
}