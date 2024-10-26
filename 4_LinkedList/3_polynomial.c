#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode {
    int coef;
    int expon;
    struct PolyNode* link;
} PolyNode;


int compareNode(PolyNode* a, PolyNode* b) {
    if (a->expon == b->expon) {
        return 0;       // equal! go to add;
    }
    else if (a->expon > b->expon) {
        return -1;      // a is big; -> attatch (a)
    }
    else if (a->expon < b->expon) {
        return 1;       // b is big; go attatch (b)
    }

    fprintf(stderr, "compareNode() error!");        //에러 검사
    exit(1);
}

void attach(PolyNode** to, PolyNode** from) {      //to의 link를 from을 가리키게      <- 지금보니까 반대로 작성한거 아님?
    (*to)->link = *from;
    (*to) = (*to)->link;
}

PolyNode* pAdd(PolyNode* a, PolyNode* b) {
    PolyNode* c = (PolyNode*)malloc(sizeof(PolyNode));        //결과 값, 식의 헤드

    PolyNode* pc = c;       // c의 node를 포인팅

    while (a != NULL && b != NULL) {
        PolyNode* tmp = (PolyNode*)malloc(sizeof(PolyNode));  //node를 복사할 임시 저장공간
        tmp->link = NULL;

        switch (compareNode(a, b)) {
        case -1:
            tmp->coef = a->coef;
            tmp->expon = a->expon;
            attach(&pc, &tmp);
            a = a->link;        //a만 다음 노드를 포인팅
            break;
        case 0:
            tmp->coef = a->coef + b->coef;
            tmp->expon = a->expon;
            attach(&pc, &tmp);
            a = a->link;
            b = b->link;
            break;
        case 1:
            tmp->coef = b->coef;
            tmp->expon = b->expon;
            attach(&pc, &tmp);
            b = b->link;        //b만 다음 노드를 포인팅
            break;
        }
    }

    // a나 b의 남아있는 노드를 c 뒤에다가 가져다가 붙이기
    if (a != NULL) {
        while (a != NULL) {
            PolyNode* tmp = (PolyNode*)malloc(sizeof(PolyNode));
            tmp->coef = a->coef;
            tmp->expon = a->expon;
            attach(&pc, &tmp);
            pc = pc->link;
            a = a->link;
        }
    }
    else if (b != NULL) {
        while (b != NULL) {
            PolyNode* tmp = (PolyNode*)malloc(sizeof(PolyNode));
            tmp->coef = b->coef;
            tmp->expon = b->expon;
            attach(&pc, &tmp);
            pc = pc->link;
            b = b->link;
        }
    }
    else {
        fprintf(stderr, "왜 여기서 에러가 발생했지?? while문이 제대로 작동했으면 에러가 발생하면 안됨;;");
        exit(1);
    }

    //c의 대가리 삭제
    PolyNode* tmp = c;
    c = c->link;
    free(tmp);

    return c;
}

int main() {

    /********
     * a = 3x^14 + 2x^8 + 1
     * b = 8x^14 - 3x^10 + 10x^6
     * 을 만들어서 계산값은 c = a + b 로 빼는 코드임
     **************/

    PolyNode* tmp = NULL;
    PolyNode* a = NULL;
    PolyNode* b = NULL;
    PolyNode* c = NULL;

    //make a
    a = (PolyNode*)malloc(sizeof(PolyNode));
    a->coef = 3;
    a->expon = 14;
    PolyNode* head_a = a;

    tmp = (PolyNode*)malloc(sizeof(PolyNode));
    tmp->coef = 2;
    tmp->expon = 8;
    attach(&a, &tmp);

    tmp = (PolyNode*)malloc(sizeof(PolyNode));
    tmp->coef = 1;
    tmp->expon = 0;
    tmp->link = NULL;
    attach(&a, &tmp);

    //make b
    b = (PolyNode*)malloc(sizeof(PolyNode));
    b->coef = 8;
    b->expon = 14;
    PolyNode* head_b = b;

    tmp = (PolyNode*)malloc(sizeof(PolyNode));
    tmp->coef = -3;
    tmp->expon = 10;
    attach(&b, &tmp);

    tmp = (PolyNode*)malloc(sizeof(PolyNode));
    tmp->coef = 10;
    tmp->expon = 6;
    tmp->link = NULL;
    attach(&b, &tmp);

    c = pAdd(head_a, head_b);
    

    return 0;
}