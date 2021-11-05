#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string s) {
	int answer = 21e8;
	int len = s.size();
	if (len == 1) return 1; //len�� 1�϶� ����ó��
	for (int cut = 1; cut <= len / 2; cut++) { //len�� 1�϶��� �ȵ���
		vector<pair<int, string> > v;
		for (int start = 0; start < len; start += cut) {
			string ss = "";
			if (start + cut <= len) { //������ �߶�����
				for (int i = 0; i < cut; i++) {
					ss += s[start + i];
				}

				if (!v.empty()) {
					if (v[v.size() - 1].second == ss) {
						v[v.size() - 1].first++;
					}
					else {
						v.push_back({ 1, ss });
					}
				}
				else {
					v.push_back({ 1, ss });
				}
			}
			else { //������ �ڸ��� ���� ���ڿ�
				for (int i = start; i < len; i++) {
					ss += s[i];
				}
				v.push_back({ 1, ss });
			}
		}
		int tmp = 0;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].first == 1) {
				tmp += v[i].second.length();
			}
			else {
				tmp += to_string(v[i].first).length() + v[i].second.length();
			}
		}

		if (answer > tmp) answer = tmp;
	}
	return answer;
}