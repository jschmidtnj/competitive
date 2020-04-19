#include <bits/stdc++.h>

using namespace std;

ssize_t max_board = 10e9;
ssize_t min_board = -10e-9;

pair<ssize_t, ssize_t> findCircle(vector<pair<ssize_t, ssize_t>> points) {
  ssize_t x1 = points[0].first;
  ssize_t y1 = points[0].second;
  ssize_t x2 = points[1].first;
  ssize_t y2 = points[1].second;
  ssize_t x3 = points[2].first;
  ssize_t y3 = points[2].second;
  ssize_t x12 = x1 - x2;
  ssize_t x13 = x1 - x3;

  ssize_t y12 = y1 - y2;
  ssize_t y13 = y1 - y3;

  ssize_t y31 = y3 - y1;
  ssize_t y21 = y2 - y1;

  ssize_t x31 = x3 - x1;
  ssize_t x21 = x2 - x1;

  // x1^2 - x3^2
  ssize_t sx13 = pow(x1, 2) - pow(x3, 2);

  // y1^2 - y3^2
  ssize_t sy13 = pow(y1, 2) - pow(y3, 2);

  ssize_t sx21 = pow(x2, 2) - pow(x1, 2);
  ssize_t sy21 = pow(y2, 2) - pow(y1, 2);

  ssize_t f = ((sx13) * (x12) + (sy13) * (x12) + (sx21) * (x13) + (sy21) * (x13)) /
          (2 * ((y31) * (x12) - (y21) * (x13)));
  ssize_t g = ((sx13) * (y12) + (sy13) * (y12) + (sx21) * (y13) + (sy21) * (y13)) /
          (2 * ((x31) * (y12) - (x21) * (y13)));

  // ssize_t c = -pow(x1, 2) - pow(y1, 2) - 2 * g * x1 - 2 * f * y1;

  // eqn of circle be x^2 + y^2 + 2*g*x + 2*f*y + c = 0
  // where centre is (h = -g, k = -f) and radius r
  // as r^2 = h^2 + k^2 - c
  ssize_t h = -g;
  ssize_t k = -f;
  // ssize_t sqr_of_r = h * h + k * k - c;

  // r is the radius
  // ssize_t r = sqrt(sqr_of_r);

  return pair<ssize_t, ssize_t>(h, k);
}

int main() {
  int num_trials;
  ssize_t min_radius, max_radius;
  cin >> num_trials;
  default_random_engine generator;
  for (int trial = 0; trial < num_trials; trial++) {
    cin >> min_radius;
    cin >> max_radius;
    ssize_t current_max = max_board + max_radius;
    ssize_t current_min = min_board - max_radius;
    uniform_int_distribution<> distr(current_min, current_max);
    vector<pair<ssize_t, ssize_t>> points_on_circle;
    int num_points = 3;
    for (int i = 0; i < num_points; i++) {
      string res = "MISS";
      ssize_t current_x = 0, current_y = 0;
      while (res == "MISS") {
        current_x = distr(generator);
        current_y = distr(generator);
        cout << current_x << ' ' << current_y << endl;
        cin >> res;
      }
      if (res == "HIT") {
        ssize_t last_guess = current_y;
        ssize_t current_guess = current_y - max_radius;
        bool found_center = false;
        while (last_guess != current_guess) {
          cout << current_x << ' ' << current_guess << endl;
          cin >> res;
          ssize_t new_delta = abs(current_guess - last_guess) / 2;
          last_guess = current_guess;
          if (res == "HIT") {
            current_guess -= new_delta;
          } else if (res == "MISS") {
            current_guess += new_delta;
          } else if (res == "CENTER") {
            found_center = true;
            break;
          } else {
            return EXIT_FAILURE;
          }
        }
        if (found_center) {
          continue;
        }
        points_on_circle.push_back(pair<int, int>(current_x, current_guess));
      } else if (res == "CENTER") {
        continue;
      } else {
        return EXIT_FAILURE;
      }
    }
    pair<int, int> center = findCircle(points_on_circle);
    cout << center.first << ' ' << center.second << '\n';
    string res;
    cin >> res;
    if (res != "CENTER") {
      int delta = 5;
      bool foundCenter = false;
      for (int i = -delta; i < delta; i++) {
        for (int j = -delta; j < delta; j++) {
          cout << center.first  + i << ' ' << center.second + j << '\n';
          string res;
          cin >> res;
          if (res == "CENTER") {
            foundCenter = true;
            break;
          }
        }
      }
      if (!foundCenter) {
        return EXIT_FAILURE;
      }
    }
  }
}
