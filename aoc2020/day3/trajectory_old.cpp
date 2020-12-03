#include <bits/stdc++.h>

using namespace std;

#define RESERVE_SIZE 10000
#define RESERVE_SIZE_2 100

size_t solution_1(vector<vector<bool>> &data, size_t increment_x, size_t increment_y)
{
  size_t count_trees = 0, current_x = 0;
  for (size_t current_y = 0; current_y < data.size(); current_y += increment_y)
  {
    if (current_y == 0 && data[0][0]) {
      count_trees++;
    }
    if (data[current_y].size() == 0) {
      cout << "cannot divide by zero" << endl;
      return -1;
    }
    cout << current_x << ", " << current_y << endl;
    current_x = (current_x + increment_x) % data[current_y].size();
    if (current_y == 0) {
      continue;
    }
    if (data[current_y][current_x]) {
      count_trees++;
    }
  }
  return count_trees;
}

int main()
{
  string line;
  ifstream thefile("input.txt");
  stringstream str_stream, int_stream;
  vector<vector<bool>> data;
  data.reserve(RESERVE_SIZE);
  while (getline(thefile, line))
  {
    vector<bool> current_row;
    for (char const &curr_char: line) {
      current_row.push_back(curr_char == '#');
    }
    data.push_back(current_row);
    // copy(current_row.begin(), current_row.end(), ostream_iterator<bool>(cout, " "));
    // cout << endl;
  }
  size_t res_1 = solution_1(data, 3, 1);
  cout << "part 1 output: " << res_1 << endl;
}
