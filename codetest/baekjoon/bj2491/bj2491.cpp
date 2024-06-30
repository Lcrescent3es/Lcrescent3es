#include <iostream>
#include <vector>
using namespace std;
vector<int> nums;
int N, answer, cnt = 1;
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> N;
    nums = vector<int>(N);

    for (int& num : nums){
        cin >> num;
    }
    for (int i = 0; i < N - 1; ++i) {
        if (nums[i] <= nums[i + 1]) {
            cnt++;
        }
        else{
            answer = max(answer, cnt);
            cnt = 1;
        }
    }
    answer = max(answer, cnt);
    cnt = 1;

    for (int i = 0; i < N - 1; ++i) {
        if (nums[i] >= nums[i + 1]) {
            ++cnt;
        }
        else {
            answer = max(answer, cnt);
            cnt = 1;
        }
    }
    answer = max(answer, cnt);

    cout << answer;
    return 0;
}
