//Problem 1195/B on codeforces.com



#include <iostream>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;

	int lo = 0, hi = n+1;

	while(lo+1 < hi) {
		int e = (lo + hi)/2;
		int p = n - e;

		long long guess_k = 1ll*p*(p+1)/2 - e;

		if(guess_k >= k) {
			lo = e;
		} else {
			hi = e;
		}
	}

	cout << lo << endl;
	return 0;
}