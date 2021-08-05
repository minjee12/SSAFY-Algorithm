// 적록색약

#include <iostream>
#include <queue>

#define endl '\n'
#define MAX_SIZE 101
using namespace std;

int N = 0;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

char pic[MAX_SIZE][MAX_SIZE] = { 0, };

int visited[MAX_SIZE][MAX_SIZE] = { 0, };

void bfs(int x, int y, char color)
{
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	visited[x][y] = 1;
	while (q.size())
	{
		pair<int, int> c_pos = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = dx[i] + c_pos.first;
			int ny = dy[i] + c_pos.second;

			if (0 <= nx && nx < N && 0 <= ny && ny < N) {
				if (!visited[nx][ny])
				{
					if (pic[nx][ny] == color)
					{
						visited[nx][ny] = 1;
						q.push(make_pair(nx, ny));
					}
				}
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int result = 0;
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> pic[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j]) {
				bfs(i, j, pic[i][j]);
				result++;
			}
		}
	}
	memset(visited, 0, sizeof(visited));
	cout << result << " ";
	result = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (pic[i][j] == 'G')
			{
				pic[i][j] = 'R';
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j]) {
				bfs(i, j, pic[i][j]);
				result++;
			}
		}
	}
	cout << result;
	return 0;

}