#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
    int data;
    struct Element* link;
} Element;

void pushElement(int data, Element** head) {        //data를 head가 포함된 리스트의 맨 뒤에 붙이는 함수
    Element* tmp = (Element*)malloc(sizeof(Element));
    tmp->data = data;
    tmp->link = NULL;

    if (*head) {
        for (; (*head)->link != NULL; *head = (*head)->link)
        (*head)->link = tmp;
    }
    else {
        *head = tmp;
    }
}

void insertList(Element* front, Element* insert_list_head) {       //front뒤에 새로운 리스트를 추가하는 함수 원래 front뒤에 있던 원소들은 새로운 리스트 뒤로 감
    Element* back = front->link;
    front->link = insert_list_head;

    for (; insert_list_head->link != NULL; insert_list_head = insert_list_head->link);
    insert_list_head->link = back;
}

void deleteElement(Element* f_element) {        //f_element가 NULL이라면 맨 앞의 원소를 삭제

    Element* d_element = f_element->link;
    f_element->link = d_element->link;
    free(d_element);

}

Element* makeEXList() {     //각 원소가 0부터 9를 갖는 리스트의 헤드 리턴
    Element* head = NULL;
    Element* iter = NULL;
    for (int i = 0; i < 10; i++) {
        Element* tmp = (Element*)malloc(sizeof(Element));
        tmp->data = i;
        tmp->link = NULL;

        if (iter) {
            iter->link = tmp;
            iter = iter->link;
        }
        else {
            head = tmp;
            iter = tmp;
        }
    }

    return head;
}

int main() {

    Element* list_1 = makeEXList();
    Element* list_2 = makeEXList();

    Element* iter = list_1;
    for (int i = 0; i < 3; i++) {
        iter = iter->link;
    }

    insertList(iter, list_2);
    iter = iter->link;
    deleteElement(iter);


    //https://developing-sunny.tistory.com/12   뭐 나중에 참고하던가.
    //https://velog.io/@woojinn8/%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0-Linked-List

    return 0;
}