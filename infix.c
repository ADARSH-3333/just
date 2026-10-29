#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char charStack[MAX];
int charTop = -1;

void pushChar(char c) {
    charStack[++charTop] = c;
}

char popChar() {
    return charStack[charTop--];
}

char peekChar() {
    if (charTop == -1) return '\0';
    return charStack[charTop];
}

int intStack[MAX];
int intTop = -1;

void pushInt(int val) {
    intStack[++intTop] = val;
}

int popInt() {
    return intStack[intTop--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    int j = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            pushChar(ch);
        }
        else if (ch == ')') {
            while (charTop != -1 && peekChar() != '(') {
                postfix[j++] = popChar();
            }
            popChar(); 
        }
        else {
            while (charTop != -1 && precedence(peekChar()) >= precedence(ch)) {
                postfix[j++] = popChar();
            }
            pushChar(ch);
        }
    }

    while (charTop != -1) {
        postfix[j++] = popChar();
    }
    postfix[j] = '\0';
}

int evaluatePostfix(char postfix[]) {
    intTop = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            pushInt(ch - '0');
        }
        else {
            int op2 = popInt();
            int op1 = popInt();
            
            switch (ch) {
                case '+': pushInt(op1 + op2); break;
                case '-': pushInt(op1 - op2); break;
                case '*': pushInt(op1 * op2); break;
                case '/': pushInt(op1 / op2); break;
            }
        }
    }
    return popInt();
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter a valid infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("postfix: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("result: %d\n", result);

    return 0;
}

