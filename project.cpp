#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>

typedef char ElemType;
typedef char ExpressionType;
typedef int DigitalType;
using namespace std;

class BiTreeNode{
    private:
        ElemType data;
        BiTreeNode* left;
        BiTreeNode* right;
    public:
        BiTreeNode(ElemType _data = '\0'){
            this->data = _data;
            this->left = NULL;
            this->right = NULL;
        }
        void DestoryTree(){
            if(this->left)
                this->left->DestoryTree();
            if(this->right)
                this->right->DestoryTree();
            delete this;
        }
        void CreateTree(const char str[]){
            if(strlen(str) == 0)
                return;
            this->data = str[0];
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
                    this->left = NULL;
                    this->right = new BiTreeNode();
                    this->right->CreateTree(vec.data() + 1);
                }
                else{
                    vector<char> _vec;
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
        void PreOrderTraverse(){
            cout << this->data << " ";
            if(this->left != NULL)
                this->left->PreOrderTraverse();
            if(this->right != NULL)
                this->right->PreOrderTraverse();
        }
        void InOrderTraverse(){
            if(this->left != NULL)
                this->left->InOrderTraverse();
            cout << this->data << " ";
            if(this->right != NULL)
                this->right->InOrderTraverse();
        }
        void PostOrderTraverse(){
            if(this->left != NULL)
                this->left->PostOrderTraverse();
            if(this->right != NULL)
                this->right->PostOrderTraverse();
            cout << this->data << " ";
        }
        void LevelOrderTraverse(){
            list<BiTreeNode*> l = {this};
            while(!l.empty()){
                cout << l.front()->data << " ";
                if(l.front()->left != NULL)
                    l.push_back(l.front()->left);
                if(l.front()->right != NULL)
                    l.push_back(l.front()->right);
                l.pop_front();
            }
        }
        bool ifLeaf(){
            return this->left == NULL && this->right == NULL;
        }
        int Depth(){
            int ldepth = this->left == NULL ? 0 : this->left->Depth();
            int rdepth = this->right == NULL ? 0 : this->right->Depth();
            return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
        }
        int LeafCount(){
            int lcount = this->left == NULL ? 0 : this->left->LeafCount();
            int rcount = this->right == NULL ? 0 : this->right->LeafCount();
            return this->ifLeaf() ? 1 : lcount + rcount;
        }
        void DispTree(){
            if(this->left == NULL && this->right == NULL){
                cout<<this->data;
                return;
            }
            else if(this->right == NULL){
                cout<<this->data<<"(";
                this->left->DispTree();
                cout<<")";
            }
            else{
                cout<<this->data<<"(";
                this->left->DispTree();
                cout<<",";
                this->right->DispTree();
                cout<<")";
            }
        }
        ElemType elemData(){
            return this->data;
        }
        BiTreeNode* leftChild(){
            return this->left;
        }
        BiTreeNode* rightChild(){
            return this->right;
        }
        BiTreeNode* copy(){
            BiTreeNode* newNode = new BiTreeNode(this->data);
            if(this->left != NULL)
                newNode->left = this->left->copy();
            if(this->right != NULL)
                newNode->right = this->right->copy();
            return newNode;
        }
        void buildFullTree(int depth = -1){
            if(depth == 0)
                return;
            if(depth == -1)
                depth = this->Depth()-1;
            if(this->left == NULL)
                this->left = new BiTreeNode();
            this->left->buildFullTree(depth - 1);
            if(this->right == NULL)
                this->right = new BiTreeNode();
            this->right->buildFullTree(depth - 1);
        }
        void changeData(ElemType _data){
            this->data = _data;
            return;
        }
        void clearEmptyNode(){
            if(this->data == '\0'){
                this->DestoryTree();
                return;
            }
            if(this->left != NULL)
                this->left->clearEmptyNode();
            if(this->right != NULL)
                this->right->clearEmptyNode();
        }
};

class OrderTree{
    private:
        vector<ElemType> data;
    public:
        OrderTree(BiTreeNode* root){
            BiTreeNode* newTree = root->copy();
            newTree->buildFullTree();
            list<BiTreeNode*> l = {newTree};
            while(!l.empty()){
                this->data.push_back(l.front()->elemData());
                if(l.front()->leftChild() != NULL)
                    l.push_back(l.front()->leftChild());
                if(l.front()->rightChild() != NULL)
                    l.push_back(l.front()->rightChild());
                l.pop_front();
            }
        }
        void destory(){
            this->data.clear();
            return;
        }
        void setup(BiTreeNode* root){
            this->destory();
            BiTreeNode* newTree = root->copy();
            newTree->buildFullTree();
            list<BiTreeNode*> l = {newTree};
            while(!l.empty()){
                this->data.push_back(l.front()->elemData());
                if(l.front()->leftChild() != NULL)
                    l.push_back(l.front()->leftChild());
                if(l.front()->rightChild() != NULL)
                    l.push_back(l.front()->rightChild());
                l.pop_front();
            }
        }
        void push(ElemType elem){
            this->data.push_back(elem);
        }
        void output(){
            for(int i = 0; i < this->data.size(); i++)
                if(this->data[i] == '\0')
                    cout << "#";
                else
                    cout << this->data[i];
            cout << endl;
        }
        BiTreeNode* ToBiTree(){
            int depth = 0, j = 1;
            while(this->data.size() > j){
                j *= 2;
                depth ++;
            }
            BiTreeNode* result = new BiTreeNode();
            result->buildFullTree(depth);
            list<BiTreeNode*> l = {result};
            list<ElemType> el(this->data.data(),this->data.data()+this->data.size());
            while(!el.empty()){
                l.front()->changeData(el.front());
                el.pop_front();
                l.push_back(l.front()->leftChild());
                l.push_back(l.front()->rightChild());
                l.pop_front();
            }
            result->clearEmptyNode();
            return result;
        }
};

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
        void BuildExpressionTree(const char str[]){
            if(str[0] == '\0')
                return;
            vector<char> formula;
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
                vector<char> vec;
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
        
        void ExpressionTreeTraverse(){
            if(this->isOperator){
                if(this->exp != '*' && this->exp != '/' && !(this->left->isOperator || this->right->isOperator))
                    cout << "(";
                this->left->ExpressionTreeTraverse();
                cout << this->exp;
                this->right->ExpressionTreeTraverse();
                if(this->exp != '*' && this->exp != '/' && !(this->left->isOperator || this->right->isOperator))
                    cout << ")";
            }
            else
                cout << this->num;
        }

        int CalcExpressionTree(){
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

#elif 0

int main(){
    BiTreeNode* root = new BiTreeNode();
    string str;
    cin >> str;
    root->CreateTree(str.data());
    root->LevelOrderTraverse();
    OrderTree ot(root);
    ot.output();
    root.DestoryTree();
    root = ot.ToBiTree();
    root->LevelOrderTraverse();
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

//A(B(D,E),C(,F(G,)))
//9+(3*(4/2))