#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>

typedef char    ElemType;
typedef char    ExpressionType;
typedef int     DigitalType;

//链式二叉树
class BiTreeNode{
    friend class OrderTree;
    private:
        ElemType data;
        BiTreeNode* left;
        BiTreeNode* right;
    public:
        BiTreeNode(const ElemType _data = '\0'){ //默认构造函数
            this->data = _data;
            this->left = this->right = NULL;
        }
        void DestoryTree(){ //销毁二叉树
            if(this->left)
                this->left->DestoryTree();
            if(this->right)
                this->right->DestoryTree();
            delete this;
        }
        void CreateTree(const char str[]){ //创建二叉树
            if(strlen(str) == 0)
                return;
            this->data = str[0];
            if(str[1] == '('){
                std::vector<ElemType> vec;
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
                    this->left = NULL;
                    this->right = new BiTreeNode();
                    this->right->CreateTree(vec.data() + 1);
                }
                else{
                    std::vector<ElemType> _vec;
                    int i, j = 0;
                    bool ifSingle = true;
                    for(i = 0; (vec.data()[i] != ',' || j != 0) && ifSingle; i++){
                        _vec.push_back(vec.data()[i]);
                        if(vec.data()[i] == '(')
                            j ++;
                        else if(vec.data()[i] == ')')
                            j --;
                        else if(vec.data()[i] == '\0')
                            ifSingle = false;
                    }
                    _vec.push_back('\0');
                    if(ifSingle){
                        this->left = new BiTreeNode();
                        this->left->CreateTree(_vec.data());
                        if(vec.data()[i+1] != '\0'){
                            this->right = new BiTreeNode();
                            this->right->CreateTree(vec.data() + i + 1);
                        }else
                            this->right = NULL;
                    }else{
                        this->right = NULL;
                        this->left = new BiTreeNode();
                        this->left->CreateTree(_vec.data());
                    }
                }
            }
            else{
                this->left = NULL;
                this->right = NULL;
            }
        }
        void DispTree(){ //打印二叉树
            if(this){
                if(this->left == NULL && this->right == NULL){
                    std::cout<<this->data;
                    return;
                }
                else if(this->right == NULL){
                    std::cout<<this->data<<"(";
                    this->left->DispTree();
                    std::cout<<")";
                }
                else{
                    std::cout<<this->data<<"(";
                    this->left->DispTree();
                    std::cout<<",";
                    this->right->DispTree();
                    std::cout<<")";
                }
            }
            
        }
        void PreOrderTraverse(void (*Visit)(const ElemType e)){ //前序遍历
            Visit(this->data);
            if(this->left != NULL)
                this->left->PreOrderTraverse(Visit);
            if(this->right != NULL)
                this->right->PreOrderTraverse(Visit);
        }
        void InOrderTraverse(void (*Visit)(const ElemType e)){ //中序遍历
            if(this->left != NULL)
                this->left->InOrderTraverse(Visit);
            Visit(this->data);
            if(this->right != NULL)
                this->right->InOrderTraverse(Visit);
        }
        void PostOrderTraverse(void (*Visit)(const ElemType e)){ //后序遍历
            if(this->left != NULL)
                this->left->PostOrderTraverse(Visit);
            if(this->right != NULL)
                this->right->PostOrderTraverse(Visit);
            Visit(this->data);
        }
        void LevelOrderTraverse(void (*Visit)(ElemType e)){ //层序遍历
            std::list<BiTreeNode*> l = {this};
            while(!l.empty()){
                Visit(l.front()->data);
                if(l.front()->left != NULL)
                    l.push_back(l.front()->left);
                if(l.front()->right != NULL)
                    l.push_back(l.front()->right);
                l.pop_front();
            }
        }
        int Depth(){ //求深度
            int ldepth = this->left == NULL ? 0 : this->left->Depth();
            int rdepth = this->right == NULL ? 0 : this->right->Depth();
            return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
        }
        int LeafCount(){ //求叶子节点数
            int lcount = this->left == NULL ? 0 : this->left->LeafCount();
            int rcount = this->right == NULL ? 0 : this->right->LeafCount();
            return (this->left == NULL && this->right == NULL) ? 1 : lcount + rcount;
        }
        void BuildBiTree(BiTreeNode*& bnode, ElemType* data, int size, int loc = 1){
            if(loc > size)
                return;
            if(data[loc] == 0)
                return;
            bnode = new BiTreeNode(data[loc]);
            BuildBiTree(bnode->left, data, size, loc*2);
            BuildBiTree(bnode->right, data, size, loc*2 + 1);
        }
};

