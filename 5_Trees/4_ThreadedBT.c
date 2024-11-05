// 과제: list에서 배운 getNode와 retNode를 이용해서 노드 삭제와 삽입을 해보자.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    Node* leftchild;
    Node* rightchild;
    bool leftThread;
    bool rightThread;
} Node;

Node* newNode(int data) {
    Node* nd = (Node*)malloc(sizeof(Node));
    nd->data = data;
    nd->leftchild = NULL;
    nd->leftThread = true;
    nd->rightchild = NULL;
    nd->rightThread = true;

    return nd;
}

Node* insertLeft(Node* child, Node* parent) {
    if (child->leftThread == false || child->rightchild == false) {
        fprintf(stderr, "this node isn't thread. the data of node: %d", child->data);
        exit(1);
    }

    if (parent->leftThread == true) {
        child->leftchild = parent->leftchild;
        child->rightchild = parent;
        parent->leftchild = child;
        parent->leftThread = false;
    }
    else {
        /// 만드는 중
    }
}

Node* insertRight(Node* child, Node* parent) {

}

Node* newTree() {
    Node* head = newNode(9876);
    head->rightchild = head;



}

int main() {

    return 0;
}