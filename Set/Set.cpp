#include <iostream>
#include "Windows.h"

using namespace std;

class Set {
    int* set;
    int size;
public:
    Set(int* setInput, int sizeInput) : set{ new int[sizeInput] }, size{ sizeInput }
    {
        for (int i = 0; i < size; i++) {
            set[i] = setInput[i];
        }
    }

    Set(const Set& object) : set{ new int[object.size] }, size{ object.size }
    {
        for (int i = 0; i < size; i++) {
            set[i] = object.set[i];
        }
    }

    Set() : Set(nullptr, size) {}

    Set& operator=(const Set& name) {
        if (this == &name) return *this;
        delete[] set;
        size = name.size;
        set = new int[size];
        for (int i = 0; i < size; i++) {
            set[i] = name.set[i];
        }
        return *this;
    }

    int* getSet() const {
        return set;
    }

    int getSize() const {
        return size;
    }

    bool isBelong(int element) const {
        for (int i = 0; i < size; i++) {
            if (element == set[i]) return true;
        }
        return false;
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << set[i] << ' ';
        }
        cout << endl;
    }

    friend Set operator+(const Set& setInput, int element);
    friend Set operator+(int element, const Set& setInput);
    friend Set operator+(const Set& setInput1, const Set& setInput2);
    friend Set operator-(const Set& setInput, int element);
    friend Set operator-(const Set& setInput1, const Set& setInput2);
    friend Set operator*(const Set& setInput1, const Set& setInput2);
    friend Set operator==(const Set& setInput1, const Set& setInput2);

    ~Set() {
        delete[] set;
    }
};

Set operator+(const Set& setInput, int element) {
    if (!setInput.isBelong(element)) {
        int* newSet = new int[setInput.getSize() + 1];
        for (int i = 0; i < setInput.getSize(); i++) {
            newSet[i] = setInput.getSet()[i];
        }
        newSet[setInput.getSize()] = element;
        return Set(newSet, setInput.getSize() + 1);
    }
    return setInput;
}
Set operator+(int element, const Set& setInput) {
    if (!setInput.isBelong(element)) {
        int* newSet = new int[setInput.getSize() + 1];
        newSet[0] = element;
        for (int i = 1; i < setInput.getSize() + 1; i++) {
            newSet[i] = setInput.getSet()[i-1];
        }
        return Set(newSet, setInput.getSize() + 1);
    }
    return setInput;
}
Set operator+(const Set& setInput1, const Set& setInput2) {
    int* newSetAr = new int[setInput1.getSize() + setInput2.getSize()];
    Set newSet(newSetAr, setInput1.getSize() + setInput2.getSize());
    int index = 0;
    for (int i = 0; i < setInput1.getSize(); i++) {
        if (!newSet.isBelong(setInput1.set[i])) {
            newSet.set[index] = setInput1.set[i];
            index++;
        }
    }
    for (int i = 0; i < setInput2.getSize(); i++) {
        if (!newSet.isBelong(setInput2.set[i])) {
            newSet.set[index] = setInput2.set[i];
            index++;
        }
    }
    newSet.size = index;
    return newSet;
}
Set operator-(const Set& setInput, int element) {
    if (setInput.isBelong(element)) {
        int* newSet = new int[setInput.getSize() - 1];
        int j = 0;
        for (int i = 0; i < setInput.getSize(); i++) {
            if (setInput.set[i] != element) {
                newSet[j] = setInput.set[i];
                j++;
            }
        }
        return Set(newSet, setInput.getSize() - 1);
    }
    return setInput;
}
Set operator-(const Set& setInput1, const Set& setInput2) {
    int* newSetAr = new int[setInput1.getSize()];
    Set newSet(newSetAr, setInput1.getSize());
    int index = 0;
    for (int i = 0; i < setInput1.getSize(); i++) {
        if (!setInput2.isBelong(setInput1.set[i]) && !newSet.isBelong(setInput1.set[i])) {
            newSet.set[index] = setInput1.set[i];
            index++;
        }
    }
    newSet.size = index;
    return newSet;
}
Set operator*(const Set& setInput1, const Set& setInput2) {
    int* newSetAr = new int[setInput1.getSize()];
    Set newSet(newSetAr, setInput1.getSize());
    int index = 0;
    for (int i = 0; i < setInput1.getSize(); i++) {
        if (setInput2.isBelong(setInput1.set[i]) && !newSet.isBelong(setInput1.set[i])) {
            newSet.set[index] = setInput1.set[i];
            index++;
        }
    }
    newSet.size = index;
    return newSet;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int size1 = 4;
    int size2 = 9;
    int* ar1 = new int[size1] { 23, 45, 12, 28 };
    int* ar2 = new int[size1] { 23, 13, 45, 897, 12, 28, 189, 67, 34};
    Set set1{ ar1, 4 };
    Set set2{ set1 };
    Set set3{ ar2, size2 };

    set1.print();
    set1 = 3 + set1 + 8;
    set1.print();
    set1 = set1 + set2;
    set1.print();
    set2 = set2 - 45;
    set2.print();
    set3 = set3 - set1;
    set3.print();
    set1 = set1 * set2;
    set1.print();
    delete[] ar1;
};
