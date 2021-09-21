// 암호 만들기
// https://www.acmicpc.net/problem/1759

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int L = 0, C = 0;

vector<char> alpha;
int used[26];
char password[15];

bool is_vowel(char c)
{
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
	return false;
}

void alpha_cnt(int& vowels, int& consonants)
{
	for (int i = 0; i < L; i++)
	{
		if (is_vowel(password[i])) vowels++;
		else consonants++;
	}
}

void dfs(int level, int before)
{
	if (level == L)
	{
		int vol = 0, con = 0;
		alpha_cnt(vol, con);
		if (vol < 1 || con < 2) return;
		cout << password << '\n';
		return;
	}

	for (int i = before; i < C; i++)
	{
		if (used[alpha[i] - 'a']) continue;
		password[level] = alpha[i];
		dfs(level + 1, i + 1);
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	cin >> L >> C;

	for (int i = 0; i < C; i++)
	{
		char c; cin >> c;
		alpha.push_back(c);
	}
	sort(alpha.begin(), alpha.end());

	dfs(0, 0);

	return 0;
}