#include <bits/stdc++.h>

using namespace std;

#define start 108457
#define end 562041

int main()
{
  int count = 0;
  vector<int> digits;
  for (int i = start + 1; i < end; i++)
  {
    digits.clear();
    int getDigits = i;
    for (int j = 0; j < 6; j++)
    {
      digits.push_back(getDigits % 10);
      getDigits /= 10;
    }
    bool foundSequential = false;
    int numRow = 1;
    for (int j = digits.size() - 1; j >= 1; j--)
    {
      if (digits[j] > digits[j - 1])
      {
        foundSequential = false;
        break;
      }
      if (digits[j] == digits[j - 1]) {
        numRow++;
        if (j == 1 && numRow == 2) {
          foundSequential = true;
        }
      } else {
        if (numRow == 2) {
          foundSequential = true;
        }
        numRow = 1;
      }
    }
    if (foundSequential)
      count++;
  }
  cout << count << endl;
}
