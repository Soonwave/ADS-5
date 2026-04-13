// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"
int getPriority(char op) {
    switch (op) {
    case '(': return 0;
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default:  return -1;
    }
}

int applyOp(int a, int b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default:  return 0;
    }
}

std::string infx2pstfx(const std::string& inf) {
    std::string post = "";
    TStack<char, 100> stack;
    for (int i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                post += inf[i++];
            }
            post += ' ';
            i--;
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                post += stack.top();
                post += ' ';
                stack.pop();
            }
            stack.pop();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && getPriority(stack.top()) >= getPriority(c)) {
                post += stack.top();
                post += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        post += stack.top();
        post += ' ';
        stack.pop();
    }
    if (!post.empty() && post.back() == ' ') post.pop_back();
    return post;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;

    for (int i = 0; i < post.length(); ++i) {
        if (isspace(post[i])) continue;
        if (isdigit(post[i])) {
            int num = 0;
            while (i < post.length() && isdigit(post[i])) {
                num = num * 10 + (post[i++] - '0');
            }
            stack.push(num);
            i--;
        }
        else {
            int v2 = stack.top(); stack.pop();
            int v1 = stack.top(); stack.pop();
            stack.push(applyOp(v1, v2, post[i]));
        }
    }
    return stack.top();
}
