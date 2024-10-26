#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* link;
} Node;

Node* newNode(int data) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = data;
    tmp->link = NULL;
    return tmp;
}

Node* invertList(Node* head) {
    Node* tmp = NULL;
    Node* tail = NULL;
    for (; head != NULL;) {
        tmp = head->link;
        head->link = tail;
        tail = head;
        head = tmp;
    }
    return tail;
}

int main() {

    Node* a = newNode(1);
    Node* b = newNode(2);
    Node* c = newNode(3);
    
    a->link = b;
    b->link = c;

    Node* reverse_head = invertList(a);

    return 0;
}