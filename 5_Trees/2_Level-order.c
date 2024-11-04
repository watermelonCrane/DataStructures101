/***************
 * 여기서 잠깐! 왜 int형 큐가 구현되어있는지 궁금해 할 수 있어!
 * 그건바로 내가 멍청하게도 사용할 줄 알고 만들어놨는데 안쓰게 되어서 그런거야!
 * 만들었는데 바로 지우기에 아까워서 놔두었어!
 * 그럼 즐코!(즐거운 코딩이라는 뜻 ㅎ)
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    Node* leftchild;
    Node* rightchild;
} Node;

//define int_queue and Node_pointer_queue
#define MAX_Q 10

//define int_queue
int INT_Q[MAX_Q];
int INT_front = 0;
int INT_rear = 0;

void INT_push(int data);
int INT_pop();
bool INT_isFull();
bool INT_isEmpty();
void INT_init();
//      end define int_queue


//define Node_pointer_queue
Node* NP_Q[MAX_Q];
int NP_front = 0;
int NP_rear = 0;

void NP_push(Node* NP);
Node* NP_pop();
bool NP_isFull();
bool NP_isEmpty();
void NP_init();
//      end define Node_pointer_queue
//          end define int_queue and Node_pointer_queue

//level order function
Node* makeTree(int inputData[]);
void printLevelOrder(Node* treeRoot);
Node* newNode(int data);
//      end levelorder function


int main() {
    int inputData[] = {1, 2, 3, 4, 5, 6, 7, 8};     // 원소개수 8개

    Node* newTree = makeTree(inputData);

    printLevelOrder(newTree);

    return 0;
}

Node* makeTree(int inputData[]) {
    NP_init();

    Node* root = newNode(inputData[0]);
    NP_push(root);
    
    for (int i = 1; i < 8; i++) {   //  원소개수는 일단 8로 고정됨
        Node* tmp = newNode(inputData[i]);
        NP_push(tmp);
        if (NP_Q[NP_front]->leftchild == NULL) {
            NP_Q[NP_front]->leftchild = tmp;
            continue;
        }
        if (NP_Q[NP_front]->rightchild == NULL) {
            NP_Q[NP_front]->rightchild = tmp;
            NP_pop();
            continue;
        }
    }

    return root;
}

void printLevelOrder(Node* treeRoot) {
    NP_init();

    printf("%d ", treeRoot->data);
    NP_push(treeRoot);

    for (; NP_isEmpty() == false;) {
        Node* tmp = NP_pop();
        if (tmp->leftchild != NULL) {
            NP_push(tmp->leftchild);
            printf("%d ", tmp->leftchild->data);
        }
        if (tmp->rightchild != NULL) {
            NP_push(tmp->rightchild);
            printf("%d ", tmp->rightchild->data);
        }
    }

}

Node* newNode(int data) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = data;
    tmp->leftchild = NULL;
    tmp->rightchild = NULL;

    return tmp;
}


void INT_push(int data) {
    if (INT_isFull() == true) {
        fprintf(stderr, "INT_Q is Full\n");
        exit(1);
    }
    INT_Q[INT_rear] = data;
    INT_rear++;
    INT_rear %= MAX_Q;  //adjust index number for q size;
}

int INT_pop() {
    if (INT_isEmpty() == true) {
        fprintf(stderr, "INT_Q is empty\n");
        exit(1);
    }
    int tmp = INT_Q[INT_front];
    INT_front++;
    INT_front %= MAX_Q; // adjust same as above;

    return tmp;
}

bool INT_isFull() {
    if ((INT_rear + 1) % MAX_Q == INT_front) return true;
    else return false;
}
bool INT_isEmpty() {
    if (INT_front == INT_rear) return true;
    else return false;
}

void INT_init() {
    INT_front = INT_rear = 0;
}

void NP_push(Node* NP) {
    if (NP_isFull() == true) {
        fprintf(stderr, "NP_Q is Full\n");
        exit(1);
    }
    NP_Q[NP_rear] = NP;
    NP_rear++;
    NP_rear %= MAX_Q;
}

Node* NP_pop() {
    if (NP_isEmpty() == true) {
        fprintf(stderr, "NP_Q is empty\n");
        exit(1);
    }
    Node* tmp = NP_Q[NP_front];
    NP_front++;
    NP_front %= MAX_Q;

    return tmp;
}

bool NP_isFull() {
    if ((NP_rear + 1) % MAX_Q == NP_front) return true;
    else return false;
}

bool NP_isEmpty() {
    if (NP_front == NP_rear) return true;
    else return false;
}

void NP_init() {
    NP_front = NP_rear = 0;
}