#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>

typedef char    ElemType;
typedef char    ExpressionType;
typedef int     DigitalType;
typedef bool    Branch;


//二叉树位置编码
class NodeLoc{
    private:
        std::vector<Branch> w;
    public:
        NodeLoc(int n = -1){
            if(n == -1)
                return;
            int i = 1, j = 1;
            while(i <= n){
                i += i + 1;
                j ++;
            }
            n -= (i-1)/2;
            std::vector<Branch> v;
            while(j --){
                v.push_back(n % 2);
                n /= 2;
            }
            for(auto in = v.rbegin(); in != v.rend(); in ++){
                this->w.push_back(*in);
            }
        }
        NodeLoc(const std::vector<Branch>& _w){
            this->w = _w;
        }
        unsigned int size(){
            return this->w.size();
        }
        void clear(){
            this->w.clear();
        }
        int LocNum(){
            if(this->empty())
                return -1;
            int base = 1, sum = 0;
            for(auto i = this->w.rbegin(); i != this->w.rend(); i ++){
                if(*i) sum += base;
                base *= 2;
            }
            return base/2 + sum - 1;
        }
        void output(){
            for(auto i = this->w.begin(); i != this->w.end(); i ++)
                if(*i)  std::cout << 1;
                else    std::cout << 0;
            std::cout << std::endl;
            return;
        }
        void push(const Branch b){
            this->w.push_back(b);
        }
        void push(const NodeLoc& nl){
            for(auto i = nl.w.begin(); i != nl.w.end(); i ++)
                this->w.push_back(*i);
        }
        void push(Branch b[] , int n){
            for(int i = 0; i < n; i ++)
                this->w.push_back(b[i]);
        }
        bool empty(){
            return this->w.empty();
        }
        NodeLoc* child(const Branch b){
            NodeLoc* tmp = new NodeLoc(this->w);
            tmp->push(b);
            return tmp;
        }
        NodeLoc operator+(const Branch b){
            NodeLoc tmp(this->w);
            tmp.push(b);
            return tmp;
        }
        void operator+=(const Branch& b){
            this->push(b);
        }
};

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
            this->left = NULL;
            this->right = NULL;
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
                std::vector<char> vec;
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
                    std::vector<char> _vec;
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
        bool ifLeaf(){ //判断是否是叶子节点
            return this->left == NULL && this->right == NULL;
        }
        int Depth(){ //求深度
            int ldepth = this->left == NULL ? 0 : this->left->Depth();
            int rdepth = this->right == NULL ? 0 : this->right->Depth();
            return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
        }
        int LeafCount(){ //求叶子节点数
            int lcount = this->left == NULL ? 0 : this->left->LeafCount();
            int rcount = this->right == NULL ? 0 : this->right->LeafCount();
            return this->ifLeaf() ? 1 : lcount + rcount;
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
        BiTreeNode* copy(){ //复制二叉树
            BiTreeNode* newNode = new BiTreeNode(this->data);
            if(this->left != NULL)
                newNode->left = this->left->copy();
            if(this->right != NULL)
                newNode->right = this->right->copy();
            return newNode;
        }
        void buildFullTree(int depth = -1){ //构造满二叉树
            if(depth == -1)
                depth = this->Depth();
            if(depth > 1){
                if(this->left == NULL)
                    this->left = new BiTreeNode();
                this->left->buildFullTree(depth - 1);
                if(this->right == NULL)
                    this->right = new BiTreeNode();
                this->right->buildFullTree(depth - 1);
            }
        }
        void clearEmptyNode(){ //清除空节点
            if(this->left != NULL)
                if(this->left->data == '\0'){
                    this->left->DestoryTree();
                    this->left = NULL;
                }
                else
                    this->left->clearEmptyNode();
            if(this->right != NULL)
                if(this->right->data == '\0'){
                    this->right->DestoryTree();
                    this->right = NULL;
                }
                else
                    this->right->clearEmptyNode();
        }
};


