#include <bits/stdc++.h>

using namespace std;

#define relativeMode 2
#define immediateMode 1
#define positionMode 0

#define empty 0
#define ball 2

#define messageSize 3

const int screenSize = 50;

void getParamMode(long num, vector<long> &params)
{
  params.push_back(num % 100);
  num /= 100;
  while (num != 0)
  {
    params.push_back(num % 10);
    num /= 10;
  }
  while (params.size() < 4)
    params.push_back(0);
}

bool trial(vector<long> &data, vector<vector<long>> &screen)
{
  size_t i = 0;
  long relativeBase = 0;
  vector<long> params;
  vector<int> currentOutput;
  while (i < data.size())
  {
    getParamMode(data[i], params);
    long opcode = params[0];
    if (opcode == 1 || opcode == 2 || opcode == 3 || opcode == 4 || opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8 || opcode == 9)
    {
      long firstparam;
      if (params[1] == positionMode)
        firstparam = data[i + 1];
      else if (params[1] == immediateMode)
        firstparam = i + 1;
      else
        firstparam = relativeBase + data[i + 1];
      if (opcode == 1 || opcode == 2 || opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8)
      {
        long secondparam;
        if (params[2] == positionMode)
          secondparam = data[i + 2];
        else if (params[2] == immediateMode)
          secondparam = i + 2;
        else
          secondparam = relativeBase + data[i + 2];
        if (opcode == 5 || opcode == 6)
        {
          if (opcode == 5)
          {
            if (data[firstparam] != 0)
              i = data[secondparam];
            else
              i += 3;
          }
          else
          {
            if (data[firstparam] == 0)
              i = data[secondparam];
            else
              i += 3;
          }
        }
        else
        {
          long thirdparam;
          if (params[3] == positionMode)
            thirdparam = data[i + 3];
          else if (params[3] == immediateMode)
            thirdparam = i + 3;
          else
            thirdparam = relativeBase + data[i + 3];
          if (opcode == 1)
            data[thirdparam] = data[firstparam] + data[secondparam];
          else if (opcode == 2)
            data[thirdparam] = data[firstparam] * data[secondparam];
          else if (opcode == 7)
            if (data[firstparam] < data[secondparam])
              data[thirdparam] = 1;
            else
              data[thirdparam] = 0;
          else if (data[firstparam] == data[secondparam])
            data[thirdparam] = 1;
          else
            data[thirdparam] = 0;
          i += 4;
        }
      }
      else
      {
        if (opcode == 9) {
          relativeBase += data[firstparam];
        } else if (opcode == 3) {
          cin >> data[firstparam];
        } else {
          currentOutput.push_back(data[firstparam]);
          if (currentOutput.size() == messageSize) {
            screen[currentOutput[0]][currentOutput[1]] = data[firstparam];
            currentOutput.clear();
          }
          // cout << "out: " << data[firstparam] << endl;
        }
        i += 2;
      }
    }
    else if (opcode == 99)
    {
      return true;
    }
    else
    {
      cout << "invalid op code " << data[i] << endl;
      return false;
    }
    params.clear();
  }
  return true;
}

int main()
{
  string line;
  ifstream thefile("codes.txt");
  getline(thefile, line);
  stringstream linestream;
  vector<long> data;
  data.reserve(10000);
  string splitsegment;
  stringstream strstream;
  linestream.str(line);
  while (getline(linestream, splitsegment, ','))
  {
    strstream.str(splitsegment);
    long code;
    if (!(strstream >> code))
    {
      cerr << "cannot cast to long" << endl;
      return -1;
    }
    data.push_back(code);
    strstream.clear();
  }
  vector<vector<long>> screen;
  screen.reserve(screenSize);
  for (int i = 0; i < screenSize; i++) {
    vector<long> current;
    current.reserve(screenSize);
    for (int j = 0; j < screenSize; j++) {
      current.push_back(empty);
    }
    screen.push_back(current);
  }
  // play for free
  // data[0] = 2;
  bool res = trial(data, screen);
  if (!res)
  {
    cerr << "got error" << endl;
    return -1;
  }
  size_t count = 0;
  for (vector<long> & curr : screen) {
    for (long & pixel: curr) {
      if (pixel == ball) {
        count++;
      }
    }
  }
  cout << count << endl;
}
