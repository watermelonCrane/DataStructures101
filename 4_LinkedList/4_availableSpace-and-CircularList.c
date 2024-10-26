// circularList and getNode, retNode, cerase

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* link;    
} Node;
Node* avail_List = NULL;        // available space list

Node* getNode() {
    Node* tmp = NULL;
    if (avail_List == NULL) {
        tmp = (Node*)malloc(sizeof(Node));
    }
    else {
        tmp = avail_List;
        avail_List = avail_List->link;
    }
    tmp->link = NULL;       // 이거 안해주면 avail_List가 계속 연결된 것이 따라옴
    return tmp;
}

void retNode(Node* node) {
    node->link = avail_List;
    avail_List = node;
}

void cerase(Node** head) {       // list의 길이가 어떻든 고정된 시간 보장.
    Node* tmp = (*head)->link;   //이중 포인터로 가져오는 이유: head의 원본 값을 바꾸기 때문에 NULL로 만들 것인데 그냥 포인터로 가져오면 NULL값으로 바꿀 수 없음. 값복사로 가져온 변수가 되기 때문이다.
    (*head)->link = avail_List;
    avail_List = tmp;
    *head = NULL;
}



int main() {

    //make chain
    Node* testnode = getNode();
    testnode->data = 1;
    testnode->link = getNode();
    testnode->link->data = 2;
    testnode->link->link = getNode();
    testnode->link->link->data = 3;
    testnode->link->link->link = getNode();
    testnode->link->link->link->data = 4;

    // 노드 두개를 지워보자.
    retNode(testnode->link->link->link);
    testnode->link->link->link = NULL;
    retNode(testnode->link->link);
    testnode->link->link = NULL;

    //그 두개를 다시 가져와 보자. 원래 값이 그대로 남아있는걸 알 수 있음.
    testnode->link->link = getNode();
    testnode->link->link->link = getNode();

    testnode->link->link->link->link = testnode;        //make circular list

    cerase(&testnode);

    


    return 0;
}