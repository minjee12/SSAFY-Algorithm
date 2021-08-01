// ������ �����ֱ�(1)

#include <iostream>

using namespace std;

int n = 0; // �ǿ����� ����

int opt[4] = { 0, }; // ������ ����

int opr[100] = { 0, }; // �ǿ����� �迭

int min_result = 1000000001;
int max_result = -1000000001;

// opr1 : �ǿ�����1, opr2 : �ǿ�����2, opt : ������
int calc(int opr1, int opr2, int opt)
{
	switch (opt)
	{
	case 0: // +
		return opr1 + opr2;
	case 1: // -
		return opr1 - opr2;
	case 2: // ��
		return opr1 * opr2;
	case 3: // ��
		return opr1 / opr2;
	}
}

// level : ����, before : ���� ��� ���
void rec(int level, int before)
{
	if (level == (n - 1))
	{
		int result = 0;
		
		for (int i = 0; i < 4; i++)
		{
			if (opt[i])
			{
				result = calc(before, opr[level], i);
			}
		}
		max_result = result > max_result ? result : max_result;
		min_result = result < min_result ? result : min_result;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (opt[i])
		{
			opt[i]--;
			rec(level + 1, calc(before, opr[level], i));
			opt[i]++;
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> opr[i];
	}

	for (int i = 0; i < 4; i++)
	{
		cin >> opt[i];
	}

	rec(1, opr[0]);

	cout << max_result << endl << min_result;
	return 0;
}