//편의상 해당 코드부터 c++을 사용하여 구현합니다.
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//인덱싱은 구현 안할 것임.
//vector 기반이므로 full() method 불필요.
class MaxHeap {
private:
    vector<int> tree;

public:

    MaxHeap() {
        tree.resize(1);    //index: 1은 사용하지 않음.
    }

    void push(int data) {
        tree.push_back(data);
        for (int i = tree.size() - 1; i != 1 && data > tree[i / 2]; i /= 2) {
            tree[i] = tree[i / 2];
            tree[i / 2] = data;
        }
    }

    int pop() {
        if (empty()) throw runtime_error("Heap is empty!");     // 비어있으면 에러 발생

        int result = tree[1];

        tree[1] = tree.back();
        tree.pop_back();

        for (int i = 1; i * 2 <= tree.size() - 1; ) {   // 자식이 존재하는 동안 반복
            if (tree[i] > tree[i * 2] && tree[i] > tree[i * 2 + 1]) break;
            if (i * 2 == tree.size() - 1 || tree[i * 2] > tree[i * 2 + 1]) {    // LeftChild 만 존재하거나 LeftChild가 RightChild보다 클 경우
                int tmp = tree[i * 2];
                tree[i * 2] = tree[i];
                tree[i] = tmp;
                i *= 2;
            }
            else {  // Right Child가 더 크거나 같을 경우
                int tmp = tree[i * 2 + 1];
                tree[i * 2 + 1] = tree[i];
                tree[i] = tmp;
                i *= 2;
                i++;
            }
        }

        return result;
    }

    bool empty() {
        if (tree.size() == 1) return true;
        else return false;
    }

    void printHeap() {
        cout << '\n';
        int h = 1;
        for (int i = 1; i < tree.size(); i++) {
            if (h != ceil(log2(i + 1))) {
                cout << '\n';
                h = ceil(log2(i + 1));
            }
            cout << tree[i] << ' ';
        }
    }
};

int main() {
    MaxHeap h;
    
    h.push(6);
    h.push(2);
    h.push(3);
    h.push(1);
    h.push(0);

    h.printHeap();
    

    cout << '\n';
    for (; !h.empty();) {
        cout << h.pop() << ' ';
    }



    return 0;
}