#include <bits/stdc++.h>

using namespace std;

int main(){
    int max = 0, min = 100000;
    int arr[] = {1, 2,3,4,5,6,7,8,9,10};
    int size = sizeof(arr) / sizeof(arr[0]);
    for(int i = 0; i < size; i++){
        if(arr[i] > max){
            max = arr[i];
        }
        if (arr[i] < min){
            min = arr[i];
        }
    }
    cout << "Answer: " << max - min;
    return 0;
}