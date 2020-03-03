#include <bits/stdc++.h>
#define ios ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
using namespace std;

int n, m;

bool is_enough(int k, vector<int> &v) {
	int prev = 0;

	for(int i = 0; i < n; i++) {
		int mx = min(v[i]+k, m-1);

		if(mx < prev)
			return false;

		int mn = v[i];
		if(v[i]+k >= m + prev)
			mn = prev;

		prev = max(prev, mn);
	}

	return true;
}

int main() {
	cin >> n >> m;

	vector<int>v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());

	long long lo = -1, hi = m-1;
	while(lo+1 < hi) {
		long long mid = (lo + hi)/2;

		if(is_enough(mid, v)) {
			hi = mid;
		else
			lo = mid;
		}
	}
	cout << hi << endl;

}