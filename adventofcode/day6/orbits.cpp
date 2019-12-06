/**
 * 
 */

#include <bits/stdc++.h>

using namespace std;

const string me = "YOU", santa = "SAN", com = "COM";
const char splitChar = ')';

struct Node
{
  string key;
  Node *parent;
  unordered_set<Node *> children;
  Node(string _key, Node *_parent) : key{_key}, parent{_parent} {};
  Node(){};
};

void cleanup(unordered_map<string, Node *> nodes)
{
  for (pair<string, Node *> keyValue : nodes)
    delete keyValue.second;
}

uint64_t countPaths(Node *node, uint64_t level)
{
  if (node == nullptr)
    return level;
  uint64_t res = 0;
  for (Node *child : node->children)
    res += countPaths(child, level + 1);
  return res + level;
}

int main()
{
  string line;
  ifstream thefile("orbits.txt");
  istringstream linestream;
  linestream.str(line);
  unordered_map<string, Node *> nodes;
  istringstream splitstream;
  string center, orbiting;
  Node *root = nullptr, *start = nullptr, *end = nullptr;
  while (getline(thefile, line))
  {
    splitstream.str(line);
    getline(splitstream, center, splitChar);
    getline(splitstream, orbiting, splitChar);
    if (nodes.find(center) == nodes.end())
    {
      Node *centerNode = new Node(center, nullptr);
      nodes[center] = centerNode;
      if (center == com)
        root = nodes[center];
    }
    if (nodes.find(orbiting) == nodes.end())
    {
      Node *orbitingNode = new Node(orbiting, nodes[center]);
      nodes[orbiting] = orbitingNode;
    }
    else
    {
      nodes[orbiting]->parent = nodes[center];
    }
    nodes[center]->children.insert(nodes[orbiting]);
    if (orbiting == me)
      start = nodes[orbiting];
    else if (orbiting == santa)
      end = nodes[orbiting];
    splitstream.clear();
  }
  if (root == nullptr || start == nullptr || end == nullptr)
  {
    cerr << "did not find center of mass or me or santa" << endl;
    cleanup(nodes);
    return -1;
  }
  cout << "num paths: " << countPaths(root, 0) << endl;
  unordered_set<Node *> myPathNodes;
  list<Node *> myPath;
  Node *current_node = start;
  while (current_node != end && current_node != root)
  {
    myPath.push_back(current_node);
    myPathNodes.insert(current_node);
    current_node = current_node->parent;
  }
  myPath.push_back(current_node);
  myPathNodes.insert(current_node);
  list<Node *> santaPath;
  current_node = end;
  while (myPathNodes.find(current_node) == myPathNodes.end())
  {
    santaPath.push_front(current_node);
    current_node = current_node->parent;
  }
  santaPath.push_front(current_node);
  while (myPath.back() != santaPath.front())
    myPath.pop_back();
  santaPath.pop_front();
  myPath.insert(myPath.end(), santaPath.begin(), santaPath.end());
  // for (list<Node *>::iterator it = myPath.begin(); it != myPath.end(); it++)
  //   cout << (*it)->key << ", ";
  // cout << endl;
  cout << "transfers: " << myPath.size() - 3 << endl;
  cleanup(nodes);
}
