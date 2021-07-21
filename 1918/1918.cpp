// https://www.acmicpc.net/problem/1918 //
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int priority(char a) {
    if(a == '(' || a == ')') return 1;
    else if(a == '+' || a == '-') return 2;
    else if(a == '*' || a == '/') return 3;
    else return -1;
}

string postfix(string str) {
    string result = "";
    stack<char> operatorStack;
    int size = str.size();
    for(int i = 0; i < size; ++i) {
        if(priority(str[i]) == -1) result += str[i];
        else if(str[i] == '(') {
            operatorStack.push(str[i]);
        }
        else if(str[i] == ')') {
            while(true) {
                char tmp = operatorStack.top();
                if(tmp == '(') {
                    operatorStack.pop();
                    break;
                }
                else {
                    result += tmp;
                    operatorStack.pop();
                }
            }
        }
        else {
            if(!operatorStack.empty() && priority(operatorStack.top()) >= priority(str[i])) {
                while(true) {
                    result += operatorStack.top();
                    operatorStack.pop();
                    if(operatorStack.empty() || priority(operatorStack.top()) < priority(str[i])) {
                        break;
                    }
                }
            }
            operatorStack.push(str[i]);
        }
    }

    while(!operatorStack.empty()) {
        result += operatorStack.top();
        operatorStack.pop();
    }

    return result;
}

int main() {
    string expression;
    cin >> expression;
    cout << postfix(expression);
    return 0;
}