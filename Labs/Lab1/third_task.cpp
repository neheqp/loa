#include <bits/stdc++.h>

using namespace std;

int main() {
    int size;
    cout << "Enter array size: ";
    cin >> size;
    int arr[size];
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
