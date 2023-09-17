#include <bits/stdc++.h>

using namespace std;

int main() {
    srand(time(NULL));
    int arr[10];
    for(int i =0; i< 10; i++){
        arr[i] = rand() % 100;
    }

    for(int i = 0; i < 10; i++){
        cout << arr[i] << " ";
    }

    return 0;
}
