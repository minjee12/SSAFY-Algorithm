#include <iostream>
#include <queue>
using namespace std;

int n, d, start, res;
int arr[51] = { 0, };

void bfs() {
	queue<int> q;
	if (arr[start] == -1) {
		q.push(start);
	}

	while (!q.empty()) {
		int f = q.front();
		q.pop();

		int flag = 0;
		for (int i = 0; i < n; i++) {
			if (arr[i] == f) {
				flag = 1;
				q.push(i);
			}
		}
		if (flag == 0) res++;
	}
}

void del_node() {
	queue<int> q;
	q.push(d);
	
	while (!q.empty()) {
		int f = q.front();
		arr[f] = -2;
		q.pop();

		for (int i = 0; i < n; i++) {
			if (arr[i] == f) {
				q.push(i);
			}
		}
	}
}

int main() {

	//input
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		if (arr[i] == -1) start = i;
	}
	cin >> d;

	//노드 지우기
	del_node();
	//리프 노드 개수 구하기
	bfs();

	//output
	cout << res << "\n";

	return 0;
}