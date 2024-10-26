//일단 작동은 함.
//예제 코드와 비교 필요
// 이제 실제 숫자를 넣어서 계산시켜보자.

//어제 비교 결과 코드 로직은 비슷함. 우선 순위를 결정하는 방법이 나랑 달랐음. 생각보다 신박했다. enum으로 순서 인덱스를 생성해서 하는 것이 나의 compare함수랑 비슷했음.

//추가로 계산 결과를 만드는 식을 작성해보자. 숫자는 한자리 수만 존재한다고 가정함.

//코드 재사용성을 고려 안하고 만들어서 가독성 떨어짐. ex) 스택의 세부 기능 분리 안했음

#include <stdio.h>
#include <string.h>

#define MULTI 1
#define SUM 0
#define ISP -1
#define ICP 5       //연산자 마다 가중치를 두었음 Parethensis의 연산자로 ISP는 In Stack Precedenc, ICP는 In Comming Precedenc임.

char stack[20];
int top = -1;

char out_exp[20];
int out_top = -1;

int compare(char a) {
    if (a == '+' || a == '-') {
        return SUM;
    }
    else if (a == '*' || a == '/' || a == '%') {
        return MULTI;
    }
    else if (a == '(') {
        return ICP;
    }
    else if (a == ')') {
        return ISP;
    }
    return 9;       //error!
}

void gostack(char a) {      //연산자의 스택에 넣을지 말지 결정 & 출력

    if (top == -1) {        //is empty?
        stack[top + 1] = a;     //push!
        top++;
        return;
    }

    for (; top >= 0 && compare(a) <= compare(stack[top]);) {    //비교 후 우선순위가 높지 않은 연산자를 pop
        out_exp[out_top + 1] = stack[top];
        out_top++;
        top--;      // pop and out
    }

    if (a == '(') {
        stack[top + 1] = ')';   // in stack, its precedence is lowest;
        top++;
    }
    else {
        stack[top + 1] = a;
        top++;   
    }

}

void popPare() {
    for (; stack[top] != ')'; top--) {
        out_exp[out_top + 1] = stack[top];
        out_top++;
    }
    top--;  //delete ')'
}

void popAll() {
    for (; top != -1; top--) {
        out_exp[out_top + 1] = stack[top];
        out_top++;
    }
}

void evaluate(char a) {
    switch (a) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '(':
        gostack(a);
        break;
    case ')':
        popPare();
        break;
    case '\0':
        popAll();
        out_exp[out_top + 1] = '\0';
        out_top++;
        break;
    default:
        out_exp[out_top + 1] = a;
        out_top++;        
    }
}

int int_stack[20];
int int_top = -1;

int operatePostfix() {
    for (int i = 0; i < out_top; i++) {
        switch (out_exp[i]) {
        case '+':
            int_stack[int_top - 1] += int_stack[int_top];
            int_top--;
            break;
        case '-':
            int_stack[int_top - 1] -= int_stack[int_top];
            int_top--;
            break;
        case '/':
            int_stack[int_top - 1] /= int_stack[int_top];
            int_top--;
            break;
        case '*':
            int_stack[int_top - 1] *= int_stack[int_top];
            int_top--;
            break;
        case '%':
            int_stack[int_top - 1] %= int_stack[int_top];
            int_top--;
            break;
        default:
            int_stack[++int_top] = out_exp[i] - 48;
        }
        
    }


    return int_stack[int_top];
}

int main() {
    freopen("4_testcase.txt", "r", stdin);

    char exp[20];
    scanf("%s", exp);

    for (int i = 0; i < strlen(exp) + 1; i++) {
        evaluate(exp[i]);
    }

    printf("%s\n", out_exp);
    printf("%d", operatePostfix());



    return 0;
}