#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 참고글 https://injae-kim.github.io/dev/2020/07/23/all-about-kmp-algorithm.html

int* failure(const char* pat) {
    int patlen = strlen(pat);
    int* pi = (int*)malloc(sizeof(int) * patlen);

    int i, k;   // i: 선행자, k: 후행자
    for (i = k = 0; i < patlen;) {
        if (i == 0) {   // 처음 시작에서 pi[0]을 0으로 두고 시작함.
            pi[i] = 0;
            i++;
        }

        if (pat[i] == pat[k]) {     // 접두사와 접미사가 같다면 pi[i]의 배열에 몇글자가 일치하는지 기록
            pi[i] = k + 1;
            i++;
            k++;
        }
        else if (k == 0) {  // 접두사와 접미사가 끝까지 같지 않다면 pi[i] = 0 으로 설정
            pi[i] = 0;
            i++;
        }
        else {  // 이어지는 접두사와 접미사가 일치하지 않을 때 바로 앞까지 같았던 정보를 참고하여 다시 비교 시작 (kmp와 같은 원리)
            if (k == pi[k]) k--;
            else k = pi[k];
        }

    }

    return pi;
}

int kmp(const char* str, const char* pat) {
    int* pi = failure(pat);
    int patlen = strlen(pat);

    int i, k;       // i: str배열 인덱스 포인팅, k: pat 배열 인덱스 포인팅
    for (i = k = 0; k < patlen;) {
        if (str[i] == pat[k]) {
            i++;
            k++;
        }
        else if (k == 0) {
            i++;
        }
        else {
            k = pi[k - 1];
        }
    }

    if (k >= patlen) {
        return i - k;
    } else return -1;

}

int main() {
    const char* str = "aabcaabcabaabcaad";
    const char* pat = "aabcaad";


    // 패턴 위치 찾기
    int result = kmp(str, pat);


    //결과 출력
    for (int i = result; i < result + strlen(pat); i++) {
        printf("%c", str[i]);
    }



    return 0;
}