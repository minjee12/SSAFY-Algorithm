// 색종이
// https://www.acmicpc.net/problem/2563

#include <iostream>

using namespace std;

int map[100][100] = { 0, };

void att(int x, int y)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[x + i][y + j] = 1;
        }
    }
}

int main()
{
    int t, x, y = 0;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        cin >> x >> y;
        att(x, y);
    }

    int count = 0;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            count += map[i][j];
        }
    }
    cout << count;
    return 0;

}