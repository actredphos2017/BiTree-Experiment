#include "head/tree.h"

using namespace std;

int main(){
    Branch b[] = {0,1,1,1};
    NodeLoc a(b,4);
    cout << a.LocNum() << endl;
    return 0;
}