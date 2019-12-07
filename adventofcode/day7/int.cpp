#include <bits/stdc++.h>

using namespace std;

#define immediateMode 1
#define positionMode 0

#define startNum 5
#define endNum 9

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

int trial(vector<int> &data, int &i, int input, int phase, bool sendPhase)
{
  vector<int> params;
  while (i < (int)data.size())
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
        i += 2;
        if (opcode == 3)
          if (sendPhase)
          {
            data[firstparam] = phase;
          }
          else
          {
            data[firstparam] = input;
          }
        else
          return data[firstparam];
        sendPhase = false;
      }
    }
    else if (opcode == 99)
    {
      return INT_MAX;
    }
    else
    {
      cout << "invalid op code " << data[i] << endl;
      return 0;
    }
    params.clear();
  }
  cout << "done2" << endl;
  return 1;
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
  int maxRes = 0;
  int maxI = 0, maxJ = 0, maxK = 0, maxL = 0, maxM = 0;
  unordered_set<int> inputs;
  for (int i = startNum; i <= endNum; i++)
    for (int j = startNum; j <= endNum; j++)
      for (int k = startNum; k <= endNum; k++)
        for (int l = startNum; l <= endNum; l++)
          for (int m = startNum; m <= endNum; m++)
          {
            int theindexes[] = {i, j, k, l, m};
            bool cont = false;
            for (int n = 0; n < 5; n++)
              if (inputs.find(theindexes[n]) == inputs.end())
              {
                inputs.insert(theindexes[n]);
              }
              else
              {
                cont = true;
                break;
              }
            inputs.clear();
            if (cont)
              continue;
            int res = 0;
            int lastRes = 0;
            bool firstLoop = true;
            vector<int> data1(data);
            vector<int> data2(data);
            vector<int> data3(data);
            vector<int> data4(data);
            vector<int> data5(data);
            int count1 = 0;
            int count2 = 0;
            int count3 = 0;
            int count4 = 0;
            int count5 = 0;
            while (true)
            {
              res = trial(data1, count1, res, i, firstLoop);
              if (res == INT_MAX)
                break;
              res = trial(data2, count2, res, j, firstLoop);
              if (res == INT_MAX)
                break;
              res = trial(data3, count3, res, k, firstLoop);
              if (res == INT_MAX)
                break;
              res = trial(data4, count4, res, l, firstLoop);
              if (res == INT_MAX)
                break;
              res = trial(data5, count5, res, m, firstLoop);
              if (res == INT_MAX)
                break;
              else
                lastRes = res;
              firstLoop = false;
            }
            res = lastRes;
            if (res > maxRes)
            {
              maxRes = res;
              maxI = i;
              maxJ = j;
              maxK = k;
              maxL = l;
              maxM = m;
            }
          }
  cout << maxI << ", " << maxJ << ", " << maxK << ", " << maxL << ", " << maxM << endl;
  cout << maxRes << endl;
}
