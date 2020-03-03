#include <bits/stdc++.h>

using namespace std;

int n, m;

bool is_enough(int k, vector<int> & v) {
  int n = v.size(), prev = 0;
  for (int i = 0; i < n; i++) {
    // can I make something >= to prev
    int max_val = min(v[i] + k, m - 1);
    if (max_val < prev) {
      return false;
    }
    // update prev
    int min_val = v[i];
    if (v[i] + k >= m + prev) {
      min_val = prev;
    }
    prev = max(prev, min_val);
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];

  // it never guesses low or high individually
  int low = -1, high = m - 1;
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    if (is_enough(mid, v)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  cout << high << '\n';
}
