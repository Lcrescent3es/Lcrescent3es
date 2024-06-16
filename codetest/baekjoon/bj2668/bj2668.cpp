
//https://www.acmicpc.net/problem/2668
// 숫자고르기 - Gold 5

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
// input 저장용 벡터
vector<int> vec;
bool visited[101];
// dfs 결과 저장용 세트
set<int> ans;
int N;
bool isRight = false;

void dfs(int start, int current) {
	if (visited[current-1]) {
		if (start == current) {
			visited[current-1] = false;
			isRight = true;
			ans.insert(current);
		}
		return;
	}
	visited[current-1] = true;
	dfs(start, vec[current-1]);
	if (isRight) {
		ans.insert(current);
		//ans.insert(vec[current]);
	}
	visited[current-1] = false;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int tempint = 0;
	// 입력
	cin >> N;
	for (int i = 1; i <= N; i++) {
		visited[i - 1] = false;
		cin >> tempint;
		vec.push_back(tempint);
	}

	// bfs
	for (int i = 0; i < N; i++) {
			visited[i] = true;
			dfs(i+1, vec[i]);
			isRight = false;
	}

	// 출력
	cout << ans.size() << '\n';
	for (auto o : ans) {
		cout << o << '\n';
	}
	return 0;
}
