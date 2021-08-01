#include<stdc++.h>
using namespace std;
vector<int> numbers;
int N;
int main()
{
	int tmp, result=0;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		scanf(" %d", &tmp);
		result = max(result, tmp);
		if (numbers.size() == 0)
			numbers.push_back(tmp);
		else if (numbers[numbers.size() - 1] >= 0 && tmp >= 0)
		{
			numbers[numbers.size() - 1] += tmp;
			result = max(result, numbers[numbers.size() - 1]);
		}
		else if (numbers[numbers.size() - 1] < 0 && tmp < 0)
			numbers[numbers.size() - 1] += tmp;
		else
			numbers.push_back(tmp);


		if (numbers.size() >= 3 && numbers[numbers.size() - 1] >= 0)
		{
			if (numbers[numbers.size() - 1] + numbers[numbers.size() - 2] >= 0 && numbers[numbers.size() - 3] + numbers[numbers.size() - 2] >= 0)
			{
				numbers[numbers.size() - 3] = numbers[numbers.size() - 3] + numbers[numbers.size() - 2] + numbers[numbers.size() - 1];
				numbers.pop_back();
				numbers.pop_back();
				result = max(result, numbers[numbers.size() - 1]);
			}
		}
		else if (numbers.size() >= 3 && numbers[numbers.size() - 1] < 0)
		{
			if (numbers[numbers.size() - 1] + numbers[numbers.size() - 2] < 0 && numbers[numbers.size() - 3] + numbers[numbers.size() - 2] < 0)
			{
				numbers[numbers.size() - 3] = numbers[numbers.size() - 3] + numbers[numbers.size() - 2] + numbers[numbers.size() - 1];
				numbers.pop_back();
				numbers.pop_back();
			}

		}
	}
	tmp = 0;
	for (int i = 0; i < numbers.size(); ++i)
	{
		tmp = max(numbers[i], tmp+numbers[i]);
		result = max(result, tmp);
	}
	printf("%d", result);
	return 0;
}
