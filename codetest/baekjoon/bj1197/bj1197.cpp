#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

int n[10001];
int find(int x) {
	if (n[x] == x)return x;
	else return n[x] = find(n[x]); 
}
void union(int x, int y) {
	x = find(x); 
	y = find(y); 
	n[y] = x; 
}
bool findParent(int x, int y) {
	x = find(x); 
	y = find(y); 
	if (x == y)return true;
	else return false; 
}
int main() {
	int vertex, e; 
	cin >> vertex >> e;
	int result = 0; 
	vector<pair<int, pair<int, int>>>v; 
	for (int i = 0; i < e; i++) {
		int a, b, c; 
		cin >> a >> b >> c; 
		v.push_back({ c,{a,b} }); 
	}
	sort(v.begin(), v.end()); 
	for (int i = 1; i <= vertex; i++)n[i] = i; 
	for (int i = 0; i < v.size(); i++) {
		if (!findParent(v[i].second.first, v[i].second.second)) {
			union(v[i].second.first, v[i].second.second); 
			result += v[i].first; 
		}
	}
	cout << result; 
}
