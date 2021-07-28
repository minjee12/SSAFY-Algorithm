#include <iostream>
#include <queue>

using namespace std;

typedef struct {
	int _x;
	int _y;
}pos;

int dx[4] = { -1, 1, 0 ,0 };
int dy[4] = { 0 ,0 , -1, 1};

int map[101][101] = { 0, };
int n = 0, l = 0, r = 0;

int map_bfs[101][101] = { 0, };

bool bfs(int sx, int sy)
{
	int pop_sum = map[sx][sy];
	int country_count = 1;
	queue <pos> q;
	pos start = { sx, sy };
	map_bfs[sx][sy] = 1;
	q.push(start);
	bool flag = false; // �α��� ���̳��� ������ ���� �� true
	while (q.size())
	{
		pos c_pos = q.front();
		q.pop();

		// 4���� Ž��
		for (int i = 0; i < 4; i++) 
		{
			// ���� ��ġ �ε���
			int n_x = c_pos._x + dx[i];
			int n_y = c_pos._y + dy[i];

			// ���� ���� ���� ���
			if ((0 <= n_x && n_x < n) && (0 <= n_y && n_y < n))
			{
				// �湮 ���� ���
				if (map_bfs[n_x][n_y] == 0)
				{
					// �α��� ����
					int pop_diff = abs(map[c_pos._x][c_pos._y] - map[n_x][n_y]);
					// ���̰� L�̻� R������ ��
					if ((pop_diff >= l) && (pop_diff <= r))
					{
						flag = true;
						pop_sum += map[n_x][n_y];
						country_count++;
						//cout << "(" << c_pos._x << "," << c_pos._y << ")";
						//cout << "to(" << n_x << "," << n_y << ")" << endl;
						map_bfs[n_x][n_y] = 1;
						pos next = { n_x, n_y };
						q.push(next);
					}
				}
			}
		}
	}
	if (!flag)
		map_bfs[sx][sy] = 0;
	else
	{
		int pop_mean = pop_sum / country_count;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (map_bfs[i][j] == 1)
				{
					map[i][j] = pop_mean;
					map_bfs[i][j] = -1; // �ʱ�ȭ
				}
			}
		}
	}
	return flag;
}

void pop_movm()
{
	int pop_sum = 0;
	int country_count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map_bfs[i][j] == 1)
			{
				pop_sum += map[i][j];
				country_count++;
			}
		}
	}

}

int main()
{
	freopen_s(new FILE*, "input.txt", "r", stdin);

	cin >> n >> l >> r;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
		}
	}
	
	int result = 0;
	bool is_moved = false;
	while (1)
	{
		is_moved = false;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (map_bfs[i][j] == 0)
				{
					if (bfs(i, j))
						is_moved = true;
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			memset(map_bfs[i], 0, sizeof(int) * n);
		}	

		if (!is_moved) {
			break;
		}
		result++;
	}
	
	cout << result;
	return 0;
}