#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(NULL));
    int arr[4][5];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            arr[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < 4; i++) {
        int s = 0;
        for (int j = 0; j < 5; ++j) {
            s += arr[i][j];
        }
        cout << "Sum of " << i + 1 << " row = " << s << "\n";
    }

    return 0;
}
