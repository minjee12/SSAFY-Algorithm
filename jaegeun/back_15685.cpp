#pragma warning(disable:4996)
#include<iostream>
#define endl "\n"
#define MAX 101

using namespace std;

int M[MAX][MAX] = { 0, };

int dx[4] = { 0, -1, 0, 1 };
int dy[4] = { 1, 0, -1, 0 };


int main(void)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	// 입출력 최적화

	int n = 0;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int x, y, d, g;
		cin >> y >> x >> d >> g;
		
		int curve[1024] = { 0, };  // 최대 2^10개의 점
		int len = 1;  // 커브의 길이
		curve[0] = d; // 시작점에서의 방향

		M[x][y] = 1;
		for (int j = 0; j < g; j++) // 세대 수 만큼 이어 나감
		{
			for (int k = len - 1; k > -1; k--)
			{
				curve[len++] = (curve[k] + 1) % 4;  // 방향의 변화를 계속 추가해줌
			}
		}
		
		for (int i = 0; i < len; i++)  // 방향의 변화를 맵에 반영
		{
			x = dx[curve[i]] + x;
			y = dy[curve[i]] + y;
			M[x][y] = 1;
		}
	}
	
	int count = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++)
		{
			if (M[i][j])  // 4점이 모두 1인 경우 세기
			{
				if (M[i + 1][j] && M[i][j + 1] && M[i + 1][j + 1])
				{
					count++;
				}
			}
		}
	}
	cout << count << endl;;
}