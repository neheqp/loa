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

    cout << "\n";

    for (int i = 0; i < 4; i++) {
        int sum_width = 0;
        for (int j = 0; j < 5; j++) {
            sum_width += arr[i][j];
        }
        cout << "Sum of " << i + 1 << " row = " << sum_width << "\n";
    }

    cout << "\n";

    for (int i = 0; i < 5; i++) {
        int sum_height = 0;
        for (int j = 0; j < 4; j++) {
            sum_height += arr[j][i];
        }
        cout << "Sum of " << i + 1 << " colomn = " << sum_height << "\n";
    }
    return 0;
}
