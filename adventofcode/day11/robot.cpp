#include <bits/stdc++.h>
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

using namespace cv;

#define relativeMode 2
#define immediateMode 1
#define positionMode 0

#define white 1
#define black 0

const int mapSize = 200;

struct coords {
  int x;
  int y;
  coords(int _x, int _y) : x{_x}, y{_y} {};
  bool operator==(const coords &otherCoords) const {
    return x == otherCoords.x && y == otherCoords.y;
  }
};

struct custCoordsHasher {
  size_t operator()(const coords &coord) const {
    int xHash = hash<double>{}(coord.x);
    int yHash = hash<int>{}(coord.y);
    return xHash ^ (yHash << 1);
  }
};

void getParamMode(long num, vector<long> &params) {
  params.push_back(num % 100);
  num /= 100;
  while (num != 0) {
    params.push_back(num % 10);
    num /= 10;
  }
  while (params.size() < 4) params.push_back(0);
}

pair<bool, size_t> solution(vector<long> &data, vector<vector<bool>> &map,
                            coords location, Mat &image) {
  size_t numpaint = 0;
  size_t i = 0;
  long relativeBase = 0;
  vector<long> params;
  int currentDirection = 1;  // 0 = right, 1 = up, 2 = left, 3 = down
  bool gotColor = false;
  unordered_set<coords, custCoordsHasher> visited;
  while (i < data.size()) {
    getParamMode(data[i], params);
    long opcode = params[0];
    if (opcode == 1 || opcode == 2 || opcode == 3 || opcode == 4 ||
        opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8 ||
        opcode == 9) {
      long firstparam;
      if (params[1] == positionMode)
        firstparam = data[i + 1];
      else if (params[1] == immediateMode)
        firstparam = i + 1;
      else
        firstparam = relativeBase + data[i + 1];
      if (opcode == 1 || opcode == 2 || opcode == 5 || opcode == 6 ||
          opcode == 7 || opcode == 8) {
        long secondparam;
        if (params[2] == positionMode)
          secondparam = data[i + 2];
        else if (params[2] == immediateMode)
          secondparam = i + 2;
        else
          secondparam = relativeBase + data[i + 2];
        if (opcode == 5 || opcode == 6) {
          if (opcode == 5) {
            if (data[firstparam] != 0)
              i = data[secondparam];
            else
              i += 3;
          } else {
            if (data[firstparam] == 0)
              i = data[secondparam];
            else
              i += 3;
          }
        } else {
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
      } else {
        if (opcode == 9) {
          relativeBase += data[firstparam];
        } else if (opcode == 3) {
          data[firstparam] = map[location.y][location.x];
          // cin >> data[firstparam];
        } else {
          if (!gotColor) {
            map[location.y][location.x] = data[firstparam];
            gotColor = true;
            if (visited.find(location) == visited.end()) {
              numpaint++;
              visited.insert(location);
            }
            int outputColor = 0;
            if (map[location.y][location.x] == white) {
              outputColor = 255;
            }
            image.at<Vec3b>(location.y, location.x)[0] = outputColor;
            image.at<Vec3b>(location.y, location.x)[1] = outputColor;
            image.at<Vec3b>(location.y, location.x)[2] = outputColor;
          } else {
            if (data[firstparam] == 0) {
              // turn left by 90
              if (currentDirection == 3) {
                currentDirection = 0;
              } else {
                currentDirection++;
              }
            } else {
              if (currentDirection == 0) {
                currentDirection = 3;
              } else {
                currentDirection--;
              }
            }
            if (currentDirection == 0) {
              location.x++;
            } else if (currentDirection == 1) {
              location.y--;
            } else if (currentDirection == 2) {
              location.x--;
            } else {
              location.y++;
            }
            gotColor = false;
          }
          // cout << "out: " << data[firstparam] << endl;
        }
        i += 2;
      }
    } else if (opcode == 99) {
      return pair<bool, size_t>(true, numpaint);
    } else {
      cout << "invalid op code " << data[i] << endl;
      return pair<bool, size_t>(false, 0);
    }
    params.clear();
  }
  return pair<bool, size_t>(true, numpaint);
}

int main() {
  string line;
  ifstream thefile("codes.txt");
  getline(thefile, line);
  stringstream linestream;
  vector<long> data;
  data.reserve(10000);
  string splitsegment;
  stringstream strstream;
  linestream.str(line);
  while (getline(linestream, splitsegment, ',')) {
    strstream.str(splitsegment);
    long code;
    if (!(strstream >> code)) {
      cerr << "cannot cast to long" << endl;
      return -1;
    }
    data.push_back(code);
    strstream.clear();
  }
  vector<vector<bool>> map;
  map.reserve(mapSize);
  for (int i = 0; i < mapSize; i++) {
    vector<bool> currentRow;
    currentRow.reserve(mapSize);
    for (int j = 0; j < mapSize; j++) {
      currentRow.push_back(black);
    }
    map.push_back(currentRow);
  }
  coords location(mapSize / 2, mapSize / 2);
  map[location.y][location.x] = white;
  Mat image(mapSize, mapSize, CV_8UC3, Scalar(0, 0, 0));
  pair<bool, size_t> res = solution(data, map, location, image);
  if (!res.first) {
    cerr << "got error" << endl;
    return -1;
  }
  cout << "num visited: " << res.second << endl;
  imwrite("image.png", image);
}
