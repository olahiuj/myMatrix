#include <bits/stdc++.h>
#include "myMatrix.hpp"

// here's the main function
int main(void) {
	freopen("data.in", "r", stdin);
	freopen("myp.out", "w", stdout);
	LL n, k; std:: cin >> n >> k;
	myMatrix <LL> G(n, n), H(n, n), E(n, n);
	rep(i, 1, n) rep (j, 1, n) {
		LL x; std:: cin >> x;
		G.set(i, j, x);
	}
	rep(i, 1, n) H.set(i, i, 1);
	H = G ^ k;
	std:: cout << H;
	return 0;
}
