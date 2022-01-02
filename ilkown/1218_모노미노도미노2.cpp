#include <iostream>
using namespace std;

int green[6][4] = {};
int blue[6][4] = {};
int N;
int score = 0;

void b_gravity(int d) {
	for(int y=d - 1;y>=0;y--){
		for (int x = 0; x < 4; x++) {
			if (blue[y][x] == 1) {
				if (blue[y + 1][x] == 1) continue;
				blue[y + 1][x] = 1;
				blue[y][x] = 0;
			}
		}
	}
}

void g_gravity(int d) {
	for (int y = d - 1; y >= 0; y--) {
		for (int x = 0; x < 4; x++) {
			if (green[y][x] == 1) {
				if (green[y + 1][x] == 1) continue;
				green[y + 1][x] = 1;
				green[y][x] = 0;
			}
		}
	}
}

int switch_y(int x) {
	switch (x) {
	case 0:
		return 3;
		break;
	case 1:
		return 2;
		break;
	case 2:
		return 1;
		break;
	case 3:
		return 0;
	}
}

void stack_blue(int t, int t_x ) {//y가 들어옴
	int s_y = -1;

	t_x = switch_y(t_x);

	for (int y = 5; y >= 0; y--) {
		if (blue[y][t_x] == 1) {
			s_y = y;
		}
	}

	if (t == 1) {
		//1x1
		if (s_y == -1) {
			blue[5][t_x] = 1;
		}
		else {
			blue[s_y - 1][t_x] = 1;
		}
	}
	else if (t == 2) {
		//1x2 -> blue == 2x1
		if (s_y == -1) {
			blue[5][t_x] = 1;
			blue[4][t_x] = 1;
		}
		else {
			blue[s_y - 1][t_x] = 1;
			blue[s_y - 2][t_x] = 1;
		}
	}
	else {
		//2x1 -> 1x2

		for (int y = 5; y >= 0; y--) {
			if (blue[y][t_x - 1] == 1 || blue[y][t_x] == 1) {
				s_y = y;
			}
		}
		if (s_y == -1) {
			blue[5][t_x] = 1;
			blue[5][t_x - 1] = 1;
		}
		else {
			blue[s_y - 1][t_x] = 1;
			blue[s_y - 1][t_x - 1] = 1;
		}
	}
}

void stack_green(int t, int t_x) {
	int s_y = -1;

	for (int y = 5; y >= 0; y--) {
		if (green[y][t_x] == 1) {
			s_y = y;
		}
	}

	if (t == 1) {
		//1x1
		if (s_y == -1) {
			green[5][t_x] = 1;
		}
		else {
			green[s_y - 1][t_x] = 1;
		}
	}
	else if (t == 2) {
		//1x2
		for (int y = 5; y >= 0; y--) {
			if (green[y][t_x + 1] == 1 || green[y][t_x]==1) {
				s_y = y;
			}
		}

		if (s_y == -1) {
			green[5][t_x] = 1;
			green[5][t_x + 1] = 1;
		}
		else {
			green[s_y - 1][t_x] = 1;
			green[s_y - 1][t_x + 1] = 1;
		}
	}
	else {
		//2x1
		if (s_y == -1) {
			green[5][t_x] = 1;
			green[4][t_x] = 1;
		}
		else {
			green[s_y - 1][t_x] = 1;
			green[s_y - 2][t_x] = 1;
		}
	}
}

void chk_line_blue() {
	//행 체크
	for (int y = 2; y < 6; y++) {
		int k = 0;
		for (int x = 0; x < 4; x++) {
			if (blue[y][x] == 1) k++;
		}
		if (k == 4) {
			for (int x = 0; x < 4; x++) {
				blue[y][x] = 0;
			}
			b_gravity(y);
			score++;
		}
	}

}

void chk_line_green() {

	for (int y = 2; y < 6; y++) {
		int k = 0;
		for (int x = 0; x < 4; x++) {
			if (green[y][x] == 1) k++;
		}
		if (k == 4) {
			for (int x = 0; x < 4; x++) {
				green[y][x] = 0;
			}
			g_gravity(y);
			score++;
		}
	}

}

void chk_top_blue() {
	//연한 라인 검사
	for (int y = 0; y < 2; y++) {
		int flag = 0;
		for (int x = 0; x < 4; x++) {
			if (blue[y][x] == 1) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			for (int x = 0; x < 4; x++) {
				blue[5][x] = 0;
			}
			b_gravity(5);
		}
	}
}

void chk_top_green() {
	//연한 라인 검사
	for (int y = 0; y < 2; y++) {
		int flag = 0;
		for (int x = 0; x < 4; x++) {
			if (green[y][x] == 1) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			for (int x = 0; x < 4; x++) {
				green[5][x] = 0;
			}
			g_gravity(5);
		}
	}

}


int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		int t, y, x;
		cin >> t >> y >> x;

		stack_blue(t, y);
		stack_green(t, x);
	
		chk_line_blue();
		chk_line_green();

		chk_top_blue();
		chk_top_green();

	}
	//chk_line_blue();
	//chk_line_green();

	int sum = 0;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 4; x++) {
			if (blue[y][x] == 1) sum++;
		}
	}
	
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 4; x++) {
			if (green[y][x] == 1) sum++;
		}
	}

	cout << score << "\n";
	cout << sum << "\n";
	
	return 0;
}