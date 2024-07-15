#include<iostream>
#include<algorithm>
#define NUM 1000000000;

using namespace std;
typedef long long ll;
ll n, k;
ll dp[204][204];
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> n >> k;
	for (int i = 0; i <= n; i++) {
		dp[1][i] = 1;
	}
	for (int i = 2; i <= k; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k <= j; k++) {
				dp[i][j] += dp[i - 1][k];
			}
			dp[i][j] %= NUM;
		}
	}
	cout << dp[k][n];
	return 0;
}
