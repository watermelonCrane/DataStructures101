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

Node* findLeftTreadNode(Node* root) {
    if (root->leftThread == true) return root;
    return findLeftTreadNode(root->leftchild);
}

Node* findRightTreadNode(Node* root) {
    if (root->rightThread == true) return root;
    return findRightTreadNode(root->rightchild);
}

Node* insertLeft(Node* child, Node* parent) {
    if (child->leftThread == false || child->rightThread == false) {                     // subTree는 insert 할 수 없음 오직 단독 노드만
        fprintf(stderr, "this node isn't thread. the data of node: %d", child->data);
        exit(1);
    }

    if (parent->leftThread == true) {           // 삽입하려는 노드의 부모될 노드가 리프노드라면
        child->leftchild = parent->leftchild;
        child->rightchild = parent;
        parent->leftchild = child;
        parent->leftThread = false;
    }
    else {
        child->leftchild = parent->leftchild;
        parent->leftchild = child;

        child->leftThread = false;
        child->rightThread = true;
        child->rightchild = parent;

        findRightTreadNode(child->leftchild)->rightchild = child;       //마지막 리프노드의 thread 링크 조정 => 삽입하려는 노드로
    }

    return child;       //child 포인터를 다시 내뱉음
}

Node* insertRight(Node* child, Node* parent) {

}

Node* newTree() {
    Node* head = newNode(9876);     //쓰레기값을 포함함
    head->rightchild = head->leftchild = head;

    return head;        // head노드만 뱉어냄
}

int main() {

    Node* ThBT = newTree();
    Node* tmp = insertLeft(newNode(1), ThBT);
    
    tmp = insertLeft(newNode(2), tmp);
    tmp = tmp->rightchild;

    tmp = insertLeft(newNode(0), tmp);

    return 0;
}