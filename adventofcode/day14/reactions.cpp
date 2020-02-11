#include <bits/stdc++.h>

using namespace std;

#define fileName "reactions.txt"
#define target "FUEL"
#define raw "ORE"

struct reaction {
  int amountProduced;
  vector<pair<int, string>> amountRequired;
  reaction(int _amountProduced, vector<pair<int, string>> _amountRequired)
      : amountProduced{_amountProduced}, amountRequired{_amountRequired} {};
  reaction() {};
};

struct Node {
  vector<Node *> children;
  string key;
  Node() {};
  Node(string _key) : key{_key} {};
};

int main(const int argc, char *const argv[]) {
  string line;
  ifstream thefile(fileName);
  string splitLine;
  istringstream splitLineStream;
  string splitComma;
  istringstream splitCommaStream;
  string splitQuantity;
  istringstream splitQuantityStream;
  istringstream amountToInt;
  unordered_map<string, reaction> possibleReactions;
  unordered_map<string, Node *> nodes;
  while (getline(thefile, line)) {
    splitLineStream.str(line);
    vector<pair<int, string>> amountRequired;
    for (int i = 0; i < 2; i++) {
      getline(splitLineStream, splitLine, '=');
      splitCommaStream.str(splitLine);
      while (getline(splitCommaStream, splitComma, ',')) {
        if (i == 0) {
          if (splitComma.front() == ' ') {
            splitComma = splitComma.substr(1);
          }
          if (splitComma.back() == ' ') {
            splitComma.pop_back();
          }
        } else {
          splitComma = splitComma.substr(2);
        }
        splitQuantityStream.str(splitComma);
        int amount;
        for (int j = 0; j < 2; j++) {
          getline(splitQuantityStream, splitQuantity, ' ');
          if (j == 0) {
            amountToInt.str(splitQuantity);
            if (!(amountToInt >> amount) || amount <= 0) {
              cerr << "invalid amount found" << endl;
              return -1;
            }
            amountToInt.clear();
          } else {
            if (i == 0) {
              if (nodes.find(splitQuantity) == nodes.end()) {
                nodes[splitQuantity] = new Node(splitQuantity);
              }
              amountRequired.push_back(pair<int, string>(amount, splitQuantity));
            } else {
              possibleReactions[splitQuantity] = reaction(amount, amountRequired);
              if (nodes.find(splitQuantity) != nodes.end()) {
                nodes[splitQuantity] = new Node(splitQuantity);
              }
              for (pair<int, string> & required : amountRequired) {
                nodes[splitQuantity]->children.push_back(nodes[required.second]);
              }
            }
          }
        }
        splitQuantityStream.clear();
      }
      splitCommaStream.clear();
    }
    splitLineStream.clear();
    amountRequired.clear();
  }
  if (possibleReactions.find(target) == possibleReactions.end()) {
    cerr << "cannot find target" << endl;
    return -1;
  }
  // topological_sort(nodes);
  // gets the nodes in order
  queue<string> itemQueue;
  itemQueue.push(target);
  // unordered_map<string, int> totalRequired;
  /*
  size_t rawRequired = 0;
  unordered_map<string, int> currentAmounts;
  while (itemQueue.size() > 0) {
    if (possibleReactions.find(itemQueue.front()) == possibleReactions.end()) {
      cerr << "cannot find key " << itemQueue.front() << endl;
      return -1;
    }
    for (pair<int, string> & required : possibleReactions[itemQueue.front()].amountRequired) {
      if (required.second == raw) {
        rawRequired += required.first;
      } else {
        itemQueue.push(required.second);
      }
      int alreadyHave = 0;
      if (currentAmounts.find(required.second) != currentAmounts.end()) {
        alreadyHave = currentAmounts[required.second];
      }
      int needToGet = alreadyHave > required.first ? 0 : required.first - alreadyHave;
      currentAmounts[required.second] = alreadyHave < required.first ? 0 : alreadyHave - required.first;
      int numProducedPerReaction = possibleReactions[required.second].amountProduced;
      int numReactions = ceil((float)needToGet / numProducedPerReaction);
      for (int i = 0; i < numReactions; i++) {
        if (required.second == raw) {
          rawRequired += required.first;
        } else {
          itemQueue.push(required.second);
        }
      }
    }
    if (currentAmounts.find(itemQueue.front()) == currentAmounts.end()) {
      currentAmounts[itemQueue.front()] = possibleReactions[itemQueue.front()].amountProduced;
    } else {
      currentAmounts[itemQueue.front()] += possibleReactions[itemQueue.front()].amountProduced;
    }
    itemQueue.pop();
  }
  cout << "requires " << rawRequired << " ore" << endl;
  */
}
