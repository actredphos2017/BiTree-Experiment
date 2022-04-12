#include <iostream>
#include <string>
#include <vector>
#include "head/tree.h"

#if 0

int main(){
    BiTreeNode* root = new BiTreeNode();
    string str;
    cin >> str;
    root->CreateTree(str.data());
    root->PreOrderTraverse();
    cout << endl;
    root->InOrderTraverse();
    cout << endl;
    root->PostOrderTraverse();
    cout << endl;
    root->LevelOrderTraverse();
    cout << endl;
    cout << root->ifLeaf() << endl;
    cout << root->Depth() << endl;
    cout << root->LeafCount() << endl;
    return 0;
}

#elif 1

int main(){
    BiTreeNode* root = new BiTreeNode();
    string str;
    cin >> str;
    root->CreateTree(str.data());
    root->LevelOrderTraverse();
    OrderTree ot(root);
    ot.output();
    root->DestoryTree();
    root = ot.ToBiTree();
    cout << "PreOrderTraverse: ";
    root->PreOrderTraverse();
    cout << endl;
    cout << "InOrderTraverse: ";
    root->InOrderTraverse();
    cout << endl;
    cout << "PostOrderTraverse: ";
    root->PostOrderTraverse();
    cout << endl;
    root->DispTree();
    system("pause");
    return 0;
}

#else

int main(){
    ExpressionTreeNode* root = new ExpressionTreeNode();
    string str;
    cin >> str;
    root->BuildExpressionTree(str.data());
    root->ExpressionTreeTraverse();
    cout << endl;
    cout << root->CalcExpressionTree() << endl;
    system("pause");
    return 0;
}

#endif
/*
A(B(C,D),E(F,G))
A BE CDFG

0       0
00      1
01      2
000     3
001     4
010     5
011     6
0000    7
0001    8
0010    9
0011    10
0100    11
0101    12
0110    13
0111    14

PreOrderTraverse: A B C D E F G
0
00
000
001
01
010
011

InOrderTraverse: C B D A F E G
000
00
001
0
010
01
011

PostOrderTraverse: C D B F G E A
000
001
00
010
011
01
0
*/