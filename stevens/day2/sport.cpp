#include <bits/stdc++.h>

using namespace std;

// https://codeforces.com/problemset/problem/1195/B

int binarySearch(int l, int r, int x) {
  if (r >= l) {
    int p = l + (r - l) / 2;
    int val = ((1 + p) * p) / 2 + p;
    if (val == x) return p;
    if (val > x) return binarySearch(l, p - 1, x);
    return binarySearch(p + 1, r, x);
  }
  return -1;
}

int main() {
  int k = 1;
  int n = 1;
  cout << binarySearch(0, 1000000, k + n) << endl;
}