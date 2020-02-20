#include <bits/stdc++.h>

using namespace std;

int max_slices, num_pizzas;
int* pizza_data;

pair<int, vector<int>> use_lose(int index) {
  pair<int, vector<int>> res = pair<int, vector<int>>(0, vector<int>());
  res.second.reserve(max_slices);
  if (pizza_data[index] > max_slices || index >= num_pizzas) {
    return res;
  }
  pair<int, vector<int>> recursive = use_lose(index + 1);
  if (pizza_data[index] + recursive.first > max_slices) {
    return recursive;
  }
  recursive.first += pizza_data[index];
  recursive.second.push_back(index);
  return recursive;
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    cout << "invalid args" << endl;
    return 1;
  }
  ifstream file(argv[1]);
  file >> max_slices >> num_pizzas;
  pizza_data = new int[num_pizzas];
  for (int i = 0; i < num_pizzas; i++) {
    int current_pizza_num_slices;
    file >> current_pizza_num_slices;
    pizza_data[i] = current_pizza_num_slices;
    // cout << current_pizza_num_slices << endl;
  }
  pair<int, vector<int>> res = use_lose(0);
  cout << res.first << endl;
  sort(res.second.begin(), res.second.end());
  if (res.second.size() > 0) {
    cout << res.second[0];
  }
  for (size_t i = 1; i < res.second.size(); i++) {
    cout << ", " << res.second[i];
  }
  cout << '\n';
  file.close();
  delete pizza_data;
}
