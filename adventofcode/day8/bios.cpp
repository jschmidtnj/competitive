#include <bits/stdc++.h>

using namespace std;

#define filename "image.txt"

const int width = 25;
const int height = 6;

bool comparePairs(const pair<int, int> &a, const pair<int, int> &b)
{
  return a.first < b.first;
}

int main()
{
  string line;
  ifstream thefile(filename);
  getline(thefile, line);
  istringstream iss;
  vector<pair<int, int>> count;
  iss.str(line);
  iss.clear();
  for (int layerIndex = 0; layerIndex <  (int)line.size(); layerIndex += width * height) {
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;
    for (const char & currChar : line.substr(layerIndex, width * height))
      if (currChar == '0')
        count0++;
      else if (currChar == '1')
        count1++;
      else if (currChar == '2')
        count2++;
    count.push_back(pair<int, int>(count0, count1 * count2));
  }
  sort(count.begin(), count.end(), comparePairs);
  cout << "num 0: " << count[0].first << endl;
  cout << "num 1 * 2: " << count[0].second << endl;
}
