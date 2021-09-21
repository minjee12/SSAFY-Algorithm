// 나는야 포켓몬 마스터 이다솜
// https://www.acmicpc.net/problem/1620

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);

	int n, m; cin >> n >> m;
	map<string, int> map_name;
	map<int, string> map_index;
	for (int i = 1; i <= n; i++)
	{
		string name; cin >> name;
		map_name.insert({ name, i });
		map_index.insert({ i, name });
	}

	for (int i = 0; i < m; i++)
	{
		string inp; cin >> inp;
		if (isdigit(int(inp[0])))
		{
			int index = stoi(inp);
			cout << map_index[index] << '\n';
		}
		else
		{
			cout << map_name[inp] << '\n';
		}
	}

	return 0;
}