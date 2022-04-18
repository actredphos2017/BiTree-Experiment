#include <cstdio>
#include <assert.h>

class Test
{
    public:
        typedef void (Test::*DATAFUNC) (); // 范例1，类内部的typeDef函数声明，属于Test成员，声明时必须加Test声明作用域，且赋值的函数必须为Test成员（核心原理为类的成员函数实际上参数压栈时多了一个this指针，所以匹配时会做类型检查）
        typedef void (*DATAFUNC2) ();      // 范例2，类内部的typeDef函数声明，属于Test成员，声明时必须加Test声明作用域，且赋值的函数必须不为Test成员

        Test(){mi =0;}
        ~Test(){};

    void testfunc()
    {
        printf("interval testfunc\n");
    }
    private:
        int mi;
};


typedef void (Test::*DATAFUNC1)();
//范例3，类外部的typeDef函数声明，不属于Test成员，声明时不能加Test声明作用域，赋值的函数必须为Test成员
typedef void (*FUNC)();
//范例4，类外部的typeDef函数声明，不属于Test成员，声明时不能加Test声明作用域，赋值的函数必须不为Test成员

void testfunc2() {printf("external testfunc2\n");}

int main(int argc, char* argv[])
{
    Test t;
    Test::DATAFUNC      pfunc   = NULL;    
    Test::DATAFUNC2     pfunc2  = NULL;
    DATAFUNC1           pfunc1  = NULL;
    FUNC                pf      = NULL;


    printf("the addr of Test::testfunc is %x\n",&Test::testfunc);
    //printf("the addr of t.testfunc is %x\n",&(t.testfunc)); //对象没有成员函数地址，类才有成员函数地址

    //范例1
    pfunc = &Test::testfunc;  //不必要也不能使用对象的成员函数，因为成员函数都属于类本身，在构建对象之前就会构建。
    //pfunc();                  //无法输出，pfunc的实际指向是类的成员，必须依赖类的对象或者静态化来输出；
    (t.*pfunc)();               //输出
    //pfunc = &testfunc2;       //无法转换，赋值函数必须为类成员类型

    //范例2
    //pfunc2 =  &Test::testfunc;  //无法转换，赋值函数必须为全局void (*) ()类型，不能为类成员
    pfunc2   = &testfunc2;        //&可用可不用，全局函数名是表示函数地址的
    pfunc2();                     //可以输出，指针实际指向的不是类的成员。

    //范例3
    pfunc1 =&Test::testfunc;   //虽然typedef本身
    //pfunc1();
    (t.*pfunc1)();             //同样可以借助类对象输出，就是很别扭！不能直接调用
    //pfunc1  = testfunc2;

    //范例4
    //pf  = &Test::testfunc;     //FUNC类型也不是类成员，无需this指针
    //pf();                        //可以输出，但注意测试并没有被赋值
    pf = &testfunc2;
    pf();
    
    return 0;
}