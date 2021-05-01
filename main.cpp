#include <bits/stdc++.h>
#include "myMatrix.hpp"

LL tmp[N][N];

LL read() {
	LL x=0,v=1; char ch=getchar();
	for (;ch<'0'||ch>'9';v=(ch=='-')?(-1):v,ch=getchar());
	for (;ch<='9'&&ch>='0';x=x*10+ch-'0',ch=getchar());
	return x*v;
}

// here's the main function
int main(void) {
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	LL n = 2000;
	rep(i, 1, n) rep (j, 1, n) {
		tmp[i][j] = read();
	}
	myMatrix <LL> G(n, n, tmp), H(n, n), E(n, n);
	G *= G;
	std:: cout << G;
	return 0;
}
