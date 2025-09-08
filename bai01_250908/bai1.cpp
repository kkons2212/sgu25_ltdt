#include <stack>
#include <string>
#include <iostream>
using namespace std;

struct Lop
{
    int malop;
    string tenlop;
};

stack<char> s1;
stack<int> s2;
stack<double> s3;
stack<string> s4;
stack<Lop> s5;

int main()
{
    // s1
    s1.push('a');
    s1.push('b');
    while(s1.empty() == false){
        char c = s1.top();
        s1.pop();
        cout << c <<  " ";
    }
    cout << endl;

    return 0;
}