#include <bits/stdc++.h>

using namespace std;

bool found_solution;
bool rows[51][51], columns[51][51];
int square[51][51];
int n_elements;
int trace;
int trial;

void recurse(int curr_trace, int row, int col) {
  if (!found_solution && curr_trace == trace && row == n_elements && col == n_elements + 1) {
    cout << "Case #" << trial + 1 << ": "
         << "POSSIBLE\n";
    for (int i = 1; i <= n_elements; i++) {
      for (int j = 1; j <= n_elements; j++) {
        cout << square[i][j] << " ";
      }
      cout << "\n";
    }
    found_solution = true;
    return;
  } else if (row > n_elements) {
    return;
  } else if (col > n_elements) {
    recurse(curr_trace, row + 1, 1);
  }
  for (int i = 1; i <= n_elements && !found_solution; i++) {
    if (!rows[row][i] && !columns[col][i]) {
      rows[row][i] = columns[col][i] = true;
      if (row == col) {
        curr_trace += i;
      }
      square[row][col] = i;
      recurse(curr_trace, row, col + 1);
      rows[row][i] = columns[col][i] = false;
      if (row == col) {
        curr_trace -= i;
      }
      square[row][col] = 0;
    }
  }
}

int main() {
  int num_trials;
  cin >> num_trials;
  for (trial = 0; trial < num_trials; trial++) {
    cin >> n_elements;
    cin >> trace;
    recurse(0, 1, 1);
    if (!found_solution) {
      cout << "Case #" << trial + 1 << ": "
           << "IMPOSSIBLE\n";
    }
    found_solution = false;
  }
}
