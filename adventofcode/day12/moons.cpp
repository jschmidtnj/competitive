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

int main(const int argc, char *const argv[]) {
  if (argc != 2) {
    cerr << "no num steps provided / too many args" << endl;
    return -1;
  }
  istringstream splitLineStream;
  splitLineStream.str(argv[1]);
  size_t numSteps;
  if (!(splitLineStream >> numSteps) || numSteps < 0) {
    cerr << "invalid num steps given" << endl;
    return -1;
  }
  splitLineStream.clear();
  string line;
  ifstream thefile(fileName);
  string splitLine;
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
  for (size_t i = 0; i < numSteps; i++) {
    for (int j = 0; j < numDimensions; j++) {
      for (posVel & curr : moons) {
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
    }
  }
  long sumTotal = 0;
  for (posVel curr : moons) {
    int potential = 0, kinetic = 0;
    for (int i = 0; i < numDimensions; i++) {
      potential += abs(curr.positions[i]);
      kinetic += abs(curr.velocities[i]);
    }
    sumTotal += potential * kinetic;
  }
  cout << "sum total: " << sumTotal << endl;
}