class OrderTree{
    private:
        std::vector<ElemType> data;
        int Pow(int base, int index){
            int r = 1;
            while(index --)
                r *= base;
            return r;
        }
    public:
        OrderTree(BiTreeNode* root){
            data.resize(Pow(2,root->Depth()));
            for(int i = 0; i < data.size(); i++)
                data[i] = 0;
            BuildOrderTree(root);
        }
        void BuildOrderTree(BiTreeNode* root, int loc = 1){
            if(root == NULL)
                return;
            this->data[loc] = root->data;
            BuildOrderTree(root->left, loc*2);
            BuildOrderTree(root->right, loc*2 + 1);
        }
        void OutPut(){
            for(int i = 1; i < this->data.size(); i ++)
                if(data[i] == 0)
                    std::cout << '#';
                else
                    std::cout << this->data[i];
            std::cout << std::endl;
        }
        void LevelOrderTraverse(void (*Visit)(ElemType e)){
            for(int i = 1; i < this->data.size(); i ++)
                if(this->data[i] != 0)
                    Visit(this->data[i]);
        }
        BiTreeNode* ToBiTree(){ //转换为二叉树
            if(this->data.size() == 0)
                return NULL;
            BiTreeNode* result = NULL;
            result->BuildBiTree(result, this->data.data(), this->data.size());
            return result;
        }
        void PreOrderTraverse(void (*Visit)(ElemType e), int loc = 1){
            if(this->data.size() == 0 || loc >= this->data.size())
                return;
            if(this->data[loc] == 0)
                return;
            Visit(this->data[loc]);
            this->PreOrderTraverse(Visit, loc*2);
            this->PreOrderTraverse(Visit, loc*2+1);
        }
        void InOrderTraverse(void (*Visit)(ElemType e), int loc = 1){
            if(this->data.size() == 0 || loc >= this->data.size())
                return;
            if(this->data[loc] == 0)
                return;
            this->InOrderTraverse(Visit, loc*2);
            Visit(this->data[loc]);
            this->InOrderTraverse(Visit, loc*2+1);
        }
        void PostOrderTraverse(void (*Visit)(ElemType e), int loc = 1){
            if(this->data.size() == 0 || loc >= this->data.size())
                return;
            if(this->data[loc] == 0)
                return;
            this->PostOrderTraverse(Visit, loc*2);
            this->PostOrderTraverse(Visit, loc*2+1);
            Visit(this->data[loc]);
        }
};

//中缀表达式树
class ExpressionTreeNode{
    private:
        bool isOperator;
        union{
            ExpressionType exp;
            DigitalType num;
        };
        ExpressionTreeNode* left;
        ExpressionTreeNode* right;
        std::string Operator = "+-*/";
    public:
        ExpressionTreeNode(const char _str[] = NULL){
            if(_str == NULL)
                return;
            this->BuildExpressionTree(_str);
        }
        void BuildExpressionTree(const char _str[]){ //构造表达式树
            char str[strlen(_str)+1];
            strcpy(str, _str);
            if(str[0] == '\0')
                return;
            std::vector<char> formula;
            int j = 0;
            for(int in = 0; in < 4; in ++){
                for(int i = 0; i < strlen(str); i ++){
                    formula.push_back(str[i]);
                    if(str[i] == '(')
                        j ++;
                    else if(str[i] == ')')
                        j --;
                    else if(str[i] == Operator[in] && j == 0){
                        formula[i] = '\0';
                        this->isOperator = true;
                        this->exp = str[i];
                        this->left = new ExpressionTreeNode(formula.data());
                        this->right = new ExpressionTreeNode(str + i + 1);
                        return;
                    }
                }
                if(j != 0){
                    std::cout << "ERROR!" << std::endl;
                    return;
                }
            }
            if(str[0] == '('){
                str[strlen(str)-1] = '\0';
                this->BuildExpressionTree(str + 1);
            }
            else{
                this->isOperator = false;
                this->num = atoi(str);
                this->left = NULL;
                this->right = NULL;
            }
        }
        void ExpressionTreeTraverse(){ //遍历输出表达式树
            if(this->isOperator){
                if(this->exp != '*' && this->exp != '/' && !(this->left->isOperator || this->right->isOperator))
                    std::cout << "(";
                this->left->ExpressionTreeTraverse();
                std::cout << this->exp;
                this->right->ExpressionTreeTraverse();
                if(this->exp != '*' && this->exp != '/' && !(this->left->isOperator || this->right->isOperator))
                    std::cout << ")";
            }
            else
                std::cout << this->num;
        }

        int CalcExpressionTree(){ //计算表达式树
            if(this->isOperator){
                if(this->exp == '+')
                    return this->left->CalcExpressionTree() + this->right->CalcExpressionTree();
                else if(this->exp == '-')
                    return this->left->CalcExpressionTree() - this->right->CalcExpressionTree();
                else if(this->exp == '*')
                    return this->left->CalcExpressionTree() * this->right->CalcExpressionTree();
                else if(this->exp == '/')
                    return this->left->CalcExpressionTree() / this->right->CalcExpressionTree();
            }
            return this->num;
        }
};