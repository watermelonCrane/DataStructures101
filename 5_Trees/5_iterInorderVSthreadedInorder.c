#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//Threaded부분은 이전 코드 그대로 가져왔음.

typedef struct Node {
    char data;
    struct Node* rightChild;
    struct Node* leftChild;
    bool leftThreaded, rightThreaded;
} Node;

Node* newNode(char data);
Node* newTree();
Node* insertRight(Node* parrent, Node* child);
Node* insertLeft(Node* parrent, Node* child);
void printInorder(Node* head);
Node* insucc(Node* n);
Node* inpre(Node* n);

void iterInorder(Node* root);

#define MAX_STACK 15
typedef struct ElementforStack {
    Node* node;
    int phase;
} Element;

Element Stack[MAX_STACK];
int top = -1;

void push(Node* node, int phase) {
    top++;
    Stack[top].node = node;
    Stack[top].phase = phase;
}

void pop() {
    top--;
}

bool isEmpty() {
    return top == -1 ? true : false;
}

int main() {
    Node* Tree_1 = newTree();   // 비어있는 새 트리 생성

    // 예제 트리를 노드 삽입을 통해 생성
    Node* tmp = insertLeft(Tree_1, newNode('A'));

    tmp = insertLeft(tmp, newNode('C'));
    tmp = insertRight(tmp, newNode('D'));
    
    insertLeft(tmp, newNode('E'));
    insertRight(tmp, newNode('F'));

    tmp = insertRight(Tree_1->leftChild, newNode('B'));
    insertLeft(tmp, newNode('G'));

    clock_t start, end;

    start = clock();
    for (int i = 0; i < 500; i++) {
        printInorder(Tree_1);
    }
    end = clock();
    printf("스레드탐색 소요시간: %ld\n", end - start);

    start = clock();
    tmp = Tree_1->leftChild;
    for (int i = 0; i < 500; i++) {
        iterInorder(Tree_1);
    }
    end = clock();
    printf("기본탐색 소요시간: %d", end - start);
    //왜 이게 더 빠르냐;;;;;


    return 0;
}

void iterInorder(Node* root) {
    top = -1;
    for(push(root, 0); isEmpty() == false; ) {

        if (Stack[top].node->leftThreaded != true && Stack[top].phase < 1) {
            Stack[top].phase = 1;
            push(Stack[top].node->leftChild, 0);
            continue;
        } // phase 1 end;

        if (Stack[top].phase < 2) {
            printf("%c ", Stack[top].node->data);
            Stack[top].phase = 2;
        } // phase 2 end;       // nomal code

        if (Stack[top].node->rightThreaded != true && Stack[top].phase < 3) {
            Stack[top].phase = 3;
            push(Stack[top].node->rightChild, 0);
            continue;
        } // phase 2 end;

        pop();
        if (Stack[top].node->data == '\0') break;
    }
}

Node* newNode(char data) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = data;
    tmp->leftChild = tmp->rightChild = tmp;
    tmp->leftThreaded = tmp->rightThreaded = false;

    return tmp;
}

Node* newTree() {
    Node* head = newNode('\0');
    head->leftThreaded = true;
    return head;
}

Node* insertRight(Node* parrent, Node* child) {
    child->rightChild = parrent->rightChild;
    child->leftChild = parrent;
    child->leftThreaded = true;
    child->rightThreaded = parrent->rightThreaded;
    parrent->rightThreaded = false;
    parrent->rightChild = child;

    if (child->rightThreaded == false) {
        insucc(child)->leftChild = child;    
    }

    return child;       //삽입한 노드 주소 반환
}

Node* insertLeft(Node* parrent, Node* child) {
    child->leftChild = parrent->leftChild;
    child->rightChild = parrent;
    child->rightThreaded = true;
    child->leftThreaded = parrent->leftThreaded;
    parrent->leftChild = child;
    parrent->leftThreaded = false;

    if (child->leftThreaded == false) {
        inpre(child)->rightChild = child;
    }

    return child;
}


void printInorder(Node* head) {
    Node* tmp = head;
    for (;;) {
        tmp = insucc(tmp);
        if (tmp == head) return;
        printf("%c ", tmp->data);
    }
}

Node* insucc(Node* n) {
    Node* temp = n->rightChild;
    
    if (n->rightThreaded == false) {
        for (; temp->leftThreaded == false; temp = temp->leftChild);
        /* if (temp->leftChild != n) {     //오류검출 나중에 지울거임      /// 이것은 삽입 코드를 작동시 동작이 안됨. 괜히 leftThreaded로 위에서 반복문 돌리는게 아님
            fprintf(stderr, "오류발생. node: %c", temp->data);
            exit(1);
        } */
    }

    return temp;

}

Node* inpre(Node* n) {
    Node* tmp = n->leftChild;

    if (n->leftThreaded == false) {
        for(; tmp->rightThreaded == false; tmp = tmp->rightChild);
    }

    return tmp;
}
