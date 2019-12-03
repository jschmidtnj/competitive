#include <bits/stdc++.h>

using namespace std;

int main() {
  string line;
  stringstream strStream;
  ifstream thefile("mass.txt");
  unsigned long total = 0;
  while (getline(thefile, line)) {
    strStream.str(line);
    int mass;
    if (!(strStream >> mass)) {
      cout << "cannot cast to int" << endl;
      return -1;
    }
    total += (mass / 3) - 2;
    strStream.clear();
  }
  cout << total << endl;
}
