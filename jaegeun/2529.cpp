#include <iostream>
#include <string>

using namespace std;


uint64_t n = 0;
string max_result = "0";
string min_result = "99999999999";

char input[9] = { 0, };
int used[10] = { 0, };

char result[10] = { 0, };

void ABC(int level, int before)
{
	if (level == n + 1)
	{
		string str_result = result;
		if (str_result > max_result) max_result = str_result;
		if (str_result < min_result) min_result = str_result;
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		if (used[i]) continue;
		if (level > 0)
		{
			if (input[level - 1] == '<')
			{
				if (!(before < i)) continue;
			}
			else if (input[level - 1] == '>')
			{
				if (!(before > i)) continue;
			}
		}
		result[level] = char('0' +  i);
		used[i] = 1;
		ABC(level + 1, i);
		used[i] = 0;
		result[level] = 0;
	}
}

int main()
{
	freopen_s(new FILE *, "text.txt", "r", stdin);
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}
	

	ABC(0, 0);

	cout.width(n + 1);
	cout.fill('0');
	cout << max_result << endl;
	cout.width(n + 1);
	cout.fill('0');
	cout << min_result << endl;
	return 0;
}