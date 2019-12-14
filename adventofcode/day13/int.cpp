#include <bits/stdc++.h>
#include <opencv4/opencv2/opencv.hpp>
#include <curses.h>

using namespace std;

using namespace cv;

#define inputCode "codes.txt"
#define outputImage "screen.png"

#define relativeMode 2
#define immediateMode 1
#define positionMode 0

#define empty 0
#define ball 4
#define block 2

#define messageSize 3

const int screenSize = 45;

void getParamMode(long num, vector<long> &params) {
  params.push_back(num % 100);
  num /= 100;
  while (num != 0) {
    params.push_back(num % 10);
    num /= 10;
  }
  while (params.size() < 4) {
    params.push_back(0);
  }
}

bool trial(vector<long> &data, vector<vector<long>> &screen, int &score,
           WINDOW *win) {
  Mat image(screenSize, screenSize, CV_8UC3, Scalar(0, 0, 0));
  size_t i = 0;
  long relativeBase = 0;
  vector<long> params;
  vector<int> currentOutput;
  while (i < data.size()) {
    getParamMode(data[i], params);
    long opcode = params[0];
    if (opcode == 1 || opcode == 2 || opcode == 3 || opcode == 4 ||
        opcode == 5 || opcode == 6 || opcode == 7 || opcode == 8 ||
        opcode == 9) {
      long firstparam;
      if (params[1] == positionMode) {
        firstparam = data[i + 1];
      } else if (params[1] == immediateMode) {
        firstparam = i + 1;
      } else {
        firstparam = relativeBase + data[i + 1];
      }
      if (opcode == 1 || opcode == 2 || opcode == 5 || opcode == 6 ||
          opcode == 7 || opcode == 8) {
        long secondparam;
        if (params[2] == positionMode) {
          secondparam = data[i + 2];
        } else if (params[2] == immediateMode) {
          secondparam = i + 2;
        } else {
          secondparam = relativeBase + data[i + 2];
        }
        if (opcode == 5 || opcode == 6) {
          if (opcode == 5) {
            if (data[firstparam] != 0) {
              i = data[secondparam];
            } else {
              i += 3;
            }
          } else {
            if (data[firstparam] == 0) {
              i = data[secondparam];
            } else {
              i += 3;
            }
          }
        } else {
          long thirdparam;
          if (params[3] == positionMode) {
            thirdparam = data[i + 3];
          } else if (params[3] == immediateMode) {
            thirdparam = i + 3;
          } else {
            thirdparam = relativeBase + data[i + 3];
          }
          if (opcode == 1) {
            data[thirdparam] = data[firstparam] + data[secondparam];
          } else if (opcode == 2) {
            data[thirdparam] = data[firstparam] * data[secondparam];
          } else if (opcode == 7) {
            if (data[firstparam] < data[secondparam]) {
              data[thirdparam] = 1;
            } else {
              data[thirdparam] = 0;
            }
          } else if (data[firstparam] == data[secondparam]) {
            data[thirdparam] = 1;
          } else {
            data[thirdparam] = 0;
          }
          i += 4;
        }
      } else {
        if (opcode == 9) {
          relativeBase += data[firstparam];
        } else if (opcode == 3) {
          rotate(image, image, ROTATE_90_CLOCKWISE);
          imwrite(outputImage, image);
          rotate(image, image, ROTATE_90_COUNTERCLOCKWISE);
          int inputVal = INT_MAX;
          while (inputVal == INT_MAX) {
            int input = getch();
            if (input == ' ' || input == KEY_UP || input == KEY_DOWN) {
              inputVal = 0;
            } else if (input == KEY_LEFT) {
              inputVal = 1;
            } else if (input == KEY_RIGHT) {
              inputVal = -1;
            }
          }
          wrefresh(win);
          data[firstparam] = inputVal;
        } else {
          currentOutput.push_back(data[firstparam]);
          if (currentOutput.size() == messageSize) {
            if (currentOutput[0] == -1 && currentOutput[1] == 0) {
              wrefresh(win);
              score = currentOutput[2];
            } else {
              screen[currentOutput[0]][currentOutput[1]] = data[firstparam];
              int outputColor = 0;
              if (data[firstparam] == ball) {
                outputColor = 100;
              } else if (data[firstparam] != empty) {
                outputColor = 255;
              }
              image.at<Vec3b>(currentOutput[0], currentOutput[1])[0] =
                  outputColor;
              image.at<Vec3b>(currentOutput[0], currentOutput[1])[1] =
                  outputColor;
              image.at<Vec3b>(currentOutput[0], currentOutput[1])[2] =
                  outputColor;
            }
            currentOutput.clear();
          }
          // cout << "out: " << data[firstparam] << endl;
        }
        i += 2;
      }
    } else if (opcode == 99) {
      return true;
    } else {
      cout << "invalid op code " << data[i] << endl;
      wrefresh(win);
      return false;
    }
    params.clear();
  }
  return true;
}

int main() {
  // setup cursor stuff
  initscr();
  cbreak();
  keypad(stdscr, true);
  WINDOW *win = newwin(20, 50, 0, 0);
  string line;
  ifstream thefile(inputCode);
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
      wrefresh(win);
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
  data[0] = 2;
  int score = 0;
  bool res = trial(data, screen, score, win);
  if (!res) {
    cerr << "got error" << endl;
    wrefresh(win);
    return -1;
  }
  size_t count = 0;
  for (vector<long> &curr : screen) {
    for (long &pixel : curr) {
      if (pixel == block) {
        count++;
      }
    }
  }
  // cout << count << endl;
  cout << "final score: " << score;
  wrefresh(win);
}
