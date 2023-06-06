#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <locale>

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isNumericDigit(char c) {
    return c >= '0' && c <= '9';
}

int getOperatorWeight(char op) {
    int weight = -1;
    switch (op) {
    case '+':
    case '-':
        weight = 1;
        break;
    case '*':
    case '/':
        weight = 2;
        break;
    case '^':
        weight = 3;
        break;
    }
    return weight;
}

bool hasHigherPrecedence(char op1, char op2) {
    int op1Weight = getOperatorWeight(op1);
    int op2Weight = getOperatorWeight(op2);
    if (op1Weight == op2Weight) {
        return true;
    }
    return op1Weight > op2Weight ? true : false;
}

double applyOperation(char op, double b, double a) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0) {
            throw "Ошибка деление на ноль!";
        }
        return a / b;
    case '^':
        return pow(a, b);
    }
    return 0.0;
}

string infixToPostfix(string expression) {
    stack<char> operators;
    string postfix = "";
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ' || expression[i] == ',') {
            continue;
        }
        else if (isNumericDigit(expression[i])) {
            string num;
            while (i < expression.length() && (isNumericDigit(expression[i]) || expression[i] == '.')) {
                num += expression[i];
                i++;
            }
            i--;
            postfix += num + " ";
        }
        else if (isOperator(expression[i])) {
            while (!operators.empty() && operators.top() != '(' && hasHigherPrecedence(operators.top(), expression[i])) {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.push(expression[i]);
        }
        else if (expression[i] == '(') {
            operators.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += " ";
                operators.pop();
            }
            operators.pop();
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        postfix += " ";
        operators.pop();
    }
    return postfix;
}

double evaluatePostfix(string expression) {
    stack<double> values;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ' || expression[i] == ',') {
            continue;
        }
        else if (isNumericDigit(expression[i])) {
            string num;
            while (i < expression.length() && (isNumericDigit(expression[i]) || expression[i] == '.')) {
                num += expression[i];
                i++;
            }
            i--;
            values.push(stod(num));
        }
        else if (isOperator(expression[i])) {
            double val2 = values.top();
            values.pop();
            double val1 = values.top();
            values.pop();
            char op = expression[i];
            values.push(applyOperation(op, val2, val1));
        }
    }
    return values.top();
}

int main() {
    setlocale(LC_ALL, "Russian");
    string expression;
    cout << "Введите выражение: ";
    getline(cin, expression);
    string postfix = infixToPostfix(expression);
    cout << "Постфиксная запись: " << postfix << endl;
    double result = evaluatePostfix(postfix);
    cout << "Результат = " << result << endl;
    return 0;
}