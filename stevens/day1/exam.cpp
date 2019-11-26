#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n;
    cin >> m;
    // cout << n << endl;
    // cout << m << endl;
    string question;
    vector<string> answers;
    for (int i = 0; i < n; i++) {
        cin >> question;
        answers.push_back(question);
    }
    sort(answers.begin(), answers.end());
    vector<int> maxPoints;
    for (int i = 0; i < m; i++) {
        int maxCount = 1;
        int currentCount = maxCount;
        for (int j = 1; j < answers.size(); j++) {
            if (answers[j][i] == answers[j-1][i]) {
                currentCount++;
            } else {
                currentCount = 1;
            }
            if (currentCount > maxCount) {
                maxCount = currentCount;
            }
        }
        maxPoints.push_back(maxCount);
    }
    vector<int> questionPoints;
    /*
    for (int a : maxPoints) {
        cout << a << endl;
    }
    */
    int res = 0;
    for (int i = 0; i < m; i++) {
        int a;
        cin >> a;
        res += a * maxPoints[i];
        questionPoints.push_back(a);
    }
    cout << res << endl;
    /*
    for (int a : questionPoints) {
        cout << a << endl;
    }
    */
}
