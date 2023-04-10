#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Student {
public:
    string lastName;
    int grades[3];
    double average;
};

bool compareByThirdGrade(const Student& a, const Student& b) {
    return a.grades[2] > b.grades[2];
}

bool compareByAverage(const Student& a, const Student& b) {
    if (a.grades[2] == b.grades[2]) {
        return a.average > b.average;
    }
    return a.grades[2] > b.grades[2];
}

bool compareByLastName(const Student& a, const Student& b) {
    if (a.grades[2] == b.grades[2] && a.average == b.average) {
        return a.lastName < b.lastName;
    }
    return compareByAverage(a, b);
}

int* buildIndexArray(Student students[], int size) {
    int* indexArray = new int[size];
    for (int i = 0; i < size; i++) {
        indexArray[i] = i;
    }
    sort(indexArray, indexArray + size, [&](int i, int j) {
        return compareByLastName(students[i], students[j]);
        });
    return indexArray;
}

int binarySearch(Student students[], int indexArray[], int size, string lastName, double average, int thirdGrade) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int index = indexArray[mid];
        if (students[index].lastName == lastName && students[index].average == average && students[index].grades[2] == thirdGrade) {
            return index;
        }
        else if (compareByLastName(students[index], { lastName, {0, 0, 0}, average })) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

int main() {
    const int SIZE = 5;
    Student students[SIZE] = {
            { "Smith", {80, 85, 90}, 85 },
            { "Johnson", {90, 80, 85}, 85 },
            { "Williams", {85, 90, 80}, 85 },
            { "Brown", {75, 80, 90}, 81.67 },
            { "Jones", {80, 75, 90}, 81.67 }
    };
    sort(students, students + SIZE, compareByThirdGrade);
    sort(students, students + SIZE, compareByAverage);
    sort(students, students + SIZE, compareByLastName);

    int* indexArray = buildIndexArray(students, SIZE);

    string lastName;
    double average;
    int thirdGrade;
    cout << "Enter last name: ";
    cin >> lastName;
    cout << "Enter average: ";
    cin >> average;
    cout << "Enter third grade: ";
    cin >> thirdGrade;

    int index = binarySearch(students, indexArray, SIZE, lastName, average, thirdGrade);

    if (index == -1) {
        cout << "Student not found." << endl;
    }
    else {
        cout << "Student found at index " << index << endl;
    }

    delete[] indexArray;
    return 0;
}