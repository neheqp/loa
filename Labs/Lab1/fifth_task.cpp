#include <bits/stdc++.h>

using namespace std;

struct Student{
    string firstName;
    string lastName;
    string group;
}
student1 = {"Shnayder", "Kirill", "22VVV3"},
student2 = {"Telnov", "Ilya", "22VVV3"},
student3 = {"Gorodnichev", "Maxim", "22VVV3"};

int main() {
    string request;
    cin >> request;
    Student arr[3] = {student1, student2, student3};
    for(int i = 0; i < 3; i++){
        if(arr[i].firstName == request){
            cout << arr[i].firstName << " " << arr[i].lastName << " " << arr[i].group;
        }
    }
    return 0;
}
