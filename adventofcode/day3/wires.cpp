#include <bits/stdc++.h>

using namespace std;

struct coords
{
  long x;
  long y;
  coords(long _x, long _y) : x{_x}, y{_y} {};
  coords() : x{0}, y{0} {};
};

bool comparePairs(const coords &a, const coords &b)
{
  return abs(a.x) + abs(a.y) < abs(b.x) + abs(b.y);
}

int main()
{
  string line;
  ifstream thefile("paths.txt");
  stringstream linestream;
  string splitsegment;
  stringstream strstream;
  unordered_map<long, vector<pair<long, long>>> vertical;
  unordered_map<long, vector<pair<long, long>>> horizontal;
  set<long> verticalKeys;
  set<long> horizontalKeys;
  vector<long> sortedVerticalKeys;
  vector<long> sortedHorizontalKeys;
  vector<coords> intersections;
  int mapsize = 200;
  vertical.reserve(mapsize);
  horizontal.reserve(mapsize);
  long stepsSecondWireFirstIntersection = 0;
  vector<pair<long, char>> firstWireSteps;
  vector<pair<long, char>> secondWireSteps;
  coords firstIntersect;
  for (int i = 0; i < 2; i++)
  {
    getline(thefile, line);
    linestream.str(line);
    coords curr(0, 0);
    while (getline(linestream, splitsegment, ','))
    {
      char type = splitsegment[0];
      strstream.str(splitsegment.substr(1));
      long distance;
      if (!(strstream >> distance))
      {
        cout << "cannot cast to unsigned long long" << endl;
        return -1;
      }
      if (i == 0)
        firstWireSteps.push_back(pair<long, char>(distance, type));
      else
        secondWireSteps.push_back(pair<long, char>(distance, type));
      if (type == 'R' || type == 'L')
      {
        long lower, upper;
        if (type == 'L')
        {
          lower = curr.x - distance;
          upper = curr.x;
        }
        else
        {
          lower = curr.x;
          upper = curr.x + distance;
        }
        if (i == 0)
        {
          horizontal[curr.y].push_back(pair<long, long>(lower, upper));
          horizontalKeys.insert(curr.y);
        }
        else
        {
          auto start = lower_bound(sortedVerticalKeys.begin(), sortedVerticalKeys.end(), lower);
          auto end = upper_bound(sortedVerticalKeys.begin(), sortedVerticalKeys.end(), upper);

          for (auto it = start; it != end; it++)
          {
            for (pair<long, long> &startEnd : vertical[*it])
            {
              if (startEnd.first <= curr.y && startEnd.second >= curr.y)
              {
                coords intersect(*it, curr.y);
                if (!(intersect.x == 0 && intersect.y == 0))
                {
                  if (firstIntersect.x == 0 && firstIntersect.y == 0)
                    firstIntersect = intersect;
                  intersections.push_back(intersect);
                }
              }
            }
          }
          if (firstIntersect.x == 0 && firstIntersect.y == 0)
          {
            stepsSecondWireFirstIntersection += distance;
          }
          else
          {
            if (type == 'L')
              stepsSecondWireFirstIntersection += (curr.x - firstIntersect.x);
            else
              stepsSecondWireFirstIntersection += (firstIntersect.x - curr.x);
          }
        }
        curr.x = type == 'R' ? upper : lower;
      }
      else if (type == 'U' || type == 'D')
      {
        long lower, upper;
        if (type == 'D')
        {
          lower = curr.y - distance;
          upper = curr.y;
        }
        else
        {
          lower = curr.y;
          upper = curr.y + distance;
        }
        if (i == 0)
        {

          vertical[curr.x].push_back(pair<long, long>(lower, upper));
          verticalKeys.insert(curr.x);
        }
        else
        {
          auto start = lower_bound(sortedHorizontalKeys.begin(), sortedHorizontalKeys.end(), lower);
          auto end = upper_bound(sortedHorizontalKeys.begin(), sortedHorizontalKeys.end(), upper);
          for (auto it = start; it != end; it++)
          {
            for (pair<long, long> &startEnd : horizontal[*it])
            {
              if (startEnd.first <= curr.x && startEnd.second >= curr.x)
              {
                coords intersect(curr.x, *it);
                if (!(intersect.x == 0 && intersect.y == 0))
                {
                  if (firstIntersect.x == 0 && firstIntersect.y == 0)
                    firstIntersect = intersect;
                  intersections.push_back(intersect);
                }
              }
            }
          }
          if (firstIntersect.x == 0 && firstIntersect.y == 0)
          {
            stepsSecondWireFirstIntersection += distance;
          }
          else
          {
            if (type == 'D')
              stepsSecondWireFirstIntersection += (curr.y - firstIntersect.y);
            else
              stepsSecondWireFirstIntersection += (firstIntersect.y - curr.y);
          }
        }
        curr.y = type == 'U' ? upper : lower;
      }
      else
      {
        cout << "invalid character found: " << type << endl;
        return -1;
      }
      strstream.clear();
    }
    if (i == 0)
    {
      sortedVerticalKeys.reserve(verticalKeys.size());
      sortedVerticalKeys.assign(verticalKeys.begin(), verticalKeys.end());
      sort(sortedVerticalKeys.begin(), sortedVerticalKeys.end());
      sortedHorizontalKeys.reserve(horizontalKeys.size());
      sortedHorizontalKeys.assign(horizontalKeys.begin(), horizontalKeys.end());
      sort(sortedHorizontalKeys.begin(), sortedHorizontalKeys.end());
    }
    linestream.clear();
  }
  sort(intersections.begin(), intersections.end(), comparePairs);
  // coords closestIntersect = intersections[0];
  // cout << "(" << firstIntersect.x << ", " << firstIntersect.y << ")" << endl;
  // cout << "(" << closestIntersect.x << ", " << closestIntersect.y << ")" << endl;
  // cout << abs(closestIntersect.x) + abs(closestIntersect.y) << endl;
  long stepsFirstWireFirstIntersection = 0;
  coords curr(0, 0);
  int i = 0;
  // something's wrong with this function when using negative numbers or something
  while (curr.x != firstIntersect.x || curr.y != firstIntersect.y)
  {
    if (firstWireSteps[i].second == 'U' || firstWireSteps[i].second == 'D')
    {
      long lower, upper;
      if (firstWireSteps[i].second == 'D')
      {
        lower = curr.y - firstWireSteps[i].first;
        upper = curr.y;
      }
      else
      {
        lower = curr.y;
        upper = curr.y + firstWireSteps[i].first;
      }
      if (curr.x == firstIntersect.x && curr.y >= lower && curr.y <= upper)
      {
        if (firstWireSteps[i].second == 'D')
          stepsFirstWireFirstIntersection += (curr.y - firstIntersect.y);
        else
          stepsFirstWireFirstIntersection += (firstIntersect.y - curr.y);
        curr = firstIntersect;
        break;
      }
      else
      {
        stepsFirstWireFirstIntersection += firstWireSteps[i].first;
        if (firstWireSteps[i].second == 'U')
          curr.y += firstWireSteps[i].first;
        else
          curr.y -= firstWireSteps[i].first;
      }
    }
    else
    {
      long lower, upper;
      if (firstWireSteps[i].second == 'L')
      {
        lower = curr.x - firstWireSteps[i].first;
        upper = curr.x;
      }
      else
      {
        lower = curr.x;
        upper = curr.x + firstWireSteps[i].first;
      }
      if (curr.y == firstIntersect.y && curr.x >= lower && curr.x <= upper)
      {
        if (firstWireSteps[i].second == 'L')
          stepsFirstWireFirstIntersection += (curr.x - firstIntersect.x);
        else
          stepsFirstWireFirstIntersection += (firstIntersect.x - curr.x);
        curr = firstIntersect;
        break;
      }
      else
      {
        stepsFirstWireFirstIntersection += firstWireSteps[i].first;
        if (firstWireSteps[i].second == 'R')
          curr.x += firstWireSteps[i].first;
        else
          curr.x -= firstWireSteps[i].first;
      }
    }
    i++;
  }
  cout << stepsFirstWireFirstIntersection + stepsSecondWireFirstIntersection << endl;
}
