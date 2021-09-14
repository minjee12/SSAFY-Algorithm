// Z
// https://www.acmicpc.net/problem/1074

#include <iostream>
#include <cmath>
#define MAX 32768

using namespace std;

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int N, r, c;
	cin >> N >> r >> c;
	int range = pow(2, N); // 초기 범위

	int counter = 0;
	while (true)
	{
		if (range == 2) break;
		int border = range / 2;
		if (r < border && c < border) // 1번 영역
		{
			counter += 0;
		}
		else if (r < border && c >= border) // 2번 영역
		{
			counter += range * (border / 2);
			c -= border;
		}
		else if (r >= border && c < border) // 3번 영역
		{
			counter += range * (border / 2) * 2;
			r -= border;
		}
		else // 4번 영역
		{
			counter += range * (border / 2) * 3;
			r -= border;
			c -= border;
		}
		range = border;
	}
	if (r == 0 && c == 1)
		counter += 1;
	if (r == 1 && c == 0)
		counter += 2;
	if (r == 1 && c== 1)
		counter += 3;

	cout << counter << '\n';
	return 0;
}