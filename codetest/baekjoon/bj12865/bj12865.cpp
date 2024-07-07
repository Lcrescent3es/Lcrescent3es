// https://www.acmicpc.net/problem/12865
// 평범한 배낭 - Gold 5
#include <iostream>
#include <vector>
using namespace std;

vector <pair<int, int>> v;
int n, k, dp[102][100002] = { 0, };

int main(int argc, const char* argv[]) {

    cin >> n >> k;

    v.push_back({ 0,0 });
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({ x,y });
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            int weight = v[i].first; //무게
            int value = v[i].second; //가치

            if (weight <= j) { //최대무게 이하
                if ((value + dp[i - 1][j - weight]) > dp[i - 1][j])
                    dp[i][j] = value + dp[i - 1][j - weight];
                else
                    dp[i][j] = dp[i - 1][j];
            }
            else //최대무게 초과
                dp[i][j] = dp[i - 1][j];
        }
    }

    cout << dp[n][k];

    return 0;
}
