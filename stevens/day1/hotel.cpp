#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    // cout << n << endl;
    vector<int> rooms = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    string memory;
    cin >> memory;
    for (int i = 0; i < n; i++) {
        if (memory[i] == 'L') {
            int addIndex = 0;
            while (rooms[addIndex] != 0) {
                addIndex++;
            }
            rooms[addIndex] = 1;
        } else if (memory[i] == 'R') {
            int addIndex = 9;
            while (rooms[addIndex] != 0) {
                addIndex--;
            }
            rooms[addIndex] = 1;
        } else {
            int removeIndex = memory[i] - 48;
            rooms[removeIndex] = 0;
        }
    }
    for (int elem : rooms) {
        cout << elem;
    }
    cout << endl;
}
