#include <iostream>
#include <string>
#include <vector>
#include "head/tree.h"

using namespace std;

#if 0
//示范代码 二叉树基础
//A(B(C),D(,E))
int main(){
    BiTreeNode* root = new BiTreeNode(); //创建一个根节点
    string str;
    cin >> str;
    root->CreateTree(str.data());
    cout << "PreOrderTraverse:      ";
    root->PreOrderTraverse();
    cout << endl;
    cout << "InOrderTraverse:       ";
    root->InOrderTraverse();
    cout << endl;
    cout << "PostOrderTraverse:     ";
    root->PostOrderTraverse();
    cout << endl;
    cout << "LevelOrderTraverse:    ";
    root->LevelOrderTraverse();
    cout << endl;
    cout << "Tree's Depth:          ";
    cout << root->Depth() << endl;
    cout << "Leaf's Count:          ";
    cout << root->LeafCount() << endl;
    return 0;
}

#elif 0

//示范代码2 链式与顺序的互相转换
//A(B(C),D(,E))
int main(){
    BiTreeNode* root = new BiTreeNode();
    string str;
    cin >> str;
    root->CreateTree(str.data());
    cout << "Old List's DispTree:   ";
    root->DispTree();
    cout << endl;
    OrderTree ot(root);
    root->DestoryTree();
    cout << "Data in Array:         ";
    ot.output();
    root = ot.ToBiTree();
    cout << "New List's DispTree:   ";
    root->DispTree();
    cout << endl;
    system("pause");
    return 0;
}

#elif 0

//顺序二叉树遍历
//A(B(C),D(,E))
int main(){
    BiTreeNode* root = new BiTreeNode();
    string str;
    cin >> str;
    root->CreateTree(str.data());
    OrderTree ot(root);
    cout << "OtOutPut:          ";
    ot.output();
    cout << "PreOrderTraverse:  ";
    ot.PreOrder();
    cout << endl;
    cout << "InOrderTraverse:   ";
    ot.InOrder();
    cout << endl;
    cout << "PostOrderTraverse: ";
    ot.PostOrder();
    cout << endl;
    system("pause");
    return 0;
}
#else

//前缀表达式的创建、输出、计算
//10+5*(6-2)/2
int main(){
    ExpressionTreeNode* root = new ExpressionTreeNode();
    string str;
    cin >> str;
    root->BuildExpressionTree(str.data());
    cout << "ExpressionTreeTraverse:    ";
    root->ExpressionTreeTraverse();
    cout << endl;
    cout << "Result of the Formula:     ";
    cout << root->CalcExpressionTree() << endl;
    system("pause");
    return 0;
}

#endif