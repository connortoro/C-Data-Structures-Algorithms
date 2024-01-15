/*
Name: Connor Toro
Programmer Number: 31
Hours Spent: 3
Problems?: took a while to figure out how postfixing works, not sure if I missed it in our class materials
*/

#include <iostream>
#include "stack_L_T.h"
#include <stdexcept>
using namespace std;

const string validChars = "1234567890*/+-()";

int priority(char c);
bool valid(string s);
double operate(double x, double y, char o);
string postfix(string equation);
double calculate(string s);

int main() {

    //input
    string equation;
    cin >> equation;

    //check token validity
    if(!valid(equation)){
        cout << "The expression is in a wrong format" << endl;
        return 0;
    }

    try {
        string pf = postfix(equation);
        cout << pf << endl;
        cout << calculate(pf) << endl;
    } catch(...) {
        cout << "The expression is in a wrong format" << endl;
        return 0;
    }
}



string postfix(string equation) {

    //create stack and string
    Stack<char> stack;
    string pf = "";


    //postfix
    for(int i = 0; i < equation.length(); i++) {

        //operand or (
        if(isdigit(equation.at(i))) {
            pf += equation.at(i);
            continue;
        }

        //opening parenthesis
        if(equation.at(i) == '(') {
            stack.push(equation.at(i));
            continue;
        }

        //closing parenthesis
        if(equation.at(i) == ')') {
            while(!stack.empty() && stack.getTop() != '(') {
                pf += stack.getTop();
                stack.pop();
            }
            stack.pop();
            continue;
        }

        //lower precedence than top of stack
        if(!stack.empty() && stack.getTop() != '(' && priority(equation.at(i)) <= priority(stack.getTop())) {
            pf += stack.getTop();
            stack.pop();
            //result might make stack unbalanced so check again
            if(!stack.empty() && stack.getTop() != '(' && priority(equation.at(i)) <= priority(stack.getTop())) {
                pf += stack.getTop();
                stack.pop();
            }
            stack.push(equation.at(i));
            continue;
        }

        //able to be pushed to stack
        stack.push(equation.at(i));


    }
    //push remaining stack to string
    while(!stack.empty()) {
        pf += stack.getTop();
        stack.pop();
    }

    return pf;
}

double calculate(string s) {
    Stack<double> stack;
    for(int i = 0; i < s.length(); i++) {

        //digit
        if(isdigit(s.at(i))) {
            stack.push(static_cast<double>(s.at(i) - '0'));
            continue;
        }

        //operator
        double y = stack.getTop();
        stack.pop();
        double x = stack.getTop();
        stack.pop();

        stack.push(operate(x, y, s.at(i)));
    }
    double result = stack.getTop();
    stack.pop();
    if(!stack.empty()) throw runtime_error("");
    return result;
}

bool valid(string s) {
    for(int i = 0; i < s.length(); i++) {
        if(validChars.find(s.at(i)) == string::npos) {
            return false;
        }
    }
    return true;
}

int priority(char c) {
    if(c == '+' || c == '-') return 1;
    if(c == '/' || c == '*') return 2;
}

double operate(double x, double y, char o) {
    switch(o) {
        case '+':
            return x + y;
            break;
        case '-':
            return x - y;
            break;
        case '/':
            return x / y;
            break;
        case '*':
            return x * y;
            break;
    }
    return 0;
}
