#include <bits/stdc++.h>

using namespace std;

#define fileName "num.txt"
#define numDigitsPrint 8

const int pattern[] = {1, 0, -1, 0};
const int patternLength = 4;
const int digitSkip = 7;
const int numRepeats = 10000; // input repeated this many times

int main(const int argc, char *const argv[]) {
  if (argc < 2) {
    cerr << "cannot find number of phases" << endl;
    return -1;
  }
  istringstream iss(argv[1]);
  int numPhases;
  if (!(iss >> numPhases) || numPhases <= 0) {
    cerr << "invalid num phases" << endl;
    return -1;
  }
  string line;
  ifstream thefile(fileName);
  getline(thefile, line);
  vector<int> nums;
  nums.reserve(line.length());
  for (const char & curr : line) {
    nums.push_back(curr - '0');
  }
  cout << "num digits: " << nums.size() << endl;
  for (int i = 0; i < numPhases; i++) {
    vector<int> newdigits = nums;
    for (size_t j = 0; j < nums.size(); j++) {
      int newDigit = 0;
      int currentPatternIndex = 0;
      int offset = 0;
      for (size_t k = 0; k < nums.size(); k++) {
        if (k < j) {
          // digit * 0
          if (k != 0) {
            offset++;
          }
          continue;
        } else {
          newDigit += nums[k] * pattern[currentPatternIndex];
          // something like this:
          if (j == 0 || (k - offset) % (j + 1) == 0) {
            currentPatternIndex++;
            if (currentPatternIndex == patternLength) {
              currentPatternIndex = 0;
            }
          }
        }
      }
      newdigits[j] = abs(newDigit) % 10;
    }
    nums = newdigits;
  }
  for (int i = 0; i < numDigitsPrint; i++) {
    cout << nums[i];
  }
  cout << endl;
  int numSkip = 0;
  for (int i = 0; i < digitSkip; i++) {
    numSkip += nums[i] * pow(10, digitSkip - i - 1);
  }
  // cout << numSkip << endl;
  for (int i = numSkip; i < numDigitsPrint; i++) {
    cout << nums[i];
  }
  cout << endl;
}
