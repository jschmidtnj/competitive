#include <bits/stdc++.h>
#define ios ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
using namespace std;

long long num_ops(int x, vector<int> &v) {
	int n = v.size();
	long ans = 0;

	for(int i = n/2; i < n; i++) {
		if(v[i] < x)
			ans += (x-v[i]);
		else
			break;
	}
}

int main() {
	int n, k;
	cin >> n >> k;

	vector<int>v(n);
	for(int i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());

	long long lo = 1, hi = 2e9+100;
	while(lo+1 < hi) {
		long long mid = (lo + hi)/2;

		if(num_ops(mid, v) <= k) {
			lo = mid;
		else
			hi = mid;
		}
	}
	cout << lo << endl;

}