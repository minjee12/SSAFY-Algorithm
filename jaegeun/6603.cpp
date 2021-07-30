#include <iostream>

using namespace std;

int arr_num[12] = { 0, };
int used[12] = { 0, };
int num = 0;
int perm[6] = { 0, };
void func(int level, int index)
{
	if (level == 6)
	{
		for (int i = 0; i < 6; i++)
			cout << perm[i] << " ";
		cout << endl;
		return;
	}

	for (int i = 0; i < num; i++)
	{
		if (used[i]) continue;
		if (i < index) continue; // 인덱스 이전 수는 고려하지 않음
		used[i] = 1;
		perm[level] = arr_num[i];
		func(level + 1, i);
		perm[level] = 0;
		used[i] = 0;
	}
}

int main()
{
	//freopen_s(new FILE*, "input.txt", "r", stdin);
	while (1)
	{
		cin >> num;
		if (num == 0) break;
		for (int i = 0; i < num; i++)
		{
			cin >> arr_num[i];
		}
		func(0, 0);
		cout << endl;
	}

    return 0;
} 