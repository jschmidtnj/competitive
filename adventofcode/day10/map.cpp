#include <bits/stdc++.h>

using namespace std;

struct custLocation {
  size_t x, y;
  double distance;
  custLocation(size_t _x, size_t _y, double _distance)
      : x{_x}, y{_y}, distance{_distance} {};
  custLocation() : x{0}, y{0} {};
  bool operator==(const custLocation &coord) const {
    return x == coord.x && y == coord.y;
  }
};

struct custSlope {
  double slope;
  int quadrant;
  custSlope(double _slope, int _quadrant)
      : slope{_slope}, quadrant{_quadrant} {};
  bool operator==(const custSlope &otherSlope) const {
    return quadrant == otherSlope.quadrant && slope == otherSlope.slope;
  }
};

struct custSlopeCompare {
  bool operator()(const custSlope &lhs, const custSlope &rhs) const {
    if (lhs.quadrant != rhs.quadrant) {
      return lhs.quadrant < rhs.quadrant;
    }
    return lhs.slope < rhs.slope;
  }
};

struct custSlopeHasher {
  size_t operator()(const custSlope &coord) const {
    size_t slopeHash = hash<double>{}(coord.slope);
    int quadrantHash = hash<int>{}(coord.quadrant);
    return slopeHash ^ (quadrantHash << 1);
  }
};

int main(const int argc, char *const argv[]) {
  if (argc != 2) {
    cerr << "cannot find target num" << endl;
    return -1;
  }
  istringstream iss(argv[1]);
  int targetDestroy;
  if (!(iss >> targetDestroy) || targetDestroy <= 0) {
    cerr << "found invalid target" << endl;
    return -1;
  }
  ifstream thefile("map.txt");
  string line;
  vector<custLocation> asteroids;
  size_t y = 0;
  while (getline(thefile, line)) {
    for (size_t x = 0; x < line.length(); x++) {
      if (line[x] == '#') {
        asteroids.push_back(custLocation(x, y, 0));
      }
    }
    y++;
  }
  custLocation targetDestroyLocation;
  // quadrant numbers:
  //     0
  // 7 2 | 1  1
  // 6 -----  2
  // 5 3 | 4  3
  //     4
  map<custSlope, custLocation, custSlopeCompare> detectedAsteroids;
  map<custSlope, custLocation, custSlopeCompare> maxDetectedAsteroids;
  int destroyCount = 0;
  while (asteroids.size() > 1) {
    for (custLocation &currentCoords : asteroids) {
      for (custLocation &potentialDetection : asteroids) {
        if (potentialDetection == currentCoords) continue;
        // (y2 - y1) / (x2 - x1)
        double dy = (double)potentialDetection.y - (double)currentCoords.y;
        double dx = (double)potentialDetection.x - (double)currentCoords.x;
        double slope;
        if (potentialDetection.y == currentCoords.y) {
          slope = 0;
        } else if (potentialDetection.x == currentCoords.x) {
          slope = DBL_MAX;
        } else {
          slope = dy / dx;
        }
        int quadrant;
        if (dy == 0) {
          quadrant = dx > 0 ? 2 : 6;
        } else if (dx == 0) {
          quadrant = dy < 0 ? 0 : 4;
        } else {
          if (dx > 0 && dy < 0) {
            quadrant = 1;
          } else if (dy < 0 && dx < 0) {
            quadrant = 7;
          } else if (dy > 0 && dx < 0) {
            quadrant = 5;
          } else {
            quadrant = 3;
          }
        }
        potentialDetection.distance = sqrt(dx * dx + dy * dy);
        custSlope theslope(slope, quadrant);
        if (detectedAsteroids.find(theslope) == detectedAsteroids.end()) {
          detectedAsteroids[theslope] = potentialDetection;
        } else if (potentialDetection.distance <
                   detectedAsteroids[theslope].distance) {
          detectedAsteroids[theslope] = potentialDetection;
        }
      }
      if (detectedAsteroids.size() > maxDetectedAsteroids.size()) {
        maxDetectedAsteroids = detectedAsteroids;
      }
      detectedAsteroids.clear();
    }
    for (pair<custSlope, custLocation> keyValue : maxDetectedAsteroids) {
      asteroids.erase(
          std::remove(asteroids.begin(), asteroids.end(),
                      custLocation(keyValue.second.x, keyValue.second.y, 0)),
          asteroids.end());
      destroyCount++;
      if (destroyCount == targetDestroy) {
        targetDestroyLocation = keyValue.second;
        targetDestroyLocation.distance = 0;
      }
    }
    maxDetectedAsteroids.clear();
  }
  if (destroyCount >= targetDestroy) {
    cout << "target destroyed at (" << targetDestroyLocation.x << ','
         << targetDestroyLocation.y
         << "): " << targetDestroyLocation.x * 100 + targetDestroyLocation.y
         << endl;
  } else {
    cout << "not enough asteroids to find target" << endl;
  }
}
