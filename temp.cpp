#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int main(){
    vector<char> vec = {'a', 'b', 'c', 'd', 'e', '\0'};
    vector<char*> vec2 = {vec.data()};
    vec.clear();
    vec = {'f', 'g', 'h', 'i', 'j', '\0'};
    vec2.push_back(vec.data());
    cout << vec2.data()[0] << endl << vec2.data()[1] << endl;
}