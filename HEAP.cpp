#include <iostream>
using namespace std;

const int MAX = 100;

class MarksHeap {
    int maxHeap[MAX];  // Max-heap for maximum marks
    int minHeap[MAX];  // Min-heap for minimum marks
    int size;

    void maxHeapifyUp(int index) {
        while (index > 0 && maxHeap[(index - 1) / 2] < maxHeap[index]) {
            int temp = maxHeap[(index - 1) / 2];
            maxHeap[(index - 1) / 2] = maxHeap[index];
            maxHeap[index] = temp;
            index = (index - 1) / 2;
        }
    }

    void minHeapifyUp(int index) {
        while (index > 0 && minHeap[(index - 1) / 2] > minHeap[index]) {
            int temp = minHeap[(index - 1) / 2];
            minHeap[(index - 1) / 2] = minHeap[index];
            minHeap[index] = temp;
            index = (index - 1) / 2;
        }
    }

public:
    MarksHeap() {
        size = 0;
    }

    void insertMark(int mark) {
        if (size >= MAX) {
            cout << "Heap is full!" << endl;
            return;
        }

        maxHeap[size] = mark;
        minHeap[size] = mark;

        maxHeapifyUp(size);
        minHeapifyUp(size);

        size++;
    }

    int getMax() {
        if (size == 0) return -1;
        return maxHeap[0];
    }

    int getMin() {
        if (size == 0) return -1;
        return minHeap[0];
    }

    void inputMarks() {
        int n, mark;
        cout << "Enter number of students: ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "Enter marks for student " << (i + 1) << ": ";
            cin >> mark;
            insertMark(mark);
        }
    }

    void showMaxMin() {
        if (size == 0) {
            cout << "No marks entered yet.\n";
            return;
        }
        cout << "Maximum marks: " << getMax() << endl;
        cout << "Minimum marks: " << getMin() << endl;
    }
};

int main() {
    MarksHeap mh;
    mh.inputMarks();
    mh.showMaxMin();
    return 0;
}
