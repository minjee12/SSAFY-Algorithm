#include<stdc++.h>
using namespace std;

int N, maxi=-987654321, mini=987654321, ops[4] = { 0, };
vector<int> numbers;
vector<int> operators;

void inserting(int depth)
{
	if (depth == N-1)
	{
		int sum = numbers[0];
		for (int i = 0; i < operators.size(); ++i)
		{
			if (operators[i] == 0)
				sum += numbers[i + 1];
			else if (operators[i] == 1)
				sum -= numbers[i + 1];
			else if (operators[i] == 2)
				sum *= numbers[i + 1];
			else 
				sum /= numbers[i + 1];
		}
		maxi = max(maxi, sum);
		mini = min(mini, sum);
		return;
	}
	for (int i = 0; i < 4; ++i)
	{
		if (!ops[i]) continue;
		ops[i]--;
		operators.push_back(i);
		inserting(depth + 1);
		operators.pop_back();
		ops[i]++;
	}

}


int main()
{
	int tmp;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		scanf(" %d", &tmp);
		numbers.push_back(tmp);
	}
	for (int i = 0; i < 4; ++i)
	{
		scanf(" %d", &ops[i]);
	}
	inserting(0);
	printf("%d\n%d", maxi, mini);
	return 0;
}
