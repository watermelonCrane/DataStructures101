#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX_STACK_SIZE 100

typedef int element;

element stack[MAX_STACK_SIZE];
int top = -1;   // denote an empty stack

bool isEmpty() {
    if (top <= -1) return true;
    else return false;
}

bool isFull() {
    if (top >= MAX_STACK_SIZE - 1) return true;
    else return false;
}

void push(element item) {
    if (isFull()) {
        fprintf(stderr, "Stack is full");
        exit(1);
    }
    stack[++top] = item;
}
void pop() {
    if (isEmpty()) {
        fprintf(stderr, "Stack is empty");
        exit(1);
    }
    top--;
}

element back() {
    if (isEmpty()) {
        fprintf(stderr, "stack is empty");
        exit(1);
    }
    return stack[top];
}

int main() {

    top = -1;

    push(1);
    push(2);
    push(3);

    for (; !isEmpty(); ) {
        printf("%d", back());
        pop();
    }

    return 0;
}