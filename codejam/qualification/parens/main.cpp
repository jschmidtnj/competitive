#include <bits/stdc++.h>

using namespace std;

int main() {
  int num_input;
  cin >> num_input;
  string line;
  getline(cin, line);
  for (int i = 0; i < num_input; i++) {
    getline(cin, line);
    string res = "";
    int stack = 0;
    for (char& curr_char : line) {
      int current_int = curr_char - '0';
      if (current_int > stack) {
        while (current_int > stack) {
          res += '(';
          stack++;
        }
        res += curr_char;
      } else if (current_int == stack) {
        res += curr_char;
      } else {
        while (current_int < stack) {
          res += ')';
          stack--;
        }
        res += curr_char;
      }
    }
    while (stack > 0) {
      res += ')';
      stack--;
    }
    cout << "Case #" << i + 1 << ": " << res << '\n';
  }
}