//顺序二叉树
class OrderTree{
    friend class BiTreeNode;
    private:
        std::vector<ElemType> data;
    public:
        OrderTree(BiTreeNode* root = NULL){ //构造函数
            if(root == NULL)
                return;
            BiTreeNode* newTree = root->copy();
            newTree->buildFullTree();
            newTree->LevelOrderTraverse(this->push);
            newTree->DestoryTree();
        }
        OrderTree(ElemType e[], int n){ //构造函数
            for(int i = 0; i < n; i ++)
                this->data.push_back(e[i]);
        }
        void destory(){ //析构函数
            this->data.clear();
            return;
        }
        void Create(BiTreeNode* root){ //创建二叉排序树
            this->destory();
            BiTreeNode* newTree = root->copy();
            newTree->buildFullTree(newTree->Depth());
            std::list<BiTreeNode*> l = {newTree};
            while(!l.empty()){
                this->data.push_back(l.front()->data);
                if(l.front()->left != NULL)
                    l.push_back(l.front()->left);
                if(l.front()->right != NULL)
                    l.push_back(l.front()->right);
                l.pop_front();
            }
        }
        void input(char str[]){ //输入
            this->destory();
            int n = strlen(str);
            for(int i = 0; i < n; i ++)
                this->data.push_back(str[i]);
        }
        void push(ElemType elem){ //插入元素
            this->data.push_back(elem);
        }
        void output(){ //输出二叉排序树
            for(auto i : this->data)
                if(i == '\0')
                    std::cout << "#";
                else
                    std::cout << i;
            std::cout << std::endl;
        }
        int Depth(){ //求深度
            int i = 1, depth = 0;
            while(i <= this->data.size()){
                i *= 2;
                depth ++;
            }
            return depth;
        }
        BiTreeNode* ToBiTree(){ //转换为二叉树
            int depth = 0, j = 1;
            while(this->data.size() > j){
                j *= 2;
                depth ++;
            }
            BiTreeNode* result = new BiTreeNode();
            result->buildFullTree(depth);
            std::list<BiTreeNode*> l = {result};
            std::list<ElemType> el(this->data.data(),this->data.data()+this->data.size());
            while(!el.empty()){
                l.front()->data = el.front();
                el.pop_front();
                l.push_back(l.front()->left);
                l.push_back(l.front()->right);
                l.pop_front();
            }
            result->clearEmptyNode();
            return result;
        }
        void LevelOrder(void (*Visit)(ElemType e)){ //层序遍历
            for(auto elem : this->data)
                if(elem != '\0')
                    std::cout << elem << " ";
            std::cout << std::endl;
        }
        void PreOrder(void (*Visit)(ElemType e), int depth = -1, NodeLoc* nl = new NodeLoc(0)){ //先序遍历
            if(depth == -1)
                depth = this->Depth();
            if(nl->empty())
                nl->push(0);
            if(depth == 0)
                return;
            Visit(this->data[nl->LocNum()]);
            PreOrder(Visit, depth-1, nl->child(0));
            PreOrder(Visit, depth-1, nl->child(1));
        }
        void InOrder(void (*Visit)(ElemType e), int depth = -1, NodeLoc* nl = new NodeLoc()){ //中序遍历
            if(depth == -1)
                depth = this->Depth();
            if(nl->empty())
                nl->push(0);
            if(depth == 0)
                return;
            InOrder(Visit, depth-1, nl->child(0));
            Visit(this->data[nl->LocNum()]);
            InOrder(Visit, depth-1, nl->child(1));
        }
        void PostOrder(void (*Visit)(ElemType e), int depth = -1, NodeLoc* nl = new NodeLoc()){ //后序遍历
            if(depth == -1)
                depth = this->Depth();
            if(nl->empty())
                nl->push(0);
            if(depth == 0)
                return;
            PostOrder(Visit, depth-1, nl->child(0));
            PostOrder(Visit, depth-1, nl->child(1));
            Visit(this->data[nl->LocNum()]);
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
    public:
        void BuildExpressionTree(const char str[]){ //构造表达式树
            if(str[0] == '\0')
                return;
            std::vector<char> formula;
            int j = 0;
            for(int i = 0; i < strlen(str); i ++){
                formula.push_back(str[i]);
                if(str[i] == '(')
                    j ++;
                else if(str[i] == ')')
                    j --;
                else if((str[i] == '+' || str[i] == '-') && j == 0){
                    formula[i] = '\0';
                    this->isOperator = true;
                    this->exp = str[i];
                    this->left = new ExpressionTreeNode();
                    this->left->BuildExpressionTree(formula.data());
                    this->right = new ExpressionTreeNode();
                    this->right->BuildExpressionTree(str + i + 1);
                    return;
                }
            }
            j = 0;
            for(int i = 0; i < strlen(str); i ++){
                formula.push_back(str[i]);
                if(str[i] == '(')
                    j ++;
                if(str[i] == ')')
                    j --;
                if((str[i] == '*' || str[i] == '/') && j == 0){
                    formula[i] = '\0';
                    this->isOperator = true;
                    this->exp = str[i];
                    this->left = new ExpressionTreeNode();
                    this->left->BuildExpressionTree(formula.data());
                    this->right = new ExpressionTreeNode();
                    this->right->BuildExpressionTree(str + i + 1);
                    return;
                }
            }
            if(str[0] == '('){
                std::vector<char> vec;
                for(int i = 1; i < strlen(str)-1; i ++)
                    vec.push_back(str[i]);
                this->BuildExpressionTree(vec.data());
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