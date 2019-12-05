#include <bits/stdc++.h>

using namespace std;

#define immediateMode 1
#define positionMode 0

void getParamMode(int num, vector<int> &params)
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

bool trial(vector<int> &data)
{
  size_t i = 0;
  vector<int> params;
  while (i < data.size())
  {
    getParamMode(data[i], params);
    int opcode = params[0];
    if (opcode == 1 || opcode == 2 || opcode == 3 || opcode == 4 || opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8)
    {
      int firstparam;
      if (params[1] == positionMode)
        firstparam = data[i + 1];
      else
        firstparam = i + 1;
      if (opcode == 1 || opcode == 2 || opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8)
      {
        int secondparam;
        if (params[2] == positionMode)
          secondparam = data[i + 2];
        else
          secondparam = i + 2;
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
          int thirdparam;
          if (params[3] == positionMode)
            thirdparam = data[i + 3];
          else
            thirdparam = i + 3;
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
        if (opcode == 3)
          cin >> data[firstparam];
        else
          cout << "out: " << data[firstparam] << endl;
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
  vector<int> data;
  string splitsegment;
  stringstream strstream;
  linestream.str(line);
  while (getline(linestream, splitsegment, ','))
  {
    strstream.str(splitsegment);
    int code;
    if (!(strstream >> code))
    {
      cerr << "cannot cast to int" << endl;
      return -1;
    }
    data.push_back(code);
    strstream.clear();
  }
  bool res = trial(data);
  if (!res)
  {
    cerr << "got error" << endl;
    return -1;
  }
}
