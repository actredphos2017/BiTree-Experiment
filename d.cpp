#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

const int MaxSize = 500;

typedef char ElementType;

typedef struct TreeNode {
    ElementType data;
    struct TreeNode *left, *right;
} BTNode;

//根据嵌套括号表示法的字符串生成链式存储的二叉树
void CreateTree(BTNode* &b, char str[]);

//以嵌套括号表示法输出一棵树
void DispTree(BTNode* b);

int main() {
    char str[MaxSize];
    string ss;

    getline(cin, ss);
    strcpy(str, ss.c_str());

    BTNode* root = NULL;

    CreateTree(root, str);

    DispTree(root);
    cout << endl;

    system("pause");
    return 0;
}

/* 请在这里填写答案 */

#include <vector>
void CreateTree(BTNode* &b, char str[]){
    if(strlen(str) == 0){
        b = NULL;
        return;
    }
    b = (BTNode*)malloc(sizeof(BTNode));
    b->data = str[0];
    if(str[1] == '('){
        vector<char> vec;
        int j = 0;
        for(int i = 2; str[i] != ')' || j > 0; i++){
            if(str[i] == '(')
                j++;
            if(str[i] == ')')
                j--;
            vec.push_back(str[i]);
        }
        vec.push_back('\0');
        if(vec.data()[0] == ','){
            b->left = NULL;
            CreateTree(b->right, vec.data() + 1);
        }
        else{
            vector<char> vec1;
            int j = 0;
            int i;
            bool flag = true;
            for(i = 0; (vec.data()[i] != ',' || j != 0) && flag; i++){
                vec1.push_back(vec.data()[i]);
                switch(vec.data()[i]){
                    case '(':
                        j ++;
                        break;
                    case ')':
                        j --;
                        break;
                    case '\0':
                        flag = false;
                        break;
                }
            }
            vec1.push_back('\0');
            if(flag){
                CreateTree(b->left, vec1.data());
                CreateTree(b->right, vec.data() + i + 1);
            }
            else{
                b->right = NULL;
                CreateTree(b->left, vec1.data());
            }
        }
    }
    else{
        b->left = NULL;
        b->right = NULL;
    }
}


void DispTree(BTNode* b){
    if(b==NULL)
        return;
    if(b->left == NULL && b->right == NULL){
        cout<<b->data;
        return;
    }
    else if(b->left == NULL){
        cout<<b->data<<"(,";
        DispTree(b->right);
        cout<<")";
    }
    else if(b->right == NULL){
        cout<<b->data<<"(";
        DispTree(b->left);
        cout<<")";
    }
    else{
        cout<<b->data<<"(";
        DispTree(b->left);
        cout<<",";
        DispTree(b->right);
        cout<<")";
    }
}