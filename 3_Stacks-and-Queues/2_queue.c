#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 8

typedef int element;

element globalQueue[MAX_QUEUE_SIZE];
int start = 0;
int rear = 0;

bool isEmpty() {
    if (start == rear) return true;
    else return false;
}

bool isFull() {
    if ((rear + 1) % MAX_QUEUE_SIZE == start) return true;
    else return false;
}

void push(element data) {
    if (isFull()) {
        fprintf(stderr, "Queue is Fulled");
        exit(1);
    }
    globalQueue[rear++] = data;
    rear %= MAX_QUEUE_SIZE;
}

element front() {
    if (isEmpty()) {
        fprintf(stderr, "Queue is Empty");
        exit(1);
    }
    return globalQueue[start];
}

element back() {
    if (isEmpty()) {
        fprintf(stderr, "Queue is Empty");
        exit(1);
    }
    return globalQueue[rear];
}

void pop() {
    if (isEmpty()) {
        fprintf(stderr, "Queue is Empty");
        exit(1);
    }
    
    start++;
    start %= MAX_QUEUE_SIZE;

}

int main() {

    for (int i = 0; i < 6; i++) {       // 1, 2, 3, 4, 5, 6
        push(i + 1);
    }

    for (int i = 0; i < 5; i++) {       // 6
        printf("%d ", front());
        pop();
    }

    for (int i = 0; i < 4; i++) {       // 6, 7, 8, 9, 10
        push(i + 7);
    }

    for (int i = 0; i < 6; i++) {       // error!
        printf("%d ", front());
        pop();
    }

    return 0;
}