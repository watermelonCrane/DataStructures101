#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

    // Element라는 구조체를 원소로 가지는 스택을 만들거임
    // n개의 스택을 만들거임

#define MAX_STACK 10
//#define MAX_SIZE 50
//여기서는 array로 스택을 만들 때 처럼 MAX_SIZE가 필수가 아니다! 그렇다고 최대치를 안두면 메모리가 터질지도?

typedef struct Element {
    int key;
    // 내가 스택에 넣고싶은 자료형
} Element;

typedef struct Stack {
    Element data;
    struct Stack* link;

} Stack;

Stack* top[MAX_STACK];

bool isEmpty(int n) {       //n번째 스택의 비어있는지 여부를 체크
    if (top[n] == NULL) {
        return true;
    }
    else {
        return false;
    }
}

//bool isFull(int n);     //n번째 스택이 꽉 찾는지 확인

void push(int n, Element data) {        //n번째 스택에 Element 자료형 Push
    Stack* tmp = (Stack*)malloc(sizeof(Stack));
    tmp->data = data;
    tmp->link = top[n];
    top[n] = tmp;
}

Element pop(int n) {
    if (top[n] == NULL) {
        fprintf(stderr, "Stack is Empty!\n");
        exit(1);
    }

    Element data = top[n]->data;

    Stack* tmp = top[n];
    top[n] = top[n]->link;
    free(tmp);

    return data;
}


int main() {

    int n = 3;

    // create n stacks
    for (int i = 0; i < n; i++) {
        top[i] = NULL;
    }

    Element tempData;

    tempData.key = 1;
    push(0, tempData);

    tempData.key = 2;
    push(0, tempData);

    tempData.key = 3;
    push(0, tempData);

    tempData.key = 21;
    push(2, tempData);

    tempData = pop(0);
    printf("%d", tempData.key);

    pop(1);     ///make error: stack empty!

    return 0;
}