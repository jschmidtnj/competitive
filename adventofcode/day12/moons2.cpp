#include <bits/stdc++.h>

using namespace std;

#define fileName "moons.txt"

const int numDimensions = 3;

struct posVel {
  vector<int> positions;
  vector<int> velocities;
  posVel() {
    positions.reserve(numDimensions);
    velocities.reserve(numDimensions);
    for (int i = 0; i < numDimensions; i++) {
      positions.push_back(0);
      velocities.push_back(0);
    }
  };
};

size_t gcd(size_t a, size_t b) {
  while (true) {
    if (a == 0) return b;
    b %= a;
    if (b == 0) return a;
    a %= b;
  }
}

size_t lcm(vector<size_t> arr) {
  if (arr.size() < 2) {
    return 0;
  }
  size_t res = arr[0];
  for (size_t i = 1; i < arr.size(); i++) {
    res = res * arr[i] / gcd(res, arr[i]);
  }
  return res;
}

int main(const int argc, char *const argv[]) {
  string line;
  ifstream thefile(fileName);
  string splitLine;
  istringstream splitLineStream;
  string splitNum;
  istringstream numStream;
  vector<posVel> moons;
  while (getline(thefile, line)) {
    splitLineStream.str(line);
    posVel current;
    for (int i = 0; i < 3; i++) {
      getline(splitLineStream, splitLine, ',');
      numStream.str(splitLine);
      for (int j = 0; j < 2; j++) {
        getline(numStream, splitNum, '=');
      }
      if (splitNum.back() == '>') {
        splitNum.pop_back();
      }
      numStream.clear();
      numStream.str(splitNum);
      int pos;
      if (!(numStream >> pos)) {
        cerr << "invalid position found: " << splitNum << endl;
        return -1;
      }
      current.positions[i] = pos;
      numStream.clear();
    }
    moons.push_back(current);
    splitLineStream.clear();
  }
  vector<int> positions;
  positions.reserve(moons.size());
  size_t count = 0;
  vector<size_t> countToRepeat;
  countToRepeat.reserve(numDimensions);
  for (size_t i = 0; i < numDimensions; i++) {
    countToRepeat.push_back(ULONG_MAX);
  }
  while (true) {
    count++;
    for (int j = 0; j < numDimensions; j++) {
      for (posVel &curr : moons) {
        positions.push_back(curr.positions[j]);
      }
      for (size_t k = 0; k < moons.size(); k++) {
        for (size_t l = 0; l < positions.size(); l++) {
          if (k == l) {
            continue;
          }
          if (moons[k].positions[j] < positions[l]) {
            moons[k].velocities[j]++;
          } else if (moons[k].positions[j] > positions[l]) {
            moons[k].velocities[j]--;
          }
        }
        moons[k].positions[j] += moons[k].velocities[j];
      }
      positions.clear();
      if (countToRepeat[j] == ULONG_MAX) {
        bool foundNonZero = false;
          for (posVel & moon : moons) {
            if (moon.velocities[j] != 0) {
              foundNonZero = true;
              break;
            }
          }
          if (!foundNonZero) {
            countToRepeat[j] = count;
          }
      }
    }
    bool notDone = false;
    for (size_t &count : countToRepeat) {
      if (count == ULONG_MAX) {
        notDone = true;
        break;
      }
    }
    if (!notDone) {
      break;
    }
  }
  size_t res = lcm(countToRepeat) * 2;
  cout << "num steps: " << res << endl;
}
