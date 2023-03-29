#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
bool chk(int x) {
	for(int i = 2;i * i <= x;++i) {
		if(x % i == 0) return 0;
	}
	return 1;
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::mt19937_64 gen(1145141919810);
	for(int i = 0;i < 10;++i) {
		int x;
		do {
			x = gen() % (int) 1e8 + 9e8;
		} while(!chk(x));
		cout << x << "\n\n";
	}
}
