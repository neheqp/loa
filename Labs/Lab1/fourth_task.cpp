#include <bits/stdc++.h>


// TODO: динамический массив "квадратный"
// TODO: заполнение от -20 до 40
// TODO: Посчитать сумму эл-тов выше гл. диагонали и на ней

using namespace std;

int main() {
    int size;

    cout << "Enter array size: ";
    cin >> size;
    srand(time(NULL));
    int arr[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = rand() % 60 - 20;
        }
    }
    cout << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << arr[i][j] << "  ";
        }
        cout << "\n";
    }

    cout << "\n";

    for (int i = 0; i < size; i++) {
        int sum_width = 0;
        for (int j = 0; j < size; j++) {
            sum_width += arr[i][j];
        }
        cout << "Sum of " << i + 1 << " row = " << sum_width << "\n";
    }

    cout << "\n";

    for (int i = 0; i < size; i++) {
        int sum_height = 0;
        for (int j = 0; j < size; j++) {
            sum_height += arr[j][i];
        }
        cout << "Sum of " << i + 1 << " colomn = " << sum_height << "\n";
    }

    cout << "\n";

    int summa = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            summa += arr[i][j];
        }
    }
    cout << "Summa: " << summa;
    return 0;
}
