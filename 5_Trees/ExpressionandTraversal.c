#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char data;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

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

Node* newNode(char data) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = data;
    tmp->leftChild = NULL;
    tmp->rightChild = NULL;
    return tmp;
}

Node* makeEXTree(); // make infix exp : A/B*C*D+E

void inorder(Node* root) {
    if (root == NULL) return;
    if (root->leftChild != NULL) {
        inorder(root->leftChild);
    }
    printf("%c", root->data);
    if (root->rightChild != NULL) {
        inorder(root->rightChild);
    }
}

///////////////아ㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏㅏ 모르겠다.
// 헷갈리면 참고해 보자: https://algorfati.tistory.com/229
void iter_inorder(Node* root) {
    for(push(root, 0); isEmpty() == false; ) {

        if (Stack[top].node->leftChild != NULL && Stack[top].phase < 1) {
            Stack[top].phase = 1;
            push(Stack[top].node->leftChild, 0);
            continue;
        } // phase 1 end;

        if (Stack[top].phase < 2) {
            printf("%c", Stack[top].node->data);
            Stack[top].phase = 2;
        } // phase 2 end;       // nomal code

        if (Stack[top].node->rightChild != NULL && Stack[top].phase < 3) {
            Stack[top].phase = 3;
            push(Stack[top].node->rightChild, 0);
            continue;
        } // phase 2 end;

        pop();
    }
}


int main() {
    Node* root = makeEXTree();
    
    inorder(root);
    printf("\n");
    iter_inorder(root);

    return 0;
}

Node* makeEXTree() {
    Node* root = newNode('+');
    root->leftChild = newNode('*');
    root->rightChild = newNode('E');

    root->leftChild->leftChild = newNode('*');
    root->leftChild->rightChild = newNode('D');

    root->leftChild->leftChild->leftChild = newNode('/');
    root->leftChild->leftChild->rightChild = newNode('C');

    root->leftChild->leftChild->leftChild->leftChild = newNode('A');
    root->leftChild->leftChild->leftChild->rightChild = newNode('B');

    return root;
}