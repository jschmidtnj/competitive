#include <bits/stdc++.h>

using namespace std;

#define RESERVE_SIZE 10000
#define sum_target 2020

int solution_1(vector<int> &data, unordered_set<int> &seen_numbers) {
  for (int &elem : data) {
    if (elem > sum_target) {
      continue;
    }
    int complement = sum_target - elem;
    if (seen_numbers.find(complement) != seen_numbers.end()) {
      cout << elem << ", " << complement << endl;
      return elem * complement;
    }
  }
  return -1;
}

int solution_2(vector<int> &data, unordered_set<int> &seen_numbers) {
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i] > sum_target) {
      continue;
    }
    for (size_t j = i + 1; j < data.size(); j++) {
      if (data[j] > sum_target) {
        continue;
      }
      int complement = sum_target - data[i] - data[j];
      if (complement < 0) {
        continue;
      }
      if (seen_numbers.find(complement) != seen_numbers.end()) {
        cout << data[i] << ", " << data[j] << ", " << complement << endl;
        return data[i] * data[j] * complement;
      }
    }
  }
  return -1;
}

int main() {
  string line;
  ifstream thefile("input.txt");
  getline(thefile, line);
  stringstream strStream;
  vector<int> data;
  data.reserve(RESERVE_SIZE);
  unordered_set<int> seen_numbers;
  seen_numbers.reserve(RESERVE_SIZE);
  while (getline(thefile, line)) {
    strStream.str(line);
    int current_num;
    if (!(strStream >> current_num)) {
      cout << "cannot cast " << line << " to int" << endl;
      return -1;
    }
    data.push_back(current_num);
    seen_numbers.insert(current_num);
    strStream.clear();
  }
  int res_1 = solution_1(data, seen_numbers);
  if (res_1 < 0) {
    cout << "no result found for part 1" << endl;
    return res_1;
  }
  cout << "part 1 output: " << res_1 << endl;
  int res_2 = solution_2(data, seen_numbers);
  if (res_2 < 0) {
    cout << "no result found for part 2" << endl;
    return res_2;
  }
  cout << "part 2 output: " << res_2 << endl;
}
