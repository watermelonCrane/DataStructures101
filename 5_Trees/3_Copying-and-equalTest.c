#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* leftchild;
    struct Node* rightchild;
} Node;

// Node Queue
#define MAX_QUEUE 8

Node* Queue[MAX_QUEUE];
int front = 0;
int rear = 0;

void initQueue() {
    front = rear = 0;
}

bool isEmpty() {
    if (front == rear) return true;
    else return false;
}

bool isFull() {
    if ((rear + 1) % MAX_QUEUE == front) return true;
    else return false;
}

void push(Node* NP) {
    if (isFull() == true) {
        fprintf(stderr, "queue is full\n");
        exit(1);
    }
    Queue[rear] = NP;
    rear++;
    rear %= MAX_QUEUE;
}

Node* pop() {
    if (isEmpty() == true) {
        fprintf(stderr, "q is empty\n");
        exit(1);
    }
    Node* tmp = Queue[front];

    front++;
    front %= MAX_QUEUE;

    return tmp;
}
//--end Node Queue


// Tree functions
#define MAX_TREE 6  //트리 최대 노드 개수

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->leftchild = NULL;
    node->rightchild = NULL;

    return node;
}

Node* makeTree(int data[]) {
    initQueue();

    Node* root = newNode(data[0]);
    push(root);
    for (int i = 1; i < MAX_TREE; i++) {
        Node* tmpNode = newNode(data[i]);
        if (Queue[front]->leftchild == NULL) {
            Queue[front]->leftchild = tmpNode;
        }
        else if (Queue[front]->rightchild == NULL) {
            Queue[front]->rightchild = tmpNode;
            pop();
        }
        push(tmpNode);
    }

    return root;
}

Node* copyTree(Node* originalRoot) {
    if (originalRoot == NULL) return NULL;

    Node* copyRoot = newNode(originalRoot->data);

    copyRoot->leftchild = copyTree(originalRoot->leftchild);
    copyRoot->rightchild = copyTree(originalRoot->rightchild);

    return copyRoot;
}

bool equalTree(Node* firstRoot, Node* secondRoot) {
    if ((!firstRoot && !secondRoot) || firstRoot->data == secondRoot->data && equalTree(firstRoot->leftchild, secondRoot->leftchild) && equalTree(firstRoot->rightchild, secondRoot->rightchild)) {
        return true;        
    }
    else {
        return false;
    }
}

//--end Tree functions

int main() {
    int data[MAX_TREE] = {1, 2, 3, 4, 5, 6};

    Node* newTree = makeTree(data);

    Node* copied = copyTree(newTree);

    int anotherData[MAX_TREE] = {1, 2, 3, 0, 5, 6};
    Node* anotherTree = makeTree(anotherData);

    if (equalTree(newTree, copied) == true) printf("Two tree is equal\n");
    else printf("Two Tree is different\n");

    if (equalTree(newTree, anotherTree) == true) printf("Two tree is equal\n");
    else printf("Two Tree is different\n");

    return 0;
}