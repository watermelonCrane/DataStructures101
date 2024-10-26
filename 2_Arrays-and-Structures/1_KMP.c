//성공~!

#include <stdio.h>
#include <string.h>

// https://injae-kim.github.io/dev/2020/07/23/all-about-kmp-algorithm.html

void makeFailure(char pat[], int failure[]) {
    for (int i = 0, k = -1; i < strlen(pat); i++) {
        if (i == 0 || pat[i] == pat[k]) {
            failure[i] = k;
            k++;
        }
        else if (k != 0) {      // 이 부분이 왜 필요했는지 생각해보자. "ababaa"패턴에서 이 조건문을 뺀다면?
            k = 0;
            i--;
        }
        else {
            k = -1;
            failure[i] = k;
            k++;
        }
    }

}

int kmp(char str[], char pat[]) {
    int failure[20];
    makeFailure(pat, failure);
    
    int lens = strlen(str);
    int lenp = strlen(pat);

    for (int i = 0, k = 0; i < lens && k < lenp; ) {
        if (str[i] == pat [k]) {
            i++;
            k++;
        }
        else if (k == 0) {
            i++;
        }
        else {
            k = failure[k - 1] + 1;
        }

        if (k == lenp) return i - lenp;

    }

    return -1;

}

int main() {

    freopen("1_testcase.txt", "r", stdin);

    char str[2000];
    char pat[20];
    scanf("%s", str);
    scanf("%s", pat);

    int result = kmp(str, pat);
    printf("%d", result);

    return 0;
}