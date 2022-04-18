#include <iostream>
#include <string>
#include <vector>
#include "head/tree.h"

using namespace std;

void ElemOut(ElemType e){
    cout << e;
}

#if 1

//示范代码1 二叉树基础
//A(B(C),D(,E))
int main(){
    BiTreeNode* root = new BiTreeNode(); //创建一个根节点
    string str;
    cin >> str;
    root->CreateTree(str.data());
    cout << "PreOrderTraverse:      ";
    root->PreOrderTraverse(ElemOut);
    cout << endl;
    cout << "InOrderTraverse:       ";
    root->InOrderTraverse(ElemOut);
    cout << endl;
    cout << "PostOrderTraverse:     ";
    root->PostOrderTraverse(ElemOut);
    cout << endl;
    cout << "LevelOrderTraverse:    ";
    root->LevelOrderTraverse(ElemOut);
    cout << endl;
    cout << "Tree's Depth:          ";
    cout << root->Depth() << endl;
    cout << "Leaf's Count:          ";
    cout << root->LeafCount() << endl;
    return 0;
}

#elif 1

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

#elif 1

//示范代码3 顺序二叉树遍历
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
    ot.PreOrder(ElemOut);
    cout << endl;
    cout << "InOrderTraverse:   ";
    ot.InOrder(ElemOut);
    cout << endl;
    cout << "PostOrderTraverse: ";
    ot.PostOrder(ElemOut);
    cout << endl;
    system("pause");
    return 0;
}
#else

//示范代码4 前缀表达式的创建、输出、计算
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