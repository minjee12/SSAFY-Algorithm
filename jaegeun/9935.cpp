// 문자열 폭발
// https://www.acmicpc.net/problem/9935

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#define MAX 1000001
using namespace std;

int result_length = 0; // result에 채워진 문자열 길이
char result[MAX];

int get_same_length(string sub_str, string boom)
{
	int n = 0;
	for (int i = 0; i < boom.length(); i++)
	{
		if (sub_str[i] != boom[i]) break;
		n++;
	}
	return n;
}

void boom_string(string str, string boom)
{
	int str_length = str.length();
	int boom_length = boom.length();
	
	vector<int> split_index;
	int str_index = 0; // 탐색할 문자열 인덱스
	while (str_index < str.length())
	{
		if (str[str_index] == boom[0]) // 첫 글자가 같을 때
		{
			string sub_str = str.substr(str_index, boom_length);
			int same_length = get_same_length(sub_str, boom);
			if (same_length == boom_length) // 모두 같을 때
			{
				str_index += boom_length; // 탐색할 문자열 index 증가
			}
			else // 일부만 같을 때 같은 길이만큼만 복사
			{
				split_index.push_back(result_length);
				memcpy(&result[result_length], &str[str_index], sizeof(char) * same_length);
				result_length += same_length; // 복사한 만큼 result 길이 증가
				str_index += same_length; // 탐색할 문자열 index 증가
			}
		}
		else // 첫 글자가 다를 때 한 글자만 result에 복사
		{
			memcpy(&result[result_length], &str[str_index], sizeof(char) * 1);
			result_length++; // 복사한 만큼 result 길이 증가
			str_index++;
		}
		
		if (split_index.size()) // 일부만 같은 문자열이 있을 때
		{
			int split_index_length = split_index.size();
			for(int i = split_index_length - 1; i >= 0; i--)
			{
				// 비교할 문자열의 길이가 boom_length의 길이보다 작으면 종료
				if (result_length - split_index[i] < boom_length) break; 
				char result_sub_str[40] = { 0, };
				memcpy(result_sub_str, &result[split_index[i]], boom_length);
				string sub_str = result_sub_str;
				int same_length = get_same_length(sub_str, boom);
				if (same_length == boom_length) // 길이가 같을 경우 그 길이만큼 지워줌
				{
					memset(&result[split_index[i]], 0, sizeof(char) * boom_length);
					result_length = split_index[i]; // result 길이 업데이트
				}
				split_index.pop_back();
			}
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	string str, boom; cin >> str >> boom;

	boom_string(str, boom);
	if (result_length) cout << result << "\n";
	else cout << "FRULA" << "\n";
	return 0;
}