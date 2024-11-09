// 과제: list에서 배운 getNode와 retNode를 이용해서 노드 삭제와 삽입을 해보자.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char data;
    Node* leftchild;
    Node* rightchild;
    bool leftThread;
    bool rightThread;
} Node;

Node* newNode(char data) {
    Node* nd = (Node*)malloc(sizeof(Node));
    nd->data = data;
    nd->leftchild = NULL;
    nd->leftThread = true;
    nd->rightchild = NULL;
    nd->rightThread = true;

    return nd;
}

/************making Threaded Tree****************/
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
        child->leftchild = parent->leftchild;   // 삽입하려는 노드의 leftthread를 부모 노드의 leftthread로 설정
        child->rightchild = parent;             // 삽입하려는 노드의 rightthread를 부모 노드로 설정
        parent->leftchild = child;              // 부모의 leftchild를 삽입하려는 노드로 설정    **a.
        parent->leftThread = false;             // 부모의 leftchild가 thread가 아니라고 설정
    }
    else {
        child->leftchild = parent->leftchild;   // 삽입하려는 노드의 leftthread를 부모 노드의 leftchild로 설정: 기존 하위 subtree이어붙이기
        parent->leftchild = child;              // 부모의 leftchild를 삽입하려는 노드로 설정

        // 이 부분에선 위 코드의 a. 부분이 필요가 없음. 이미 false로 되어있을 것이기 때문

        child->leftThread = false;              // 삽입하려는 노드의 leftchild가 thread가 아니라고 설정
        child->rightchild = parent;             // 삽입하려는 노드의 rightthread를 부모 노드로 설정

        findRightTreadNode(child->leftchild)->rightchild = child;       //마지막 리프노드의 thread 링크 조정 => 삽입하려는 노드로
    }

    return child;       //child 포인터를 다시 내뱉음
}

Node* insertRight(Node* child, Node* parent) {
    if (child->leftThread == false || child->rightThread == false) {
        fprintf(stderr, "this node isn't thread. the data of node: %d", child->data);
        exit(1);
    }

    if (parent->rightThread == true) {
        child->rightchild = parent->rightchild;
        child->leftchild = parent;
        parent->rightchild = child;
        parent->rightThread = false;
    }
    else {
        child->rightchild = parent->rightchild;
        parent->rightchild = child;
        child->rightThread = false;
        child->leftchild = parent;
        
        findLeftTreadNode(child->rightchild)->leftchild = child;
    }

    return child;
}
/******************end making Thread Tree**************/

// Threaded inorder function

// 만들어야 됨


Node* newTree() {
    Node* head = newNode('\0');     //쓰레기값을 포함함
    head->rightchild = head->leftchild = head;

    return head;        // head노드만 뱉어냄
}

int main() {

    Node* ThBT = newTree();
    Node* tmp = newNode('A');

    tmp = insertLeft(tmp, ThBT);

    tmp = insertLeft(newNode('C'), tmp);
    tmp = insertRight(newNode('D'), tmp);

    insertLeft(newNode('E'), tmp);
    insertRight(newNode('F'), tmp);

    tmp = ThBT->leftchild;
    tmp = insertRight(newNode('B'), tmp);
    insertLeft(newNode('G'), tmp);


    return 0;
}