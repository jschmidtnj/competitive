#include <bits/stdc++.h>

using namespace std;

void printAnwer(bool type) {
    cout << (type ? "YES" : "NO") << endl;
}

int main() {
    string numInputsStr;
    getline(cin, numInputsStr);
    stringstream strStream;
    strStream.str(numInputsStr);
    int numInputs;
    if (!(strStream >> numInputs)) {
        return false;
    }
    string line;
    for (int i = 0; i < numInputs; i++) {
        getline(cin, line);
        // line here contains length of input
        getline(cin, line);
        // cout << line << endl;
        if (line.length() < 11) {
            printAnwer(false);
            continue;
        }
        bool gotAnswer = false;
        for (int j = 0; j <= line.length() - 11; j++) {
            if (line[j] == '8') {
                printAnwer(true);
                gotAnswer = true;
                break;
            }
        }
        if (!gotAnswer) {
            printAnwer(false);
        }
    }
}
