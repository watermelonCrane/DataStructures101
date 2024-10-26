//Done!!

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Customer {
    char name[21];
    char phone[14];
    char course_code;

    union {
        float record;
        int score;
        bool back_bone;
    };

} Customer;

void inputCustomer(Customer[]);
void printNumberoM(Customer[], int[]);
int numberoM(Customer[], char, int[]);
void printFastestSwimer(Customer[], int[]);
void printAverageSwimLog(Customer[], int[]);
void printLowestGolfer(Customer[], int[]);
void printAverageGolfscore(Customer[], int[]);
void printNumberofBackBone(Customer[], int[]);

int main() {

    freopen("1_testcase.txt", "r", stdin);

    Customer customer[100];
    int numberCustomer[3]; // g, w, y;

    inputCustomer(customer);

    printNumberoM(customer, numberCustomer);
    printFastestSwimer(customer, numberCustomer);
    printAverageSwimLog(customer, numberCustomer);
    printLowestGolfer(customer, numberCustomer);
    printAverageGolfscore(customer, numberCustomer);
    printNumberofBackBone(customer, numberCustomer);


    return 0;
}


//회원님들 입력 함수
void inputCustomer(Customer customer[]) {
    for (int i = 0; ; i++) {
        char name[21];

        scanf("%s", name);

        strcpy(customer[i].name, name);

        if (!strcmp(name, "end")) break;  //입력 종료 조건

        scanf("%s", customer[i].phone);
        scanf(" %c", &customer[i].course_code);
        
        switch (customer[i].course_code) {
        case 'S':
            scanf("%f", &customer[i].record);
            break;
        case 'G':
            scanf("%d", &customer[i].score);
            break;
        case 'Y':
            char TorF[10];
            scanf("%s", TorF);
            if (!strcmp(TorF, "TRUE")) {
                customer[i].back_bone = true;
            }
            else {
                customer[i].back_bone = false;
            }
            break;
        default:
            printf("this is not registered code in system.\n");
            return;
        }
    }
}

void printNumberoM(Customer customer[], int numberCustomer[]) {
    printf("Swim Course: %d\n", numberoM(customer, 'S', numberCustomer));
    printf("Golf Course: %d\n", numberoM(customer, 'G', numberCustomer));
    printf("Yoga Course: %d\n\n", numberoM(customer, 'Y', numberCustomer));    
}

int numberoM(Customer customer[], char code, int numberCustomer[]) {
    int sum = 0;

    for (int i = 0; strcmp(customer[i].name, "end"); i++) {
        if (customer[i].course_code == code) sum++;
    }

    switch (code) {
        case 'G':
            numberCustomer[0] = sum;
            break;
        case 'S':
            numberCustomer[1] = sum;
            break;
        case 'Y':
            numberCustomer[2] = sum;
            break;
    }

    return sum;
}

void printFastestSwimer(Customer customer[], int numberCustomer[]) {
    if (!numberCustomer[1]) return;

    float result = 1000;
    char name[21];

    for (int i = 0; strcmp(customer[i].name, "end"); i++) {
        if (customer[i].course_code != 'S') continue;
        if (customer[i].record < result) {
            strcpy(name, customer[i].name);
            result = customer[i].record;
        }
    }

    printf("최고 수영 실력자 : %s %.1f초\n", name, result);
}


void printAverageSwimLog(Customer customer[], int numberCustomer[]) {
    if (!numberCustomer[1]) return;

    float sum = 0;
    int count = 0;

    for (int i = 0; strcmp(customer[i].name, "end"); i++) {
        if (customer[i].course_code != 'S') continue;
        sum += customer[i].record;
        count++;
    }

    printf("수영 평균 기록: %.1f초\n", sum / count);

}

void printLowestGolfer(Customer customer[], int numberCustomer[]) {
    if (!numberCustomer[0]) return;

    int result = 1000;
    char name[21];

    for (int i = 0; strcmp(customer[i].name, "end"); i++) {
        if (customer[i].course_code != 'G') continue;
        if (customer[i].score < result) {
            strcpy(name, customer[i].name);
            result = customer[i].score;
        }
    }

    printf("골프 최저타 기록 보유자: %s %d타\n", name, result);
}

void printAverageGolfscore(Customer customer[], int numberCustomer[]) {
    if (!numberCustomer[0]) return;

    int count = 0;
    int sum = 0;
    for (int i = 0; strcmp(customer[i].name, "end"); i++) {
        if (customer[i].course_code != 'G') continue;
        count++;
        sum += customer[i].score;
    }

    printf("골프 평균 타수: %d타\n", sum / count);

}

void printNumberofBackBone(Customer customer[], int numberCustomer[]) {
    if (!numberCustomer[2]) return;

    int count = 0;
    for (int i = 0; strcmp(customer[i].name, "end"); i++) {
        if (customer[i].course_code != 'Y') continue;
        if (customer[i].back_bone == true) count++;
    }

    printf("요가 척추질환 보유자 %d명\n", count);
}