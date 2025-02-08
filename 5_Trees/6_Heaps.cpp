//편의상 해당 코드부터 c++을 사용하여 구현합니다.
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


//일단 자료형 int로 만들고, templet과 Key를 넣어서 범용적이게 수정할 것.
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

    }

    bool empty() {

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
    h.push(14);
    h.push(15);
    h.push(20);
    h.push(2);
    h.push(10);

    h.printHeap();

    h.push(21);

    h.printHeap();


    return 0;
}