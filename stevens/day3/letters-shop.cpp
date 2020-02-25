#include <bits/stdc++.h>
#define ios ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
using namespace std;

int main() {
	ios;

	int n, m;
	string s;
	cin >> n >> s >> m;

	vector<vector<int>> qs(n+1, vector<int>(26));
	for(int i=0;i<n;i++){
		qs[i+1] = qs[i];
		qs[i+1][s[i] - 'a']++;
	}
	
	for (int i=0;i<m;i++){
		string name;
		cin >> name;

		vector<int> name_count(26);
		for(char c : name) name_count[c - 'a']++;

		int lo = 0, hi = n;
		while(lo + 1 < hi){
			int mid = (lo+hi)/2;

			bool is_enough = true;
			for(int i=0;i<26;i++){
				if (name_count[i] > qs[mid][i]) 
					is_enough = false;
			}

			if (is_enough)
				hi = mid;
			else
				lo = mid;
		}

		cout << hi << "\n";

	}



	return 0;
}