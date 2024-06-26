# 단지번호붙이기(Silver 1) - 2667번
- [링크](https://www.acmicpc.net/problem/2667)

### 문제
<그림 1>과 같이 정사각형 모양의 지도가 있다. 1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다. 철수는 이 지도를 가지고 연결된 집의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다. 여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 대각선상에 집이 있는 경우는 연결된 것이 아니다. <그림 2>는 <그림 1>을 단지별로 번호를 붙인 것이다. 지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.

![image](https://github.com/Lcrescent3es/Lcrescent3es/assets/112841705/f39bf383-b170-4fb5-9baa-77d4f97ccf32)

### 입력
첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고, 그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.

### 출력
첫 번째 줄에는 총 단지수를 출력하시오. 그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.

### 알고리즘 분류
- 그래프 이론
- 그래프 탐색
- 너비 우선 탐색
- 깊이 우선 탐색

### 풀이
#### 조건
1. 입력이 NxN 배열
2. 단지가 몇개 나올지 모름
3. 단지 안에 건물이 몇개인지 세어야함
4. 단지 안에 건물을 오름차순 정렬해야함
5. 단지가 어디부터 어디까지인지 모름

#### 해결법
- dfs를 실행하기 전 단지 수를 체크
- 깊이 우선 탐색(dfs)로 모든 배열을 탐색해서 단지를 체크
- dfs도중 단지 내 건물 수를 체크
- 단지 내 건물 수를 벡터에 넣어, sort()로 오름차순 정렬

#### 결과
![image](https://github.com/Lcrescent3es/Lcrescent3es/assets/112841705/5b02fafe-e8aa-40e9-843c-291b00ad293f)
