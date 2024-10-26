//https://blog.naver.com/kartmon/221525839270
//https://intelligentcm.tistory.com/123

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100    //최대 메모리 공간
#define MAX_STACK 4     //만들 수 있는 스택의 개수

int n;      //만들 스택의 개수
int stack[MAX_SIZE];    //스택 메모리

int top[MAX_STACK];     //스택의 top위치
int boundary[MAX_STACK];//스택의 최하단 원소 위치 즉, 경계

bool isFull(int a) {       //a번째 스택이 가득 찼는지 확인
    if (top[a] == boundary[a + 1]) return true;
    else return false;
}

//나머지 기능은 위를 참고하여 작성

int main() {        //스택 생성

    n = 4;

    //make first stack
    top[0] = boundary[0] = -1;

    //n-1개의 스택 생성
    for (int i = 1; i < n; i++) {
        top[i] = boundary[i] = MAX_SIZE / n * i;
    }

    boundary[n] = MAX_SIZE - 1;


    return 0;
}