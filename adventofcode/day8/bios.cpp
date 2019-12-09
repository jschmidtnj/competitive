#include <bits/stdc++.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>

using namespace cv;

using namespace std;

#define filename "image.txt"

const int width = 25;
const int height = 6;

bool comparePairs(const pair<int, int> &a, const pair<int, int> &b)
{
  return a.first < b.first;
}

int main()
{
  string line;
  ifstream thefile(filename);
  getline(thefile, line);
  istringstream iss;
  vector<pair<int, int>> count;
  vector<vector<bool>> set;
  set.reserve(height);
  for (int i = 0; i < height; i++)
  {
    vector<bool> current;
    current.reserve(width);
    for (int j = 0; j < width; j++)
      current.push_back(false);
    set.push_back(current);
  }
  iss.str(line);
  iss.clear();
  Mat image(height, width, CV_8UC3, Scalar(0, 0, 0));
  for (int layerIndex = 0; layerIndex < (int)line.size(); layerIndex += width * height)
  {
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;
    for (int row = 0; row < height; row++)
    {
      for (int col = 0; col < width; col++)
      {
        int i = layerIndex + row * width + col;
        if (line[i] == '0')
        {
          count0++;
          set[row][col] = true;
        }
        else if (line[i] == '1')
        {
          count1++;
          if (!set[row][col])
          {
            image.at<Vec3b>(row, col)[0] = 255;
            image.at<Vec3b>(row, col)[1] = 255;
            image.at<Vec3b>(row, col)[2] = 255;
          }
          set[row][col] = true;
        }
        else if (line[i] == '2')
        {
          count2++;
        }
      }
    }
    count.push_back(pair<int, int>(count0, count1 * count2));
  }
  sort(count.begin(), count.end(), comparePairs);
  cout << "num 0: " << count[0].first << endl;
  cout << "num 1 * 2: " << count[0].second << endl;
  imwrite("image.png", image);
}
