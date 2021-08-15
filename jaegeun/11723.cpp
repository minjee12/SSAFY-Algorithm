// 집합
// https://www.acmicpc.net/problem/11723

#include <iostream>
#include <bitset>
#include <string>

using namespace std;

#define endl '\n'

bitset<21> bit;

void addElement(int element)
{
	bit[element] = 1;
}
void removeElement(int element)
{
	bit[element] = 0;
}
void checkElement(int element)
{
	if (bit.test(element))
	{
		cout << 1 << endl;
	}
	else
	{
		cout << 0 << endl;
	}
}
void toggleElement(int element)
{
	bit.flip(element);
}
void changeAll()
{
	bit.set();
}
void emptySet()
{
	bit.reset();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	freopen_s(new FILE*, "text.txt", "r", stdin);

	int N = 0;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		string cmd;
		cin >> cmd;

		if (cmd == "add")
		{
			int e = 0;
			cin >> e;
			addElement(e);
		}
		else if (cmd == "remove")
		{
			int e = 0;
			cin >> e;
			removeElement(e);
		}
		else if (cmd == "check")
		{
			int e = 0;
			cin >> e;
			checkElement(e);
		}
		else if (cmd == "toggle")
		{
			int e = 0;
			cin >> e;
			toggleElement(e);
		}
		else if (cmd == "all")
		{
			changeAll();
		}
		else if (cmd == "empty")
		{
			emptySet();
		}
	}
}