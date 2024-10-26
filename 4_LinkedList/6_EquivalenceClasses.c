//본 코드는 주어진 쌍의 관계에서 동치관계를 찾아서 출력하는 코드입니다.
// x ~ x이며, x ~ y이면 y ~ x이고, x ~ y 이면서 y ~ z이면 x ~ z가 되는 관계를 동치관계라고 말합니다.
// 입력은 6_inputData.txt에서 가져올 것이고, 첫줄에는 읽어올 데이터 쌍의 개수가 주어집니다.
// 데이터 쌍은 "x y"처럼 공백을 기준으로 구분하며 이는 x ~ y라는 뜻입니다.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 12
#define MAX_STACK 50

int Stack[MAX_STACK];
int top = -1;

bool isEmpty() {
    if (top == -1) return true;
    else return false;
}

bool isFull() {
    if (top >= MAX_STACK - 1) return true;
    else return false;
}

void push(int data)  {
    if (isFull() == true) {
        fprintf(stderr, "Stack is Full!");
        exit(1);
    }
    top++;
    Stack[top] = data;
}

void justPop() {
    if (isEmpty() == true) {
        fprintf(stderr, "Stack is empty!");
        exit(1);
    }
    top--;
}


typedef struct Node {
    int data;
    struct Node* link;
} Node;

Node* seq[MAX_SIZE] = {0};
bool isOut[MAX_SIZE] = {0};       //교재에서는 기본값을 1로 했는데, 왜 1로하냐 그냥 0으로 하면 되지.

Node* newNode(int data) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL) {
        fprintf(stderr, "malloc error. data = %d", data);
        exit(1);
    }
    tmp->data = data;
    tmp->link = NULL;

    return tmp;
}

void attach(int x, int y){  //y를 x열에 가져다 붙여버리자.
    Node* tmp = seq[x];
    seq[x] = newNode(y);
    seq[x]->link = tmp;
}

void dataInput(int n) {
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        attach(x, y);
        attach(y, x);
    }
}

void printEquivalence(int n) {
    Node* ptr = NULL;
    for (int i = 0; i < n; i++) {
        if (isOut[i] == true) continue;
        
        printf("Class %d:\n", i + 1);   //새로운 묶음임을 얄려줌

        int ii = i;
        do {
            printf("%d ", ii);
            isOut[ii] = true;

            for (ptr = seq[ii]; ptr != NULL; ptr = ptr->link) {
                if (isOut[ptr->data] == false) push(ptr->data);
            }
            if (isEmpty() == true) break;

            ii = Stack[top];
            justPop();

        } while (1);

        printf("\n");   //구분용도
    }
}

int main() {
    freopen("6_inputData.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    dataInput(n);
    printEquivalence(n);

    return 0;
}