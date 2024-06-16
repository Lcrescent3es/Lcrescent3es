//https://www.acmicpc.net/problem/2667
// 단지번호붙이기 - Silver 1
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int map[25][25];
bool visited[25][25];
vector<int> vec;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int N;
int cnt;

void dfs(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= N || nx < 0 || ny >= N || ny < 0) continue;
        if (!(visited[nx][ny]) && (map[nx][ny] == 1)) {
            visited[nx][ny] = true;
            cnt += 1;
            dfs(nx, ny);
        }
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(NULL); cout.tie(NULL);
    
    int res = 0;
    string str;
    // 입력
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
            map[i][j] = str[j]-'0';
        }
    }

    // 알고리즘
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 1 && !(visited[i][j])) {
                visited[i][j] = true;
                res++; // 단지 숫자
                cnt = 1; // 시작 건물 카운트+1
                dfs(i, j);
                vec.push_back(cnt);
            }
        }
    }
    // 단지 내 건물 숫자 오름차순 정렬
    sort(vec.begin(), vec.end());

    // 출력
    // 1. 총 단지수
    cout << res << '\n';
    // 2. 단지별 집의 수(오름차순 정렬 후 한줄에 하나씩)
    for (int i = 0; i < res; i++) {
        cout << vec[i] << '\n';
    }
	return 0;
}
