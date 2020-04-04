#include <bits/stdc++.h>

using namespace std;

int main() {
  int num_tests;
  cin >> num_tests;
  for (int current_test = 0; current_test < num_tests; current_test++) {
    int n;
    cin >> n;
    int trace = 0;
    unordered_set<int> row_vals;
    row_vals.reserve(n);
    vector<unordered_set<int>> column_vals;
    column_vals.reserve(n);
    for (int i = 0; i < n; i++) {
      column_vals.push_back(unordered_set<int>());
    }
    for (unordered_set<int>& column_set : column_vals) {
      column_set.reserve(n);
    }
    vector<bool> column_limit;
    column_limit.reserve(n);
    for (int i = 0; i < n; i++) {
      column_limit.push_back(false);
    }
    int num_repeat_rows = 0;
    int num_repeat_columns = 0;
    for (int row = 0; row < n; row++) {
      bool found_repeat_row = false;
      for (int column = 0; column < n; column++) {
        int current_val;
        cin >> current_val;
        if (!column_limit.at(column)) {
          if (column_vals.at(column).find(current_val) ==
              column_vals.at(column).end()) {
            column_vals.at(column).insert(current_val);
          } else {
            num_repeat_columns++;
            column_limit.at(column) = true;
          }
        }
        if (!found_repeat_row) {
          if (row_vals.find(current_val) == row_vals.end()) {
            row_vals.insert(current_val);
          } else {
            found_repeat_row = true;
          }
        }
        if (row == column) {
          trace += current_val;
        }
      }
      if (found_repeat_row) {
        num_repeat_rows++;
      }
      row_vals.clear();
    }
    cout << "Case #" << current_test + 1 << ": " << trace << ' '
         << num_repeat_rows << ' ' << num_repeat_columns << '\n';
  }
}
