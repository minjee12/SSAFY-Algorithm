// 괄호 추가하기
// https://www.acmicpc.net/problem/16637

#include <iostream>
#include <cstring>
using namespace std;

int nums[10];
int num_size = 0;
char opts[10];
int opt_size = 0;

bool brakets[10]; // 괄호 여부
int braket_flag = 0; // 괄호 개수 () => 1개

int max_result = -21e8;

int calc_opt(int num1, int num2, char opt)
{
	if (opt == '+') return num1 + num2;
	if (opt == '*') return num1 * num2;
	if (opt == '-') return num1 - num2;
}

void remove_brakets(int* nums_dist, char* opts_dist)
{
	int num_index = 0; // 괄호 계산 이전 인덱스
	int opt_index = 0;
	int nums_dist_index = 0; // 목적지 인덱스
	int opts_dist_index = 0;
	while (true)
	{
		if (num_index > num_size || opt_index > opt_size) break; // 전체 숫자 탐색 종료
		if (brakets[num_index]) // 괄호일 경우
		{
			// 괄호 계산
			int result = calc_opt(nums[num_index], nums[num_index+1], opts[opt_index++]);
			// 계산 결과 추가
			nums_dist[nums_dist_index++] = result;
			// 괄호 이후 연산자 추가
			opts_dist[opts_dist_index++] = opts[opt_index++];
			num_index += 2;
		}
		else // 괄호 아닐 경우 숫자와 연산자 추가
		{
			nums_dist[nums_dist_index++] = nums[num_index++];
			opts_dist[opts_dist_index++] = opts[opt_index++];
		}
	}
}

void calc_result()
{
	int result = 0;
	int nums_rm_brakets[10] = { 0, };
	char opts_rm_brakets[10] = { 0, };

	if (braket_flag) // 괄호가 추가된 경우
	{
		// 괄호 없애기
		remove_brakets(nums_rm_brakets, opts_rm_brakets);
	}
	else // 괄호가 없는 경우 현재 입력 그대로 계산
	{
		memcpy(nums_rm_brakets, nums, sizeof(nums));
		memcpy(opts_rm_brakets, opts, sizeof(opts));
	}

	if (strlen(opts_rm_brakets)) // 결과 계산
	{
		int num_index = 0;
		int opt_index = 0;
		result = calc_opt(nums_rm_brakets[num_index], nums_rm_brakets[num_index + 1], opts_rm_brakets[opt_index++]);
		num_index += 2;
		while (true)
		{
			if (num_index >= num_size - braket_flag || opt_index >= opt_size - braket_flag) break;
			result = calc_opt(result, nums_rm_brakets[num_index++], opts_rm_brakets[opt_index++]);
		}
	}
	else result = nums_rm_brakets[0]; // 남은 연산자가 없을 경우
	max_result = result > max_result ? result : max_result; // 최댓값 저장
}

// level : 괄호 개수, basis : 최대 괄호 개수
void dfs(int level, int basis, int st_index)
{
	if (level == basis)
	{
		calc_result(); // 결과 계산
		return;
	}
	for (int i = st_index; i < num_size; i++)
	{
		if (i < num_size - 1 && !brakets[i]) // 괄호가 없을 경우
		{
			// 현재 인덱스, 현재 인덱스 + 1을 괄호로 만들어줌
			brakets[i] = 1; 
			brakets[i + 1] = 1;
			braket_flag += 1; // 괄호 개수 추가
			dfs(level + 1, basis, i + 2);
			// 탐색 종료 후 원상 복구
			brakets[i] = 0;
			brakets[i + 1] = 0;
			braket_flag -= 1;
		}
	}
}

int main()
{
	freopen_s(new FILE*, "text.txt", "r", stdin);
	int N; cin >> N;
	string str; cin >> str;
	for (int i = 0; i < N; i++)
	{
		if (i % 2)
		{
			opts[opt_size++] = str[i];
		}
		else
		{
			nums[num_size++] = int(str[i] - '0');
		}
	}
	for (int i = 0; i <= num_size / 2; i++)
	{
		dfs(0, i, 0);
	}
	cout << max_result << "\n";
	return 0;
}