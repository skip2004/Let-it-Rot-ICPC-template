#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
std::mt19937 gen;
std::basic_string<int> s;
template<class T>
void test(int n) {
	size_t t = clock();
	T a(n);
	generate(a.begin(), a.end(), n);
	std::cerr << "speed " << double(clock() - t) / CLOCKS_PER_SEC << '\n';
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	test<std::vector<int>>(1e8);
	// test<std::basic_string<int>>(1e8);
	std::basic_string<int> s(10);
}
