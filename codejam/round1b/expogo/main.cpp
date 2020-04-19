#include <bits/stdc++.h>

using namespace std;

vector<string> solutions;
int target_x;
int target_y;

#define max_size 9

void recurse(ssize_t current_x, ssize_t current_y, string past_jumps) {
  if (current_x == target_x && current_y == target_y) {
    solutions.push_back(past_jumps);
    return;
  }
  if (past_jumps.size() > max_size) {
    return;
  }
  ssize_t increment = pow(2, past_jumps.size());
  recurse(current_x, current_y + increment, past_jumps + 'N');
  recurse(current_x + increment, current_y, past_jumps + 'E');
  recurse(current_x, current_y - increment, past_jumps + 'S');
  recurse(current_x - increment, current_y, past_jumps + 'W');
}

struct compare_length {
  bool operator()(const std::string &l, const std::string &r) const {
    if (l.size() == r.size()) {
      return l < r;
    }
    return l.size() < r.size();
  }
};

int main() {
  int num_trials;
  cin >> num_trials;
  solutions.reserve(50);
  for (int trial = 0; trial < num_trials; trial++) {
    solutions.clear();
    cin >> target_x;
    cin >> target_y;
    recurse(0, 0, "");
    cout << "Case #" << trial + 1 << ": ";
    if (solutions.size() == 0) {
      cout << "IMPOSSIBLE";
    } else {
      sort(solutions.begin(), solutions.end(), compare_length());
      cout << solutions[0];
    }
    cout << '\n';
  }
}
