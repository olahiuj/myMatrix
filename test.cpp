#include <bits/stdc++.h>

#define rep(i, st, ed) for (int i = st; i <= ed; ++ i)

typedef long long LL;

const int MOD=1e9+7;
const int N=6005;

LL a[N][N],b[N][N];

LL read() {
	LL x=0,v=1; char ch=getchar();
	for (;ch<'0'||ch>'9';v=(ch=='-')?(-1):v,ch=getchar());
	for (;ch<='9'&&ch>='0';x=x*10+ch-'0',ch=getchar());
	return x*v;
}

int main(void) {
	freopen("1.in","r",stdin);
	// freopen("std.out","w",stdout);
	int n=2000;
	rep(i,1,n) rep(j,1,n) a[i][j]=read();
	rep(i,1,n) rep(k,1,n) {
		LL t=a[i][k];
		if (!t) continue;
		rep(j,1,n) if (a[k][j]) {
			b[i][j]+=t*a[k][j]%MOD;
			if (b[i][j] >= MOD) b[i][j]-=MOD;
		}
	}
	rep(i,1,n) {
		rep(j,1,n) {
			printf("%lld ", b[i][j]);
		}
		puts("");
	}
	return 0;
}