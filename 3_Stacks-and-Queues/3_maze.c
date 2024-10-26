#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE_MAZE 100
#define MAX_SIZE_STACK 1000

typedef struct Pair {
    int front;
    int back;
} Pair;

typedef struct Maze {
    int m, n;
    Pair entrancePoint;
    Pair exitPoint;

    char map[MAX_SIZE_MAZE][MAX_SIZE_MAZE];

} Maze;

typedef struct PathMarker {
    int row;
    int col;
    int dir;    // 0부터 7까지 -> 12시부터 시계방향
    
} PathMarker;

typedef struct PathStack {
    int top;
    PathMarker stack[MAX_SIZE_STACK];

} PathStack;

PathStack* initStack();
bool isFull(PathStack*);
bool isEmpty(PathStack*);
void push(PathStack*, int, int, int);
void pop(PathStack*);
PathMarker back(PathStack*);

Maze* initMaze();
int findPathhhh(PathStack*, Maze*);    //return 0: failed, 1: successed;
void printPathh(PathStack*);


int main() {
    freopen("3_testcase.txt", "r", stdin);
    
    Maze* maze = initMaze();
    PathStack* stack = initStack();

    if (findPathhhh(stack, maze)) {
        printf("find Path!\n");
        printPathh(stack);
    }
    else {
        printf("There is no path to exit!\n");
    }


    return 0;
}

Maze* initMaze() {
    Maze* maze = (Maze*)malloc(sizeof(Maze));
    scanf("%d %d", &maze->m, &maze->n);
    
    for (int i = 0; i < maze->m; i++) {
        scanf("%s", maze->map[i]);
    }
    
    maze->entrancePoint.front = maze->entrancePoint.back = 1;
    maze->exitPoint.front = maze->m - 2;
    maze->exitPoint.back = maze->n - 2;

    return maze;
}

PathStack* initStack() {
    PathStack* stack = (PathStack*)malloc(sizeof(PathStack));
    stack->top = 0;

    return stack;
}

bool isFull(PathStack* s) {
    return s->top > MAX_SIZE_STACK ? true : false;
}

bool isEmpty(PathStack* s) {
    return s->top == 0 ? true : false;
}

void push(PathStack* s, int r, int c, int d) {
    if (isFull(s)) {
        fprintf(stderr, "Stack is full!");
        exit(1);
    }
    PathMarker tmpdata;
    tmpdata.row = r;
    tmpdata.col = c;
    tmpdata.dir = d;

    s->stack[s->top] = tmpdata;
    s->top++;
}

void pop(PathStack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack is Empty");
        exit(1);
    }
    s->top--;
}

PathMarker back(PathStack* s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack is Empty bro...");
        exit(1);
    }
    return s->stack[s->top - 1];
}


int findPathhhh(PathStack* stack, Maze* maze) {
    
    maze->map[1][1] = '1';
    push(stack, 1, 1, 0);

    for (; ;) {
        if (isEmpty(stack)) return 0;

        PathMarker tmpPath = back(stack);

        if (tmpPath.row == maze->exitPoint.front && tmpPath.col == maze->exitPoint.back) {
            return 1;
        }

        if (tmpPath.dir == 0) {
            if (maze->map[tmpPath.row - 1][tmpPath.col] == '0') {
                push(stack, tmpPath.row - 1, tmpPath.col, 0);
                maze->map[tmpPath.row - 1][tmpPath.col] = '1';
            }
            else {
                stack->stack[stack->top - 1].dir++;
            }
            continue;
        }
        else if (tmpPath.dir == 1) {
            if (maze->map[tmpPath.row - 1][tmpPath.col + 1] == '0') {
                push(stack, tmpPath.row - 1, tmpPath.col + 1, 0);
                maze->map[tmpPath.row - 1][tmpPath.col + 1] = '1';
            }
            else {
                stack->stack[stack->top - 1].dir++;
            }
            continue;
        }
        else if (tmpPath.dir == 2) {
            if (maze->map[tmpPath.row][tmpPath.col + 1] == '0') {
                push(stack, tmpPath.row, tmpPath.col + 1, 0);
                maze->map[tmpPath.row][tmpPath.col + 1] = '1';
            }
            else {
                stack->stack[stack->top - 1].dir++;
            }
            continue;
        }
        else if (tmpPath.dir == 3) {
            if (maze->map[tmpPath.row + 1][tmpPath.col + 1] == '0') {
                push(stack, tmpPath.row + 1, tmpPath.col + 1, 0);
                maze->map[tmpPath.row + 1][tmpPath.col + 1] = '1';
            }
            else {
                stack->stack[stack->top - 1].dir++;
            }
            continue;
        }
        else if (tmpPath.dir == 4) {
            if (maze->map[tmpPath.row + 1][tmpPath.col] == '0') {
                push(stack, tmpPath.row + 1, tmpPath.col, 0);
                maze->map[tmpPath.row + 1][tmpPath.col] = '1';
            }
            else {
                stack->stack[stack->top - 1].dir++;
            }
            continue;
        }
        else if (tmpPath.dir == 5) {
            if (maze->map[tmpPath.row + 1][tmpPath.col - 1] == '0') {
                push(stack, tmpPath.row + 1, tmpPath.col - 1, 0);
                maze->map[tmpPath.row + 1][tmpPath.col - 1] = '1';
            }
            else {
                stack->stack[stack->top - 1].dir++;
            }
            continue;
        }
        else if (tmpPath.dir == 6) {
            if (maze->map[tmpPath.row][tmpPath.col - 1] == '0') {
                push(stack, tmpPath.row, tmpPath.col - 1, 0);
                maze->map[tmpPath.row][tmpPath.col - 1] = '1';
            }
            else {
                stack->stack[stack->top - 1].dir++;
            }
            continue;
        }
        else if (tmpPath.dir == 7) {
            if (maze->map[tmpPath.row - 1][tmpPath.col - 1] == '0') {
                push(stack, tmpPath.row - 1, tmpPath.col - 1, 0);
                maze->map[tmpPath.row - 1][tmpPath.col - 1] = '1';
            }
            else {
                stack->stack[stack->top - 1].dir++;
            }
            continue;
        }
        else {
            pop(stack);
        }
    }
}

void printPathh(PathStack* stack) {
    for (int i = 0; i < stack->top; i++) {
        PathMarker tmp = stack->stack[i];
        printf("[%d, %d] ", tmp.row, tmp.col);
    }
}