#include<stdc++.h>
using namespace std;


int turn(int state,int way) // 1 : CW, -1: CCW 
{
	if (way == 1)
		return ((state & 1) << 7) | (state >> 1);
	else
		return ((state & (1 << 7)) >> 7) | (state << 1) & (255);
}
void checkTurn(int cnt, int way, vector<int>& wheel, vector<int> &willturn)	 // 6시 1<< 5, 9시 1<< 1
{
	if (cnt == 0)
	{
		willturn[0] = way;
		if (((wheel[0] & 32)>>4 != (wheel[1] & 2)) && willturn[1] == 0)
		{
			willturn[1] = -way;
			checkTurn(1, -way, wheel, willturn);
		}
		else
			return;
	}
	else if (cnt == 3)
	{
		willturn[3] = way;
		if (((wheel[3] & 2) != (wheel[2] & 32)>>4 ) && willturn[2] == 0)
		{
			willturn[2] = -way;
			checkTurn(2, -way, wheel, willturn);
		}
		else
			return;

	}
	else
	{
		willturn[cnt] = way;
		if (((wheel[cnt] & 2) != (wheel[cnt-1] & 32)>>4) && willturn[cnt - 1] == 0)
		{
			willturn[cnt - 1] = -way;
			checkTurn(cnt - 1, -way, wheel, willturn);
		}
		if (((wheel[cnt] & 32)>>4 != (wheel[cnt+1]&2)) && willturn[cnt + 1] == 0)
		{
			willturn[cnt + 1] = -way;
			checkTurn(cnt + 1, -way, wheel, willturn);
		}
		else
			return;
	}
}

int main()
{
	vector<int> wheel(4);
	vector<int> willturn (4);
	int N,cnt,way,answer=0;
	string strin;
	for (int i = 0; i < 4; ++i)
	{
		getline(cin, strin);
		for (int j = 0; j < strin.length(); ++j)
		{
			if (strin[j] == '1')
				wheel[i] |= (1 << (7-j));
		}
	}
	scanf(" %d", &N);
	while (N--) {
		fill(willturn.begin(), willturn.end(), 0);
		scanf("%d %d", &cnt, &way);
		checkTurn(cnt-1, way, wheel,willturn);
		for (int i = 0; i < 4; ++i)
		{
			if (willturn[i] != 0)
				wheel[i] = turn(wheel[i], willturn[i]);
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		if (wheel[i] & (1 << 7))
			answer |= (1 << i);
	}
	printf("%d", answer);
	return 0;
}
